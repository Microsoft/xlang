﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/impl/Windows.Foundation.Collections.2.h"
#include "winrt/impl/Component.Collections.2.h"
#include "winrt/Component.h"
namespace winrt::impl
{
    template <typename D> Windows::Foundation::Collections::IIterable<hstring> consume_Component_Collections_IClassStatics<D>::Iterable() const
    {
        void* result;
        check_hresult(WINRT_SHIM(Component::Collections::IClassStatics)->Iterable(&result));
        return { result, take_ownership_from_abi };
    }
    template <typename D> Windows::Foundation::Collections::IVectorView<hstring> consume_Component_Collections_IClassStatics<D>::VectorView() const
    {
        void* result;
        check_hresult(WINRT_SHIM(Component::Collections::IClassStatics)->VectorView(&result));
        return { result, take_ownership_from_abi };
    }
    template <typename D> Windows::Foundation::Collections::IVector<hstring> consume_Component_Collections_IClassStatics<D>::Vector() const
    {
        void* result;
        check_hresult(WINRT_SHIM(Component::Collections::IClassStatics)->Vector(&result));
        return { result, take_ownership_from_abi };
    }
    template <typename D> Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<hstring, int32_t>> consume_Component_Collections_IClassStatics<D>::IterablePair() const
    {
        void* result;
        check_hresult(WINRT_SHIM(Component::Collections::IClassStatics)->IterablePair(&result));
        return { result, take_ownership_from_abi };
    }
    template <typename D> Windows::Foundation::Collections::IMapView<hstring, int32_t> consume_Component_Collections_IClassStatics<D>::MapView() const
    {
        void* result;
        check_hresult(WINRT_SHIM(Component::Collections::IClassStatics)->MapView(&result));
        return { result, take_ownership_from_abi };
    }
    template <typename D> Windows::Foundation::Collections::IMap<hstring, int32_t> consume_Component_Collections_IClassStatics<D>::Map() const
    {
        void* result;
        check_hresult(WINRT_SHIM(Component::Collections::IClassStatics)->Map(&result));
        return { result, take_ownership_from_abi };
    }
    template <typename D>
    struct produce<D, Component::Collections::IClass> : produce_base<D, Component::Collections::IClass>
    {
    };
    template <typename D>
    struct produce<D, Component::Collections::IClassStatics> : produce_base<D, Component::Collections::IClassStatics>
    {
        int32_t WINRT_CALL Iterable(void** result) noexcept final
        {
            try
            {
                *result = nullptr;
                typename D::abi_guard guard(this->shim());
                *result = detach_from<Windows::Foundation::Collections::IIterable<hstring>>(this->shim().Iterable());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL VectorView(void** result) noexcept final
        {
            try
            {
                *result = nullptr;
                typename D::abi_guard guard(this->shim());
                *result = detach_from<Windows::Foundation::Collections::IVectorView<hstring>>(this->shim().VectorView());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL Vector(void** result) noexcept final
        {
            try
            {
                *result = nullptr;
                typename D::abi_guard guard(this->shim());
                *result = detach_from<Windows::Foundation::Collections::IVector<hstring>>(this->shim().Vector());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL IterablePair(void** result) noexcept final
        {
            try
            {
                *result = nullptr;
                typename D::abi_guard guard(this->shim());
                *result = detach_from<Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<hstring, int32_t>>>(this->shim().IterablePair());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL MapView(void** result) noexcept final
        {
            try
            {
                *result = nullptr;
                typename D::abi_guard guard(this->shim());
                *result = detach_from<Windows::Foundation::Collections::IMapView<hstring, int32_t>>(this->shim().MapView());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL Map(void** result) noexcept final
        {
            try
            {
                *result = nullptr;
                typename D::abi_guard guard(this->shim());
                *result = detach_from<Windows::Foundation::Collections::IMap<hstring, int32_t>>(this->shim().Map());
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
    };
}
namespace winrt::Component::Collections
{
    inline Windows::Foundation::Collections::IIterable<hstring> Class::Iterable()
    {
        return impl::call_factory<Class, Component::Collections::IClassStatics>([&](auto&& f) { return f.Iterable(); });
    }
    inline Windows::Foundation::Collections::IVectorView<hstring> Class::VectorView()
    {
        return impl::call_factory<Class, Component::Collections::IClassStatics>([&](auto&& f) { return f.VectorView(); });
    }
    inline Windows::Foundation::Collections::IVector<hstring> Class::Vector()
    {
        return impl::call_factory<Class, Component::Collections::IClassStatics>([&](auto&& f) { return f.Vector(); });
    }
    inline Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<hstring, int32_t>> Class::IterablePair()
    {
        return impl::call_factory<Class, Component::Collections::IClassStatics>([&](auto&& f) { return f.IterablePair(); });
    }
    inline Windows::Foundation::Collections::IMapView<hstring, int32_t> Class::MapView()
    {
        return impl::call_factory<Class, Component::Collections::IClassStatics>([&](auto&& f) { return f.MapView(); });
    }
    inline Windows::Foundation::Collections::IMap<hstring, int32_t> Class::Map()
    {
        return impl::call_factory<Class, Component::Collections::IClassStatics>([&](auto&& f) { return f.Map(); });
    }
    inline Class::Class() :
        Class(impl::call_factory<Class>([](auto&& f) { return f.template ActivateInstance<Class>(); }))
    {
    }
}
namespace std
{
    template<> struct hash<winrt::Component::Collections::IClass> : winrt::impl::hash_base<winrt::Component::Collections::IClass> {};
    template<> struct hash<winrt::Component::Collections::IClassStatics> : winrt::impl::hash_base<winrt::Component::Collections::IClassStatics> {};
    template<> struct hash<winrt::Component::Collections::Class> : winrt::impl::hash_base<winrt::Component::Collections::Class> {};
}
