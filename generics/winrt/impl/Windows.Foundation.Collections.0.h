﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/base.h"
namespace winrt::Windows::Foundation
{
    struct EventRegistrationToken;
}
namespace winrt::Windows::Foundation::Collections
{
    template <typename T> struct IObservableVector;
    struct IPropertySet;
    struct PropertySet;
    struct StringMap;
    struct ValueSet;
}
namespace winrt::impl
{
    template <typename T> struct category<Windows::Foundation::Collections::IObservableVector<T>>
    {
        using type = pinterface_category<T>;
        static constexpr guid value{ 0x5917EB53,0x50B4,0x4A0D,{ 0xB3,0x09,0x65,0x86,0x2B,0x3F,0x1D,0xBC } };
    };
    template <> struct category<Windows::Foundation::Collections::IPropertySet>
    {
        using type = interface_category;
    };
    template <> struct category<Windows::Foundation::Collections::PropertySet>
    {
        using type = class_category;
    };
    template <> struct category<Windows::Foundation::Collections::StringMap>
    {
        using type = class_category;
    };
    template <> struct category<Windows::Foundation::Collections::ValueSet>
    {
        using type = class_category;
    };
    template <typename T> struct name<Windows::Foundation::Collections::IObservableVector<T>>
    {
        static constexpr auto value{ zcombine(L"Windows.Foundation.Collections.IObservableVector`1<", name_v<T>, L">") };
    };
    template <> struct name<Windows::Foundation::Collections::IPropertySet>
    {
        static constexpr auto & value{ L"Windows.Foundation.Collections.IPropertySet" };
    };
    template <> struct name<Windows::Foundation::Collections::PropertySet>
    {
        static constexpr auto & value{ L"Windows.Foundation.Collections.PropertySet" };
    };
    template <> struct name<Windows::Foundation::Collections::StringMap>
    {
        static constexpr auto & value{ L"Windows.Foundation.Collections.StringMap" };
    };
    template <> struct name<Windows::Foundation::Collections::ValueSet>
    {
        static constexpr auto & value{ L"Windows.Foundation.Collections.ValueSet" };
    };
    template <typename T> struct guid_storage<Windows::Foundation::Collections::IObservableVector<T>>
    {
        static constexpr guid value{ pinterface_guid<Windows::Foundation::Collections::IObservableVector<T>>::value };
    };
    template <> struct guid_storage<Windows::Foundation::Collections::IPropertySet>
    {
        static constexpr guid value{ 0x8A43ED9F,0xF4E6,0x4421,{ 0xAC,0xF9,0x1D,0xAB,0x29,0x86,0x82,0x0C } };
    };
    template <> struct default_interface<Windows::Foundation::Collections::PropertySet>
    {
        using type = Windows::Foundation::Collections::IPropertySet;
    };
    template <> struct default_interface<Windows::Foundation::Collections::StringMap>
    {
        using type = Windows::Foundation::Collections::IMap<hstring, hstring>;
    };
    template <> struct default_interface<Windows::Foundation::Collections::ValueSet>
    {
        using type = Windows::Foundation::Collections::IPropertySet;
    };
    template <typename T> struct abi<Windows::Foundation::Collections::IObservableVector<T>>
    {
        struct type : inspectable_abi
        {
            virtual int32_t WINRT_CALL add_VectorChanged(void*, winrt::event_token*) noexcept = 0;
            virtual int32_t WINRT_CALL remove_VectorChanged(winrt::event_token) noexcept = 0;
        };
    };
    template <> struct abi<Windows::Foundation::Collections::IPropertySet>
    {
        struct type : inspectable_abi
        {
        };
    };
    template <typename D>
    struct consume_Windows_Foundation_Collections_IObservableVector`1
    {
        winrt::event_token VectorChanged(Windows::Foundation::Collections::VectorChangedEventHandler<T> const& vhnd) const;
        using VectorChanged_revoker = impl::event_revoker<Windows::Foundation::Collections::IObservableVector`1, &impl::abi_t<Windows::Foundation::Collections::IObservableVector`1>::remove_VectorChanged>;
        VectorChanged_revoker VectorChanged(auto_revoke_t, Windows::Foundation::Collections::VectorChangedEventHandler<T> const& vhnd) const;
        void VectorChanged(winrt::event_token const& token) const noexcept;
    };
    template <> struct consume<Windows::Foundation::Collections::IObservableVector`1>
    {
        template <typename D> using type = consume_Windows_Foundation_Collections_IObservableVector`1<D>;
    };
    template <typename D>
    struct consume_Windows_Foundation_Collections_IPropertySet
    {
    };
    template <> struct consume<Windows::Foundation::Collections::IPropertySet>
    {
        template <typename D> using type = consume_Windows_Foundation_Collections_IPropertySet<D>;
    };
}
