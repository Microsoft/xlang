﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#ifndef WINRT_Component_Events_H
#define WINRT_Component_Events_H
#include "winrt/base.h"
static_assert(winrt::check_version(CPPWINRT_VERSION, "2.0.000000.0"), "Mismatched component and base headers.");
#include "winrt/impl/Windows.Foundation.2.h"
#include "winrt/impl/Component.Events.2.h"
#include "winrt/Component.h"
namespace winrt::impl
{
    template <typename D> winrt::event_token consume_Component_Events_IClass<D>::Member(Component::Events::Handler const& handler) const
    {
        winrt::event_token token;
        check_hresult(WINRT_SHIM(Component::Events::IClass)->add_Member(get_abi(handler), put_abi(token)));
        return token;
    }
    template <typename D> typename consume_Component_Events_IClass<D>::Member_revoker consume_Component_Events_IClass<D>::Member(auto_revoke_t, Component::Events::Handler const& handler) const
    {
        return impl::make_event_revoker<D, Member_revoker>(this, Member(handler));
    }
    template <typename D> void consume_Component_Events_IClass<D>::Member(winrt::event_token const& token) const noexcept
    {
        WINRT_VERIFY_(0, WINRT_SHIM(Component::Events::IClass)->remove_Member(get_abi(token)));
    }
    template <typename D> winrt::event_token consume_Component_Events_IClassStatics<D>::Static(Component::Events::Handler const& handler) const
    {
        winrt::event_token token;
        check_hresult(WINRT_SHIM(Component::Events::IClassStatics)->add_Static(get_abi(handler), put_abi(token)));
        return token;
    }
    template <typename D> typename consume_Component_Events_IClassStatics<D>::Static_revoker consume_Component_Events_IClassStatics<D>::Static(auto_revoke_t, Component::Events::Handler const& handler) const
    {
        return impl::make_event_revoker<D, Static_revoker>(this, Static(handler));
    }
    template <typename D> void consume_Component_Events_IClassStatics<D>::Static(winrt::event_token const& token) const noexcept
    {
        WINRT_VERIFY_(0, WINRT_SHIM(Component::Events::IClassStatics)->remove_Static(get_abi(token)));
    }
    template <> struct delegate<Component::Events::Handler>
    {
        template <typename H>
        struct type : implements_delegate<Component::Events::Handler, H>
        {
            type(H&& handler) : implements_delegate<Component::Events::Handler, H>(std::forward<H>(handler)) {}

            int32_t WINRT_CALL Invoke(int32_t value) noexcept final
            {
                try
                {
                    (*this)(value);
                    return 0;
                }
                catch (...)
                {
                    return to_hresult();
                }
            }
        };
    };
    template <typename D>
    struct produce<D, Component::Events::IClass> : produce_base<D, Component::Events::IClass>
    {
        int32_t WINRT_CALL add_Member(void* handler, winrt::event_token* token) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *token = detach_from<winrt::event_token>(this->shim().Member(*reinterpret_cast<Component::Events::Handler const*>(&handler)));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL remove_Member(winrt::event_token token) noexcept final
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Member(*reinterpret_cast<winrt::event_token const*>(&token));
            return 0;
        }
    };
    template <typename D>
    struct produce<D, Component::Events::IClassStatics> : produce_base<D, Component::Events::IClassStatics>
    {
        int32_t WINRT_CALL add_Static(void* handler, winrt::event_token* token) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *token = detach_from<winrt::event_token>(this->shim().Static(*reinterpret_cast<Component::Events::Handler const*>(&handler)));
                return 0;
            }
            catch (...) { return to_hresult(); }
        }
        int32_t WINRT_CALL remove_Static(winrt::event_token token) noexcept final
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Static(*reinterpret_cast<winrt::event_token const*>(&token));
            return 0;
        }
    };
}
namespace winrt::Component::Events
{
    inline Class::Class() :
        Class(impl::call_factory<Class>([](auto&& f) { return f.template ActivateInstance<Class>(); }))
    {
    }
    inline winrt::event_token Class::Static(Component::Events::Handler const& handler)
    {
        return impl::call_factory<Class, Component::Events::IClassStatics>([&](auto&& f) { return f.Static(handler); });
    }
    inline Class::Static_revoker Class::Static(auto_revoke_t, Component::Events::Handler const& handler)
    {
        auto f = get_activation_factory<Class, Component::Events::IClassStatics>();
        return { f, f.Static(handler) };
    }
    inline void Class::Static(winrt::event_token const& token)
    {
        impl::call_factory<Class, Component::Events::IClassStatics>([&](auto&& f) { return f.Static(token); });
    }
    template <typename L> Handler::Handler(L handler) :
        Handler(impl::make_delegate<Handler>(std::forward<L>(handler)))
    {
    }
    template <typename F> Handler::Handler(F* handler) :
        Handler([=](auto&&... args) { return handler(args...); })
    {
    }
    template <typename O, typename M> Handler::Handler(O* object, M method) :
        Handler([=](auto&&... args) { return ((*object).*(method))(args...); })
    {
    }
    template <typename O, typename M> Handler::Handler(com_ptr<O>&& object, M method) :
        Handler([o = std::move(object), method](auto&&... args) { return ((*o).*(method))(args...); })
    {
    }
    template <typename O, typename M> Handler::Handler(weak_ref<O>&& object, M method) :
        Handler([o = std::move(object), method](auto&&... args) { if (auto s = o.get()) { ((*s).*(method))(args...); } })
    {
    }
    inline void Handler::operator()(int32_t value) const
    {
        check_hresult((*(impl::abi_t<Handler>**)this)->Invoke(value));
    }
}
namespace std
{
    template<> struct hash<winrt::Component::Events::IClass> : winrt::impl::hash_base<winrt::Component::Events::IClass> {};
    template<> struct hash<winrt::Component::Events::IClassStatics> : winrt::impl::hash_base<winrt::Component::Events::IClassStatics> {};
    template<> struct hash<winrt::Component::Events::Class> : winrt::impl::hash_base<winrt::Component::Events::Class> {};
}
#endif
