#include "pch.h"
#include <variant>
#include "object_visualizer.h"
#include "property_visualizer.h"

using namespace Microsoft::VisualStudio::Debugger;
using namespace Microsoft::VisualStudio::Debugger::Evaluation;

using namespace xlang;
using namespace xlang::meta;
using namespace xlang::meta::reader;

template <typename...T> struct overloaded : T... { using T::operator()...; };
template <typename...T> overloaded(T...)->overloaded<T...>;

#define IID_IInspectable L"AF86E2E0-B12D-4C6A-9C5A-D7AA65101E90"
#define IID_IStringable  L"96369F54-8EB6-48F0-ABCE-C1B211E627C3"

constexpr struct
{
    PCWSTR propField;
    PCWSTR displayType;
}
g_categoryData[] = 
{
    { L"b", L"bool" },
    { L"c", L"wchar_t" },
    { L"i1", L"int8_t" },
    { L"u1", L"uint8_t" },
    { L"i2", L"int16_t" },
    { L"u2", L"uint16_t" },
    { L"i4", L"int32_t" },
    { L"u4", L"uint32_t" },
    { L"i8", L"int64_t" },
    { L"u8", L"uint64_t" },
    { L"r4", L"float" },
    { L"r8", L"double" },
    { L"s,sh", L"winrt::hstring" },
    { L"g", L"winrt::guid" },
};

static HRESULT EvaluatePropertyExpression(
    _In_ PropertyData const& prop,
    _In_ DkmVisualizedExpression* pExpression,
    _In_ DkmPointerValueHome* pObject,
    bool isAbiObject,
    _Out_ winrt::com_ptr<DkmEvaluationResult>& pEvaluationResult
)
{
    wchar_t abiAddress[40];
    bool is64Bit = ((pExpression->RuntimeInstance()->Process()->SystemInformation()->Flags() & DefaultPort::DkmSystemInformationFlags::Is64Bit) != 0);
    swprintf_s(abiAddress, is64Bit ? L"%s0x%I64x" : L"%s0x%08x", isAbiObject ? L"(::IUnknown*)" : L"*(::IUnknown**)", pObject->Address());
    wchar_t wszEvalText[500];
    std::wstring propCast;
    PCWSTR propField;
	if (prop.category < PropertyCategory::Value)
    {
        propField = g_categoryData[(int)prop.category].propField;
    }
    else
    {
        propField = L"v";
        propCast = L"*(" + prop.abiType + L"*)";
    }
    swprintf_s(wszEvalText, L"%sWINRT_abi_val(%s, L\"{%s}\", %i).%s", propCast.c_str(), abiAddress, prop.iid.c_str(), prop.index, propField);
#ifdef _DEBUG
    OutputDebugStringW(wszEvalText);
    OutputDebugStringW(L"\n");
#endif

    winrt::com_ptr<DkmString> pEvalText;
    IF_FAIL_RET(DkmString::Create(DkmSourceString(wszEvalText), pEvalText.put()));

    auto evalFlags = DkmEvaluationFlags::TreatAsExpression | DkmEvaluationFlags::ForceEvaluationNow | DkmEvaluationFlags::ForceRealFuncEval;

    auto inspectionContext = pExpression->InspectionContext();
    winrt::com_ptr<DkmLanguageExpression> pLanguageExpression;
    IF_FAIL_RET(DkmLanguageExpression::Create(
        inspectionContext->Language(),
        evalFlags,
        pEvalText.get(),
        DkmDataItem::Null(),
        pLanguageExpression.put()
    ));

    winrt::com_ptr<DkmInspectionContext> pInspectionContext;
    if ( (pExpression->InspectionContext()->EvaluationFlags() & evalFlags) != evalFlags)
    {
        DkmInspectionContext::Create(
            inspectionContext->InspectionSession(),
            inspectionContext->RuntimeInstance(),
            inspectionContext->Thread(),
            inspectionContext->Timeout(),
            evalFlags,
            inspectionContext->FuncEvalFlags(),
            inspectionContext->Radix(),
            inspectionContext->Language(),
            inspectionContext->ReturnValue(),
            pInspectionContext.put()
        );
    }
    else
    {
        pInspectionContext.copy_from(inspectionContext);
    }

    IF_FAIL_RET(pExpression->EvaluateExpressionCallback(
        pInspectionContext.get(),
        pLanguageExpression.get(),
        pExpression->StackFrame(),
        pEvaluationResult.put()
    ));

    return S_OK;
}

