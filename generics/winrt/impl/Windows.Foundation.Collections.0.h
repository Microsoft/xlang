﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/base.h"
namespace winrt::Windows::Foundation
{
    struct EventRegistrationToken;
}
namespace winrt::Windows::Foundation::Collections
{
    template <typename K, typename V> struct IObservableMap;
    template <typename T> struct IObservableVector;
    struct IPropertySet;
    template <typename T> struct IVector;
    struct PropertySet;
    struct StringMap;
    struct ValueSet;
}
namespace winrt::impl
{
    template <typename K, typename V> struct category<Windows::Foundation::Collections::IObservableMap<K, V>>
    {
        using type = pinterface_category<K, V>;
        static constexpr guid value{ 0x65DF2BF5,0xBF39,0x41B5,{ 0xAE,0xBC,0x5A,0x9D,0x86,0x5E,0x47,0x2B } };
    };
    template <typename T> struct category<Windows::Foundation::Collections::IObservableVector<T>>
    {
        using type = pinterface_category<T>;
        static constexpr guid value{ 0x5917EB53,0x50B4,0x4A0D,{ 0xB3,0x09,0x65,0x86,0x2B,0x3F,0x1D,0xBC } };
    };
    template <> struct category<Windows::Foundation::Collections::IPropertySet>
    {
        using type = interface_category;
    };
    template <typename T> struct category<Windows::Foundation::Collections::IVector<T>>
    {
        using type = pinterface_category<T>;
        static constexpr guid value{ 0x913337E9,0x11A1,0x4345,{ 0xA3,0xA2,0x4E,0x7F,0x95,0x6E,0x22,0x2D } };
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
    template <typename K, typename V> struct name<Windows::Foundation::Collections::IObservableMap<K, V>>
    {
        static constexpr auto value{ zcombine(L"Windows.Foundation.Collections.IObservableMap`2<", name_v<K>, name_v<V>, L">") };
    };
    template <typename T> struct name<Windows::Foundation::Collections::IObservableVector<T>>
    {
        static constexpr auto value{ zcombine(L"Windows.Foundation.Collections.IObservableVector`1<", name_v<T>, L">") };
    };
    template <> struct name<Windows::Foundation::Collections::IPropertySet>
    {
        static constexpr auto & value{ L"Windows.Foundation.Collections.IPropertySet" };
    };
    template <typename T> struct name<Windows::Foundation::Collections::IVector<T>>
    {
        static constexpr auto value{ zcombine(L"Windows.Foundation.Collections.IVector`1<", name_v<T>, L">") };
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
    template <typename K, typename V> struct guid_storage<Windows::Foundation::Collections::IObservableMap<K, V>>
    {
        static constexpr guid value{ pinterface_guid<Windows::Foundation::Collections::IObservableMap<K, V>>::value };
    };
    template <typename T> struct guid_storage<Windows::Foundation::Collections::IObservableVector<T>>
    {
        static constexpr guid value{ pinterface_guid<Windows::Foundation::Collections::IObservableVector<T>>::value };
    };
    template <> struct guid_storage<Windows::Foundation::Collections::IPropertySet>
    {
        static constexpr guid value{ 0x8A43ED9F,0xF4E6,0x4421,{ 0xAC,0xF9,0x1D,0xAB,0x29,0x86,0x82,0x0C } };
    };
    template <typename T> struct guid_storage<Windows::Foundation::Collections::IVector<T>>
    {
        static constexpr guid value{ pinterface_guid<Windows::Foundation::Collections::IVector<T>>::value };
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
    template <typename K, typename V> struct abi<Windows::Foundation::Collections::IObservableMap<K, V>>
    {
        struct type : inspectable_abi
        {
            virtual int32_t WINRT_CALL add_MapChanged(void*, winrt::event_token*) noexcept = 0;
            virtual int32_t WINRT_CALL remove_MapChanged(winrt::event_token) noexcept = 0;
        };
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
    template <typename T> struct abi<Windows::Foundation::Collections::IVector<T>>
    {
        struct type : inspectable_abi
        {
            virtual int32_t WINRT_CALL GetAt(uint32_t, arg_out<T>) noexcept = 0;
            virtual int32_t WINRT_CALL get_Size(uint32_t*) noexcept = 0;
            virtual int32_t WINRT_CALL GetView(void**) noexcept = 0;
            virtual int32_t WINRT_CALL IndexOf(arg_in<T>, uint32_t*, bool*) noexcept = 0;
            virtual int32_t WINRT_CALL SetAt(uint32_t, arg_in<T>) noexcept = 0;
            virtual int32_t WINRT_CALL InsertAt(uint32_t, arg_in<T>) noexcept = 0;
            virtual int32_t WINRT_CALL RemoveAt(uint32_t) noexcept = 0;
            virtual int32_t WINRT_CALL Append(arg_in<T>) noexcept = 0;
            virtual int32_t WINRT_CALL RemoveAtEnd() noexcept = 0;
            virtual int32_t WINRT_CALL Clear() noexcept = 0;
            virtual int32_t WINRT_CALL GetMany(uint32_t, uint32_t, T*, uint32_t*) noexcept = 0;
            virtual int32_t WINRT_CALL ReplaceAll(uint32_t, T*) noexcept = 0;
        };
    };
    template <typename D, typename K, typename V>
    struct consume_Windows_Foundation_Collections_IObservableMap
    {
        winrt::event_token MapChanged(Windows::Foundation::Collections::MapChangedEventHandler<K, V> const& vhnd) const;
        using MapChanged_revoker = impl::event_revoker<Windows::Foundation::Collections::IObservableMap<K, V>, &impl::abi_t<Windows::Foundation::Collections::IObservableMap<K, V>>::remove_MapChanged>;
        MapChanged_revoker MapChanged(auto_revoke_t, Windows::Foundation::Collections::MapChangedEventHandler<K, V> const& vhnd) const;
        void MapChanged(winrt::event_token const& token) const noexcept;
    };
    template <typename K, typename V> struct consume<Windows::Foundation::Collections::IObservableMap<K, V>>
    {
        template <typename D> using type = consume_Windows_Foundation_Collections_IObservableMap<D, K, V>;
    };
    template <typename D, typename T>
    struct consume_Windows_Foundation_Collections_IObservableVector
    {
        winrt::event_token VectorChanged(Windows::Foundation::Collections::VectorChangedEventHandler<T> const& vhnd) const;
        using VectorChanged_revoker = impl::event_revoker<Windows::Foundation::Collections::IObservableVector<T>, &impl::abi_t<Windows::Foundation::Collections::IObservableVector<T>>::remove_VectorChanged>;
        VectorChanged_revoker VectorChanged(auto_revoke_t, Windows::Foundation::Collections::VectorChangedEventHandler<T> const& vhnd) const;
        void VectorChanged(winrt::event_token const& token) const noexcept;
    };
    template <typename T> struct consume<Windows::Foundation::Collections::IObservableVector<T>>
    {
        template <typename D> using type = consume_Windows_Foundation_Collections_IObservableVector<D, T>;
    };
    template <typename D>
    struct consume_Windows_Foundation_Collections_IPropertySet
    {
    };
    template <> struct consume<Windows::Foundation::Collections::IPropertySet>
    {
        template <typename D> using type = consume_Windows_Foundation_Collections_IPropertySet<D>;
    };
    template <typename D, typename T>
    struct consume_Windows_Foundation_Collections_IVector
    {
        T GetAt(uint32_t index) const;
        uint32_t Size() const;
        Windows::Foundation::Collections::IVectorView<T> GetView() const;
        bool IndexOf(T const& value, uint32_t& index) const;
        void SetAt(uint32_t index, T const& value) const;
        void InsertAt(uint32_t index, T const& value) const;
        void RemoveAt(uint32_t index) const;
        void Append(T const& value) const;
        void RemoveAtEnd() const;
        void Clear() const;
        uint32_t GetMany(uint32_t startIndex, array_view<T> items) const;
        void ReplaceAll(array_view<T const> items) const;
    };
    template <typename T> struct consume<Windows::Foundation::Collections::IVector<T>>
    {
        template <typename D> using type = consume_Windows_Foundation_Collections_IVector<D, T>;
    };
}
