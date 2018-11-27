﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/impl/Windows.Foundation.Collections.1.h"
namespace winrt::Windows::Foundation::Collections
{
    struct WINRT_EBO PropertySet : Windows::Foundation::Collections::IPropertySet
    {
        PropertySet(std::nullptr_t) noexcept {}
        PropertySet(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::Collections::IPropertySet(ptr, take_ownership_from_abi) {}
        PropertySet();
    };
    struct WINRT_EBO StringMap : Windows::Foundation::Collections::IMap<hstring, hstring>,
        impl::require<StringMap, Windows::Foundation::Collections::IObservableMap<hstring, hstring>>
    {
        StringMap(std::nullptr_t) noexcept {}
        StringMap(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::Collections::IMap<hstring, hstring>(ptr, take_ownership_from_abi) {}
        StringMap();
    };
    struct WINRT_EBO ValueSet : Windows::Foundation::Collections::IPropertySet
    {
        ValueSet(std::nullptr_t) noexcept {}
        ValueSet(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::Collections::IPropertySet(ptr, take_ownership_from_abi) {}
        ValueSet();
    };
}
namespace std
{
    template<typename T> struct hash<winrt::Windows::Foundation::Collections::IIterator<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IIterator<T>> {};
    template<typename T> struct hash<winrt::Windows::Foundation::Collections::IIterable<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IIterable<T>> {};
    template<typename T> struct hash<winrt::Windows::Foundation::Collections::IVectorView<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IVectorView<T>> {};
    template<typename T> struct hash<winrt::Windows::Foundation::Collections::VectorChangedEventHandler<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::VectorChangedEventHandler<T>> {};
    template<> struct hash<winrt::Windows::Foundation::Collections::IVectorChangedEventArgs> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IVectorChangedEventArgs> {};
    template<typename K, typename V> struct hash<winrt::Windows::Foundation::Collections::IKeyValuePair<K, V>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IKeyValuePair<K, V>> {};
    template<typename K, typename V> struct hash<winrt::Windows::Foundation::Collections::IMapView<K, V>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IMapView<K, V>> {};
    template<typename K, typename V> struct hash<winrt::Windows::Foundation::Collections::IMap<K, V>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IMap<K, V>> {};
    template<typename K, typename V> struct hash<winrt::Windows::Foundation::Collections::MapChangedEventHandler<K, V>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::MapChangedEventHandler<K, V>> {};
    template<typename K> struct hash<winrt::Windows::Foundation::Collections::IMapChangedEventArgs<K>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IMapChangedEventArgs<K>> {};
}