static HRESULT EvaluatePropertyString(
    _In_ PropertyData const& prop,
    _In_ DkmVisualizedExpression* pExpression,
    _In_ DkmPointerValueHome* pObject,
    bool isAbiObject,
    _Out_ winrt::com_ptr<DkmString>& pValue
)
{
    winrt::com_ptr<DkmEvaluationResult> pEvaluationResult;
    IF_FAIL_RET(EvaluatePropertyExpression(prop, pExpression, pObject, isAbiObject, pEvaluationResult));
    if (pEvaluationResult->TagValue() != DkmEvaluationResult::Tag::SuccessResult)
    {
        return E_FAIL;
    }
    winrt::com_ptr<DkmSuccessEvaluationResult> pSuccessEvaluationResult = pEvaluationResult.as<DkmSuccessEvaluationResult>();
    if (pSuccessEvaluationResult->Address()->Value() != 0)
    {
        pValue.copy_from(pSuccessEvaluationResult->Value());
    }
    return S_OK;
}

static HRESULT ObjectToString(
    _In_ DkmVisualizedExpression* pExpression,
    _In_ DkmPointerValueHome* pObject,
    bool isAbiObject,
    _Out_ winrt::com_ptr<DkmString>& pValue
)
{
    if (SUCCEEDED(EvaluatePropertyString({ IID_IStringable, 0, PropertyCategory::String }, pExpression, pObject, isAbiObject, pValue)))
    {
        if (!pValue || pValue->Length() == 0)
        {
            pValue = nullptr;
            IF_FAIL_RET(DkmString::Create(L"<Expand object to view properties>", pValue.put()));
        }
    }
    else
    {
        IF_FAIL_RET(DkmString::Create(L"<Object uninitialized or information unavailable>", pValue.put()));
    }

    return S_OK;
}

