﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/impl/Windows.Foundation.Collections.0.h"
#include "winrt/impl/Windows.Foundation.0.h"
namespace winrt::Windows::Foundation
{
    struct WINRT_EBO IClosable :
        Windows::Foundation::IInspectable,
        impl::consume_t<IClosable>
    {
        IClosable(std::nullptr_t = nullptr) noexcept {}
        IClosable(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IDeferral :
        Windows::Foundation::IInspectable,
        impl::consume_t<IDeferral>,
        impl::require<Windows::Foundation::IDeferral, Windows::Foundation::IClosable>
    {
        IDeferral(std::nullptr_t = nullptr) noexcept {}
        IDeferral(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IDeferralFactory :
        Windows::Foundation::IInspectable,
        impl::consume_t<IDeferralFactory>
    {
        IDeferralFactory(std::nullptr_t = nullptr) noexcept {}
        IDeferralFactory(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IGetActivationFactory :
        Windows::Foundation::IInspectable,
        impl::consume_t<IGetActivationFactory>
    {
        IGetActivationFactory(std::nullptr_t = nullptr) noexcept {}
        IGetActivationFactory(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IGuidHelperStatics :
        Windows::Foundation::IInspectable,
        impl::consume_t<IGuidHelperStatics>
    {
        IGuidHelperStatics(std::nullptr_t = nullptr) noexcept {}
        IGuidHelperStatics(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IMemoryBuffer :
        Windows::Foundation::IInspectable,
        impl::consume_t<IMemoryBuffer>,
        impl::require<Windows::Foundation::IMemoryBuffer, Windows::Foundation::IClosable>
    {
        IMemoryBuffer(std::nullptr_t = nullptr) noexcept {}
        IMemoryBuffer(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IMemoryBufferFactory :
        Windows::Foundation::IInspectable,
        impl::consume_t<IMemoryBufferFactory>
    {
        IMemoryBufferFactory(std::nullptr_t = nullptr) noexcept {}
        IMemoryBufferFactory(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IMemoryBufferReference :
        Windows::Foundation::IInspectable,
        impl::consume_t<IMemoryBufferReference>,
        impl::require<Windows::Foundation::IMemoryBufferReference, Windows::Foundation::IClosable>
    {
        IMemoryBufferReference(std::nullptr_t = nullptr) noexcept {}
        IMemoryBufferReference(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IPropertyValue :
        Windows::Foundation::IInspectable,
        impl::consume_t<IPropertyValue>
    {
        IPropertyValue(std::nullptr_t = nullptr) noexcept {}
        IPropertyValue(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IPropertyValueStatics :
        Windows::Foundation::IInspectable,
        impl::consume_t<IPropertyValueStatics>
    {
        IPropertyValueStatics(std::nullptr_t = nullptr) noexcept {}
        IPropertyValueStatics(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IStringable :
        Windows::Foundation::IInspectable,
        impl::consume_t<IStringable>
    {
        IStringable(std::nullptr_t = nullptr) noexcept {}
        IStringable(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IUriEscapeStatics :
        Windows::Foundation::IInspectable,
        impl::consume_t<IUriEscapeStatics>
    {
        IUriEscapeStatics(std::nullptr_t = nullptr) noexcept {}
        IUriEscapeStatics(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IUriRuntimeClass :
        Windows::Foundation::IInspectable,
        impl::consume_t<IUriRuntimeClass>
    {
        IUriRuntimeClass(std::nullptr_t = nullptr) noexcept {}
        IUriRuntimeClass(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IUriRuntimeClassFactory :
        Windows::Foundation::IInspectable,
        impl::consume_t<IUriRuntimeClassFactory>
    {
        IUriRuntimeClassFactory(std::nullptr_t = nullptr) noexcept {}
        IUriRuntimeClassFactory(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IUriRuntimeClassWithAbsoluteCanonicalUri :
        Windows::Foundation::IInspectable,
        impl::consume_t<IUriRuntimeClassWithAbsoluteCanonicalUri>
    {
        IUriRuntimeClassWithAbsoluteCanonicalUri(std::nullptr_t = nullptr) noexcept {}
        IUriRuntimeClassWithAbsoluteCanonicalUri(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IWwwFormUrlDecoderEntry :
        Windows::Foundation::IInspectable,
        impl::consume_t<IWwwFormUrlDecoderEntry>
    {
        IWwwFormUrlDecoderEntry(std::nullptr_t = nullptr) noexcept {}
        IWwwFormUrlDecoderEntry(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IWwwFormUrlDecoderRuntimeClass :
        Windows::Foundation::IInspectable,
        impl::consume_t<IWwwFormUrlDecoderRuntimeClass>,
        impl::require<Windows::Foundation::IWwwFormUrlDecoderRuntimeClass, Windows::Foundation::Collections::IIterable<Windows::Foundation::IWwwFormUrlDecoderEntry>, Windows::Foundation::Collections::IVectorView<Windows::Foundation::IWwwFormUrlDecoderEntry>>
    {
        IWwwFormUrlDecoderRuntimeClass(std::nullptr_t = nullptr) noexcept {}
        IWwwFormUrlDecoderRuntimeClass(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_EBO IWwwFormUrlDecoderRuntimeClassFactory :
        Windows::Foundation::IInspectable,
        impl::consume_t<IWwwFormUrlDecoderRuntimeClassFactory>
    {
        IWwwFormUrlDecoderRuntimeClassFactory(std::nullptr_t = nullptr) noexcept {}
        IWwwFormUrlDecoderRuntimeClassFactory(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
}
