
namespace winrt::impl
{
    struct com_callback_args
    {
        uint32_t reserved1;
        uint32_t reserved2;
        void* data;
    };

    struct ICallbackWithNoReentrancyToApplicationSTA;

    template <> struct abi<Windows::Foundation::IUnknown>
    {
        struct WINRT_NOVTABLE type
        {
            virtual int32_t WINRT_CALL QueryInterface(guid const& id, void** object) noexcept = 0;
            virtual uint32_t WINRT_CALL AddRef() noexcept = 0;
            virtual uint32_t WINRT_CALL Release() noexcept = 0;
        };
    };

    using unknown_abi = abi_t<Windows::Foundation::IUnknown>;

    template <> struct abi<Windows::Foundation::IInspectable>
    {
        struct WINRT_NOVTABLE type : unknown_abi
        {
            virtual int32_t WINRT_CALL GetIids(uint32_t* count, guid** ids) noexcept = 0;
            virtual int32_t WINRT_CALL GetRuntimeClassName(void** name) noexcept = 0;
            virtual int32_t WINRT_CALL GetTrustLevel(Windows::Foundation::TrustLevel* level) noexcept = 0;
        };
    };

    using inspectable_abi = abi_t<Windows::Foundation::IInspectable>;

    struct WINRT_NOVTABLE IAgileObject : unknown_abi
    {
    };

    struct WINRT_NOVTABLE IAgileReference : unknown_abi
    {
        virtual int32_t WINRT_CALL Resolve(guid const& id, void** object) noexcept = 0;
    };

    struct WINRT_NOVTABLE IMarshal : unknown_abi
    {
        virtual int32_t WINRT_CALL GetUnmarshalClass(guid const& riid, void* pv, uint32_t dwDestContext, void* pvDestContext, uint32_t mshlflags, guid* pCid) noexcept = 0;
        virtual int32_t WINRT_CALL GetMarshalSizeMax(guid const& riid, void* pv, uint32_t dwDestContext, void* pvDestContext, uint32_t mshlflags, uint32_t* pSize) noexcept = 0;
        virtual int32_t WINRT_CALL MarshalInterface(void* pStm, guid const& riid, void* pv, uint32_t dwDestContext, void* pvDestContext, uint32_t mshlflags) noexcept = 0;
        virtual int32_t WINRT_CALL UnmarshalInterface(void* pStm, guid const& riid, void** ppv) noexcept = 0;
        virtual int32_t WINRT_CALL ReleaseMarshalData(void* pStm) noexcept = 0;
        virtual int32_t WINRT_CALL DisconnectObject(uint32_t dwReserved) noexcept = 0;
    };

    struct WINRT_NOVTABLE IStaticLifetime : inspectable_abi
    {
        virtual int32_t WINRT_CALL unused() noexcept = 0;
        virtual int32_t WINRT_CALL GetCollection(void** value) noexcept = 0;
    };

    struct WINRT_NOVTABLE IWeakReference : unknown_abi
    {
        virtual int32_t WINRT_CALL Resolve(guid const& iid, void** objectReference) noexcept = 0;
    };

    struct WINRT_NOVTABLE IWeakReferenceSource : unknown_abi
    {
        virtual int32_t WINRT_CALL GetWeakReference(IWeakReference** weakReference) noexcept = 0;
    };

    struct WINRT_NOVTABLE IRestrictedErrorInfo : unknown_abi
    {
        virtual int32_t WINRT_CALL GetErrorDetails(bstr* description, int32_t* error, bstr* restrictedDescription, bstr* capabilitySid) noexcept = 0;
        virtual int32_t WINRT_CALL GetReference(bstr* reference) noexcept = 0;
    };

    struct WINRT_NOVTABLE ILanguageExceptionErrorInfo : unknown_abi
    {
        virtual int32_t WINRT_CALL GetLanguageException(void** exception) noexcept = 0;
    };

    struct WINRT_NOVTABLE ILanguageExceptionErrorInfo2 : ILanguageExceptionErrorInfo
    {
        virtual int32_t WINRT_CALL GetPreviousLanguageExceptionErrorInfo(ILanguageExceptionErrorInfo2** previous) noexcept = 0;
        virtual int32_t WINRT_CALL CapturePropagationContext(void* exception) noexcept = 0;
        virtual int32_t WINRT_CALL GetPropagationContextHead(ILanguageExceptionErrorInfo2** head) noexcept = 0;
    };

    struct WINRT_NOVTABLE IContextCallback : unknown_abi
    {
        virtual int32_t WINRT_CALL ContextCallback(int32_t(WINRT_CALL *callback)(com_callback_args*), com_callback_args* args, guid const& iid, int method, void* reserved) noexcept = 0;
    };

    struct WINRT_NOVTABLE IServerSecurity : unknown_abi
    {
        virtual int32_t WINRT_CALL QueryBlanket(uint32_t*, uint32_t*, wchar_t**, uint32_t*, uint32_t*, void**, uint32_t*) noexcept = 0;
        virtual int32_t WINRT_CALL ImpersonateClient() noexcept = 0;
        virtual int32_t WINRT_CALL RevertToSelf() noexcept = 0;
        virtual int32_t WINRT_CALL IsImpersonating() noexcept = 0;
    };

    struct WINRT_NOVTABLE IBufferByteAccess : unknown_abi
    {
        virtual int32_t WINRT_CALL Buffer(uint8_t** value) noexcept = 0;
    };
}