static HRESULT CreateChildVisualizedExpression(
    _In_ PropertyData const& prop,
    _In_ DkmVisualizedExpression* pParent,
    bool isAbiObject,
    _Deref_out_ DkmChildVisualizedExpression** ppResult
)
{
    *ppResult = nullptr;

    winrt::com_ptr<DkmEvaluationResult> pEvaluationResult;
    auto valueHome = make_com_ptr(pParent->ValueHome());
    winrt::com_ptr<DkmPointerValueHome> pParentPointer = valueHome.as<DkmPointerValueHome>();
    IF_FAIL_RET(EvaluatePropertyExpression(prop, pParent, pParentPointer.get(), isAbiObject, pEvaluationResult));
    if (pEvaluationResult->TagValue() != DkmEvaluationResult::Tag::SuccessResult)
    {
        return E_FAIL;
    }

    winrt::com_ptr<DkmSuccessEvaluationResult> pSuccessEvaluationResult = pEvaluationResult.as<DkmSuccessEvaluationResult>();
    winrt::com_ptr<DkmString> pValue;
    winrt::com_ptr<DkmPointerValueHome> pChildPointer;
    bool isNonNullObject = false;
    if (prop.category == PropertyCategory::Class)
    {
        auto childObjectAddress = pSuccessEvaluationResult->Address()->Value();
        if (childObjectAddress)
        {
            isNonNullObject = true;
            IF_FAIL_RET(DkmPointerValueHome::Create(childObjectAddress, pChildPointer.put()));
            IF_FAIL_RET(ObjectToString(pParent, pChildPointer.get(), true, pValue));
        }
    }
    if(!isNonNullObject)
    {
        winrt::com_ptr<DkmExpressionValueHome> expressionValueHome = make_com_ptr(pParent->ValueHome());
        pChildPointer = expressionValueHome.as<DkmPointerValueHome>();
        pValue.copy_from(pSuccessEvaluationResult->Value());
    }

    winrt::com_ptr<DkmString> pDisplayName;
    IF_FAIL_RET(DkmString::Create(prop.displayName.c_str(), pDisplayName.put()));

    PCWSTR displayType;
    if (prop.category < PropertyCategory::Value)
    {
        displayType = g_categoryData[(int)prop.category].displayType;
    }
    else
    {
        displayType = prop.displayType.c_str();
    }
    winrt::com_ptr<DkmString> pDisplayType;
    IF_FAIL_RET(DkmString::Create(displayType, pDisplayType.put()));

    winrt::com_ptr<DkmSuccessEvaluationResult> pVisualizedResult;
    IF_FAIL_RET(DkmSuccessEvaluationResult::Create(
        pParent->InspectionContext(),
        pParent->StackFrame(),
        pDisplayName.get(),
        pSuccessEvaluationResult->FullName(),
        pSuccessEvaluationResult->Flags(),
        pValue.get(),
        pSuccessEvaluationResult->EditableValue(),
        pDisplayType.get(),
        pSuccessEvaluationResult->Category(),
        pSuccessEvaluationResult->Access(),
        pSuccessEvaluationResult->StorageType(),
        pSuccessEvaluationResult->TypeModifierFlags(),
        pSuccessEvaluationResult->Address(),
        pSuccessEvaluationResult->CustomUIVisualizers(),
        pSuccessEvaluationResult->ExternalModules(),
        DkmDataItem::Null(),
        pVisualizedResult.put()
    ));

    winrt::com_ptr<DkmChildVisualizedExpression> pChildVisualizedExpression;
    IF_FAIL_RET(DkmChildVisualizedExpression::Create(
        pParent->InspectionContext(),
        pParent->VisualizerId(),
        pParent->SourceId(),
        pParent->StackFrame(),
        pChildPointer.get(),
        pVisualizedResult.get(),
        pParent,
        2,
        DkmDataItem::Null(),
        pChildVisualizedExpression.put()
    ));

    if (isNonNullObject)
    {
        winrt::com_ptr<object_visualizer> pObjectVisualizer = winrt::make_self<object_visualizer>(pChildVisualizedExpression.get(), true);
        IF_FAIL_RET(pChildVisualizedExpression->SetDataItem(DkmDataCreationDisposition::CreateNew, pObjectVisualizer.get()));
    }
    else
    {
        winrt::com_ptr<property_visualizer> pPropertyVisualizer = winrt::make_self<property_visualizer>(pChildVisualizedExpression.get(), pSuccessEvaluationResult.get());
        IF_FAIL_RET(pChildVisualizedExpression->SetDataItem(DkmDataCreationDisposition::CreateNew, pPropertyVisualizer.get()));
    }

    *ppResult = pChildVisualizedExpression.detach();

    return S_OK;
}

struct property_type
{
    MethodDef get;
    MethodDef set;
};

