﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/impl/Windows.Foundation.2.h"
#include "winrt/impl/Windows.Foundation.Collections.2.h"
#include "winrt/Windows.Foundation.h"
namespace winrt::impl
{
    template <typename D, typename T> Windows::Foundation::Collections::IIterator<T> consume_Windows_Foundation_Collections_IIterable<D, T>::First() const
    {
        Windows::Foundation::Collections::IIterator<T> winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IIterable<T>)->First(put_abi(winrt_impl_result)));
        return winrt_impl_result;
    }
    template <typename D, typename K, typename V> winrt::event_token consume_Windows_Foundation_Collections_IObservableMap<D, K, V>::MapChanged(Windows::Foundation::Collections::MapChangedEventHandler<K, V> const& vhnd) const
    {
        winrt::event_token winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IObservableMap<K, V>)->add_MapChanged(get_abi(vhnd), put_abi(winrt_impl_result)));
        return winrt_impl_result;
    }
    template <typename D, typename K, typename V> typename consume_Windows_Foundation_Collections_IObservableMap<D, K, V>::MapChanged_revoker consume_Windows_Foundation_Collections_IObservableMap<D, K, V>::MapChanged(auto_revoke_t, Windows::Foundation::Collections::MapChangedEventHandler<K, V> const& vhnd) const
    {
        return impl::make_event_revoker<D, MapChanged_revoker>(this, MapChanged(vhnd));
    }
    template <typename D, typename K, typename V> void consume_Windows_Foundation_Collections_IObservableMap<D, K, V>::MapChanged(winrt::event_token const& token) const noexcept
    {
        WINRT_VERIFY_(0, WINRT_SHIM(Windows::Foundation::Collections::IObservableMap<K, V>)->remove_MapChanged(get_abi(token)));
    }
    template <typename D, typename T> winrt::event_token consume_Windows_Foundation_Collections_IObservableVector<D, T>::VectorChanged(Windows::Foundation::Collections::VectorChangedEventHandler<T> const& vhnd) const
    {
        winrt::event_token winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IObservableVector<T>)->add_VectorChanged(get_abi(vhnd), put_abi(winrt_impl_result)));
        return winrt_impl_result;
    }
    template <typename D, typename T> typename consume_Windows_Foundation_Collections_IObservableVector<D, T>::VectorChanged_revoker consume_Windows_Foundation_Collections_IObservableVector<D, T>::VectorChanged(auto_revoke_t, Windows::Foundation::Collections::VectorChangedEventHandler<T> const& vhnd) const
    {
        return impl::make_event_revoker<D, VectorChanged_revoker>(this, VectorChanged(vhnd));
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IObservableVector<D, T>::VectorChanged(winrt::event_token const& token) const noexcept
    {
        WINRT_VERIFY_(0, WINRT_SHIM(Windows::Foundation::Collections::IObservableVector<T>)->remove_VectorChanged(get_abi(token)));
    }
    template <typename D, typename T> T consume_Windows_Foundation_Collections_IVector<D, T>::GetAt(uint32_t index) const
    {
        T winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->GetAt(index, put_abi(winrt_impl_result)));
        return winrt_impl_result;
    }
    template <typename D, typename T> uint32_t consume_Windows_Foundation_Collections_IVector<D, T>::Size() const
    {
        uint32_t winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->get_Size(&winrt_impl_result));
        return winrt_impl_result;
    }
    template <typename D, typename T> Windows::Foundation::Collections::IVectorView<T> consume_Windows_Foundation_Collections_IVector<D, T>::GetView() const
    {
        Windows::Foundation::Collections::IVectorView<T> winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->GetView(put_abi(winrt_impl_result)));
        return winrt_impl_result;
    }
    template <typename D, typename T> bool consume_Windows_Foundation_Collections_IVector<D, T>::IndexOf(T const& value, uint32_t& index) const
    {
        bool winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->IndexOf(get_abi(value), &index, &winrt_impl_result));
        return winrt_impl_result;
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IVector<D, T>::SetAt(uint32_t index, T const& value) const
    {
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->SetAt(index, get_abi(value)));
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IVector<D, T>::InsertAt(uint32_t index, T const& value) const
    {
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->InsertAt(index, get_abi(value)));
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IVector<D, T>::RemoveAt(uint32_t index) const
    {
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->RemoveAt(index));
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IVector<D, T>::Append(T const& value) const
    {
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->Append(get_abi(value)));
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IVector<D, T>::RemoveAtEnd() const
    {
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->RemoveAtEnd());
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IVector<D, T>::Clear() const
    {
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->Clear());
    }
    template <typename D, typename T> uint32_t consume_Windows_Foundation_Collections_IVector<D, T>::GetMany(uint32_t startIndex, array_view<T> items) const
    {
        uint32_t winrt_impl_result;
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->GetMany(startIndex, items.size(), get_abi(items), &winrt_impl_result));
        return winrt_impl_result;
    }
    template <typename D, typename T> void consume_Windows_Foundation_Collections_IVector<D, T>::ReplaceAll(array_view<T const> items) const
    {
        check_hresult(WINRT_SHIM(Windows::Foundation::Collections::IVector<T>)->ReplaceAll(items.size(), get_abi(items)));
    }
    template <typename D, typename T>
    struct produce<D, Windows::Foundation::Collections::IIterable<T>> : produce_base<D, Windows::Foundation::Collections::IIterable<T>>
    {
        int32_t WINRT_CALL First(void** winrt_impl_result) noexcept final
        {
            try
            {
                *winrt_impl_result = nullptr;
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<Windows::Foundation::Collections::IIterator<T>>(this->shim().First());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
    };
    template <typename D, typename K, typename V>
    struct produce<D, Windows::Foundation::Collections::IObservableMap<K, V>> : produce_base<D, Windows::Foundation::Collections::IObservableMap<K, V>>
    {
        int32_t WINRT_CALL add_MapChanged(void* vhnd, winrt::event_token* winrt_impl_result) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<winrt::event_token>(this->shim().MapChanged(*reinterpret_cast<Windows::Foundation::Collections::MapChangedEventHandler<K, V> const*>(&vhnd)));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL remove_MapChanged(winrt::event_token token) noexcept final
        {
            typename D::abi_guard guard(this->shim());
            this->shim().MapChanged(*reinterpret_cast<winrt::event_token const*>(&token));
            return 0;
        }
    };
    template <typename D, typename T>
    struct produce<D, Windows::Foundation::Collections::IObservableVector<T>> : produce_base<D, Windows::Foundation::Collections::IObservableVector<T>>
    {
        int32_t WINRT_CALL add_VectorChanged(void* vhnd, winrt::event_token* winrt_impl_result) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<winrt::event_token>(this->shim().VectorChanged(*reinterpret_cast<Windows::Foundation::Collections::VectorChangedEventHandler<T> const*>(&vhnd)));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL remove_VectorChanged(winrt::event_token token) noexcept final
        {
            typename D::abi_guard guard(this->shim());
            this->shim().VectorChanged(*reinterpret_cast<winrt::event_token const*>(&token));
            return 0;
        }
    };
    template <typename D>
    struct produce<D, Windows::Foundation::Collections::IPropertySet> : produce_base<D, Windows::Foundation::Collections::IPropertySet>
    {
    };
    template <typename D, typename T>
    struct produce<D, Windows::Foundation::Collections::IVector<T>> : produce_base<D, Windows::Foundation::Collections::IVector<T>>
    {
        int32_t WINRT_CALL GetAt(uint32_t index, arg_out<T> winrt_impl_result) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<T>(this->shim().GetAt(index));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL get_Size(uint32_t* winrt_impl_result) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<uint32_t>(this->shim().Size());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL GetView(void** winrt_impl_result) noexcept final
        {
            try
            {
                *winrt_impl_result = nullptr;
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<Windows::Foundation::Collections::IVectorView<T>>(this->shim().GetView());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL IndexOf(arg_in<T> value, uint32_t* index, bool* winrt_impl_result) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<bool>(this->shim().IndexOf(*reinterpret_cast<T const*>(&value), *index));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL SetAt(uint32_t index, arg_in<T> value) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                this->shim().SetAt(index, *reinterpret_cast<T const*>(&value));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL InsertAt(uint32_t index, arg_in<T> value) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                this->shim().InsertAt(index, *reinterpret_cast<T const*>(&value));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL RemoveAt(uint32_t index) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                this->shim().RemoveAt(index);
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL Append(arg_in<T> value) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                this->shim().Append(*reinterpret_cast<T const*>(&value));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL RemoveAtEnd() noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                this->shim().RemoveAtEnd();
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL Clear() noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                this->shim().Clear();
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL GetMany(uint32_t startIndex, uint32_t __itemsSize, arg_out<T> items, uint32_t* winrt_impl_result) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *winrt_impl_result = detach_from<uint32_t>(this->shim().GetMany(startIndex, array_view<T>(reinterpret_cast<T*>(items), reinterpret_cast<T*>(items) + __itemsSize)));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL ReplaceAll(uint32_t __itemsSize, arg_out<T> items) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                this->shim().ReplaceAll(array_view<T const>(reinterpret_cast<T const *>(items), reinterpret_cast<T const *>(items) + __itemsSize));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
    };
}
namespace winrt::Windows::Foundation::Collections
{
    inline PropertySet::PropertySet() :
        PropertySet(impl::call_factory<PropertySet>([](auto&& f) { return f.template ActivateInstance<PropertySet>(); }))
    {
    }
    inline StringMap::StringMap() :
        StringMap(impl::call_factory<StringMap>([](auto&& f) { return f.template ActivateInstance<StringMap>(); }))
    {
    }
    inline ValueSet::ValueSet() :
        ValueSet(impl::call_factory<ValueSet>([](auto&& f) { return f.template ActivateInstance<ValueSet>(); }))
    {
    }
}
namespace std
{
    template<typename T> struct hash<winrt::Windows::Foundation::Collections::IIterable<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IIterable<T>> {};
    template<typename K, typename V> struct hash<winrt::Windows::Foundation::Collections::IObservableMap<K, V>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IObservableMap<K, V>> {};
    template<typename T> struct hash<winrt::Windows::Foundation::Collections::IObservableVector<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IObservableVector<T>> {};
    template<> struct hash<winrt::Windows::Foundation::Collections::IPropertySet> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IPropertySet> {};
    template<typename T> struct hash<winrt::Windows::Foundation::Collections::IVector<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::IVector<T>> {};
    template<> struct hash<winrt::Windows::Foundation::Collections::PropertySet> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::PropertySet> {};
    template<> struct hash<winrt::Windows::Foundation::Collections::StringMap> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::StringMap> {};
    template<> struct hash<winrt::Windows::Foundation::Collections::ValueSet> : winrt::impl::hash_base<winrt::Windows::Foundation::Collections::ValueSet> {};
}