void GetInterfaceData(
    coded_index<TypeDefOrRef> index,
    _Inout_ std::vector<PropertyData>& propertyData,
    _Out_ bool& isStringable
){
    auto resolve_type_index = [](coded_index<TypeDefOrRef> index) -> TypeDef
    {
        switch (index.type())
        {
        case TypeDefOrRef::TypeDef:
        {
            return index.TypeDef();
        }
        case TypeDefOrRef::TypeRef:
        {
            return find_required(index.TypeRef());
        }
        case TypeDefOrRef::TypeSpec:
        {
            auto type_signature = index.TypeSpec().Signature();
            auto signature = type_signature.GenericTypeInst();
            return find_required(signature.GenericType().TypeRef());
        }
        }
        return {};
    };

    auto type = resolve_type_index(index);
    auto attribute = get_attribute(type, "Windows.Foundation.Metadata", "GuidAttribute");
    if (!attribute)
    {
        throw_invalid("'Windows.Foundation.Metadata.GuidAttribute' attribute for type '", type.TypeNamespace(), ".", type.TypeName(), "' not found");
    }
    auto args = attribute.Value().FixedArgs();
    std::string guid(68, '?');
    int count = sprintf_s(guid.data(), guid.size() + 1,
        "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
        , std::get<uint32_t>(std::get<ElemSig>(args[0].value).value)
        , std::get<uint16_t>(std::get<ElemSig>(args[1].value).value)
        , std::get<uint16_t>(std::get<ElemSig>(args[2].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[3].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[4].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[5].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[6].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[7].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[8].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[9].value).value)
        , std::get<uint8_t>(std::get<ElemSig>(args[10].value).value));
    guid.resize(count);
    std::wstring propIid(guid.cbegin(), guid.cend());

    if (propIid == IID_IStringable)
    {
        isStringable = true;
        return;
    }

    int32_t propIndex = -1;
    for (auto&& method : type.MethodList())
    {
        propIndex++;

        auto isGetter = method.Flags().SpecialName() && starts_with(method.Name(), "get_");
        if (!isGetter)
        {
            continue;
        }

        PropertyCategory propCategory;
        std::wstring propAbiType;
        std::wstring propDisplayType;

        auto retType = method.Signature().ReturnType();
        std::visit(overloaded
            {
                [&](ElementType type)
                {
                    if ((type < ElementType::Boolean) || (type > ElementType::String))
                    {
                        return;
                    }
                    propCategory = (PropertyCategory)(static_cast<std::underlying_type<ElementType>::type>(type) -
                        static_cast<std::underlying_type<ElementType>::type>(ElementType::Boolean));
                },
                [&](coded_index<TypeDefOrRef> const& index)
                {
                    auto type = resolve_type_index(index);
                    auto typeName = type.TypeName();
                    if (typeName == "GUID"sv)
                    {
                        propCategory = PropertyCategory::Guid;
                    }
                    else
                    {
                        auto fullTypeName = std::string(type.TypeNamespace()) + "::" + std::string(type.TypeName());

                        // Types come back from winmd files with '.', need to be '::'
                        // Ex. Windows.Foundation.Uri needs to be Windows::Foundation::Uri
                        wchar_t cppTypename[500];
                        size_t i, j;
                        for (i = 0, j = 0; i < (fullTypeName.length() + 1); i++, j++)
                        {
                            if (fullTypeName[i] == L'.')
                            {
                                cppTypename[j++] = L':';
                                cppTypename[j] = L':';
                            }
                            else
                            {
                                cppTypename[j] = fullTypeName[i];
                            }
                        }

                        propDisplayType = std::wstring(L"winrt::") + cppTypename;
                        if(get_category(type) == category::class_type)
                        {
                            propCategory = PropertyCategory::Class;
                            propAbiType = L"winrt::impl::IInspectable*";
                        }
                        else
                        {
                            propCategory = PropertyCategory::Value;
                            propAbiType = propDisplayType;
                        }
                    }
                },
                [&](GenericTypeIndex /*var*/)
                {
                    // TODO: generic properties
                },
                [&](GenericTypeInstSig const& /*type*/)
                {
                    // TODO: generic properties
                }
            },
            retType.Type().Type());

        auto propName = method.Name().substr(4);
        std::wstring propDisplayName(propName.cbegin(), propName.cend());
        propertyData.push_back({ propIid, propIndex, propCategory, propAbiType, propDisplayType, propDisplayName });
    }
}

void object_visualizer::GetPropertyData()
{
    winrt::com_ptr<DkmString> pValue;
    winrt::com_ptr<DkmChildVisualizedExpression> pPropertyVisualized;
    if (FAILED(CreateChildVisualizedExpression({ IID_IInspectable, -2, PropertyCategory::String }, m_pVisualizedExpression.get(), m_isAbiObject, pPropertyVisualized.put())) ||
        FAILED(pPropertyVisualized->GetUnderlyingString(pValue.put())))
    {
        return;
    }
    
    auto runtimeTypeName = winrt::to_string(pValue->Value());
    auto type = db->find(runtimeTypeName);
    if (!type)
    {
        auto processPath = m_pVisualizedExpression->RuntimeInstance()->Process()->Path()->Value();
        load_type_winmd(processPath, runtimeTypeName);
        type = db->find(runtimeTypeName);
    }
    if (!type)
    {
        return;
    }

    if (get_category(type) == category::class_type)
    {
        auto impls = type.InterfaceImpl();
        for (auto&& impl : impls)
        {
            GetInterfaceData(impl.Interface(), m_propertyData, m_isStringable);
        }
    }
    else if (get_category(type) == category::interface_type)
    {
        auto impls = type.InterfaceImpl();
        for (auto&& impl : impls)
        {
            GetInterfaceData(impl.Interface(), m_propertyData, m_isStringable);
        }
        GetInterfaceData(type.coded_index<TypeDefOrRef>(), m_propertyData, m_isStringable);
    }
}

HRESULT object_visualizer::CreateEvaluationResult(_In_ DkmVisualizedExpression* pVisualizedExpression, _In_ bool isAbiObject, _Deref_out_ DkmEvaluationResult** ppResultObject)
{
    winrt::com_ptr<object_visualizer> pObjectVisualizer = winrt::make_self<object_visualizer>(pVisualizedExpression, isAbiObject);

    pVisualizedExpression->SetDataItem(DkmDataCreationDisposition::CreateNew, pObjectVisualizer.get());

    IF_FAIL_RET(pObjectVisualizer->CreateEvaluationResult(ppResultObject));

    IF_FAIL_RET(pVisualizedExpression->SetDataItem(DkmDataCreationDisposition::CreateNew, *ppResultObject));

    return S_OK;
}

HRESULT object_visualizer::CreateEvaluationResult(_Deref_out_ DkmEvaluationResult** ppResultObject)
{
    winrt::com_ptr<DkmRootVisualizedExpression> pRootVisualizedExpression = m_pVisualizedExpression.as<DkmRootVisualizedExpression>();

    auto valueHome = make_com_ptr(m_pVisualizedExpression->ValueHome());
    winrt::com_ptr<DkmPointerValueHome> pPointerValueHome = valueHome.as<DkmPointerValueHome>();

    winrt::com_ptr<DkmString> pValue;
    IF_FAIL_RET(ObjectToString(m_pVisualizedExpression.get(), pPointerValueHome.get(), m_isAbiObject, pValue));

    winrt::com_ptr<DkmDataAddress> pAddress;
    IF_FAIL_RET(DkmDataAddress::Create(m_pVisualizedExpression->StackFrame()->RuntimeInstance(), pPointerValueHome->Address(), nullptr, pAddress.put()));

    winrt::com_ptr<DkmSuccessEvaluationResult> pSuccessEvaluationResult;
    IF_FAIL_RET(DkmSuccessEvaluationResult::Create(
        m_pVisualizedExpression->InspectionContext(),
        m_pVisualizedExpression->StackFrame(),
        pRootVisualizedExpression->Name(),
        pRootVisualizedExpression->FullName(),
        DkmEvaluationResultFlags::Expandable | DkmEvaluationResultFlags::ReadOnly,
        pValue.get(),
        pValue.get(),
        pRootVisualizedExpression->Type(),
        DkmEvaluationResultCategory::Class,
        DkmEvaluationResultAccessType::None,
        DkmEvaluationResultStorageType::None,
        DkmEvaluationResultTypeModifierFlags::None,
        pAddress.get(),
        (DkmReadOnlyCollection<DkmCustomUIVisualizerInfo*>*)nullptr,
        (DkmReadOnlyCollection<DkmModuleInstance*>*)nullptr,
        DkmDataItem::Null(),
        pSuccessEvaluationResult.put()
    ));

    pSuccessEvaluationResult->SetDataItem(DkmDataCreationDisposition::CreateNew, this);

    *ppResultObject = (DkmEvaluationResult*)pSuccessEvaluationResult.detach();

    return S_OK;
}

HRESULT object_visualizer::GetChildren(
    _In_ UINT32 /*InitialRequestSize*/,
    _In_ DkmInspectionContext* pInspectionContext,
    _Out_ DkmArray<DkmChildVisualizedExpression*>* pInitialChildren,
    _Deref_out_ DkmEvaluationResultEnumContext** ppEnumContext
)
{
    // Ignore metadata errors to ensure that Raw Data is always available
    try
    {
        GetPropertyData();
    }
    catch (...)
    {
    }

    winrt::com_ptr<DkmEvaluationResultEnumContext> pEnumContext;
    IF_FAIL_RET(DkmEvaluationResultEnumContext::Create(
        static_cast<uint32_t>(m_propertyData.size()),
        m_pVisualizedExpression->StackFrame(),
        pInspectionContext,
        this,
        pEnumContext.put()));

    DkmAllocArray(0, pInitialChildren);
    *ppEnumContext = pEnumContext.detach();

    return S_OK;
}

HRESULT object_visualizer::GetItems(
    _In_ DkmVisualizedExpression* /*pVisualizedExpression*/,
    _In_ DkmEvaluationResultEnumContext* /*pEnumContext*/,
    _In_ UINT32 StartIndex,
    _In_ UINT32 Count,
    _Out_ DkmArray<DkmChildVisualizedExpression*>* pItems
)
{
    std::list<winrt::com_ptr<DkmChildVisualizedExpression>> childItems;

    auto pParent = m_pVisualizedExpression.get();
    for( auto childIndex = StartIndex; childIndex < StartIndex + Count; ++childIndex)
    {
        auto& prop = m_propertyData[childIndex];
        winrt::com_ptr<DkmChildVisualizedExpression> pPropertyVisualized;
        if(FAILED(CreateChildVisualizedExpression(prop, pParent, m_isAbiObject, pPropertyVisualized.put())))
        {
            winrt::com_ptr<DkmString> pErrorMessage;
            IF_FAIL_RET(DkmString::Create(L"<Property evaluation failed>", pErrorMessage.put()));
            
            winrt::com_ptr<DkmString> pDisplayName;
            IF_FAIL_RET(DkmString::Create(prop.displayName.c_str(), pDisplayName.put()));

            winrt::com_ptr<DkmFailedEvaluationResult> pVisualizedResult;
            IF_FAIL_RET(DkmFailedEvaluationResult::Create(
                pParent->InspectionContext(),
                pParent->StackFrame(),
                pDisplayName.get(),
                nullptr, 
                pErrorMessage.get(),
                DkmEvaluationResultFlags::ExceptionThrown, 
                DkmDataItem::Null(),
                pVisualizedResult.put()
            ));

            IF_FAIL_RET(DkmChildVisualizedExpression::Create(
                pParent->InspectionContext(),
                pParent->VisualizerId(),
                pParent->SourceId(),
                pParent->StackFrame(),
                nullptr,
                pVisualizedResult.get(),
                pParent,
                2,
                DkmDataItem::Null(),
                pPropertyVisualized.put()
            ));
        }
        childItems.push_back(pPropertyVisualized);
    }

    CAutoDkmArray<DkmChildVisualizedExpression*> resultValues;
    IF_FAIL_RET(DkmAllocArray(childItems.size(), &resultValues));

    UINT32 j = 0;
    auto pos = childItems.begin();
    while (pos != childItems.end())
    {
        winrt::com_ptr<DkmChildVisualizedExpression> pCurr = *pos;
        resultValues.Members[j++] = pCurr.detach();
        pos++;
    }

    *pItems = resultValues.Detach();

    return S_OK;
}
