﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#ifndef WINRT_HEADER_Component_Params_0
#define WINRT_HEADER_Component_Params_0
#include "winrt/base.h"
namespace winrt::Component::Structs
{
    struct Simple;
}
namespace winrt::Windows::Foundation
{
    struct IAsyncAction;
    template <typename T> struct IReference;
}
namespace winrt::Windows::Foundation::Collections
{
    template <typename T> struct IIterable;
    template <typename K, typename V> struct IMapView;
    template <typename K, typename V> struct IMap;
    template <typename T> struct IVectorView;
    template <typename T> struct IVector;
}
namespace winrt::Component::Params
{
    struct IClass;
    struct Class;
}
namespace winrt::impl
{
    template <> struct category<Component::Params::IClass>
    {
        using type = interface_category;
    };
    template <> struct category<Component::Params::Class>
    {
        using type = class_category;
    };
    template <> struct name<Component::Params::IClass>
    {
        static constexpr auto & value{ L"Component.Params.IClass" };
    };
    template <> struct name<Component::Params::Class>
    {
        static constexpr auto & value{ L"Component.Params.Class" };
    };
    template <> struct guid_storage<Component::Params::IClass>
    {
        static constexpr guid value{ 0x42070967,0x0C73,0x548C,{ 0x8B,0x37,0xDC,0x93,0x2E,0x0F,0x81,0xD0 } };
    };
    template <> struct default_interface<Component::Params::Class>
    {
        using type = Component::Params::IClass;
    };
    template <> struct abi<Component::Params::IClass>
    {
        struct type : inspectable_abi
        {
            virtual int32_t WINRT_CALL SyncCall(void*, void*, void*, void*, void*, void*, void*) noexcept = 0;
            virtual int32_t WINRT_CALL NotSyncCall(void*, void*, void*, void*, void*, void*, void*, void**) noexcept = 0;
            virtual int32_t WINRT_CALL Structs(struct struct_Component_Structs_Simple, struct struct_Component_Structs_Simple*, struct struct_Component_Structs_Simple*) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Component_Params_IClass
    {
        void SyncCall(param::hstring const& a, Windows::Foundation::IReference<int32_t> const& b, param::iterable<int32_t> const& c, param::vector_view<int32_t> const& d, param::map_view<int32_t, int32_t> const& e, param::vector<int32_t> const& f, param::map<int32_t, int32_t> const& g) const;
        Windows::Foundation::IAsyncAction NotSyncCall(param::hstring const& a, Windows::Foundation::IReference<int32_t> const& b, param::iterable<int32_t> const& c, param::vector_view<int32_t> const& d, param::map_view<int32_t, int32_t> const& e, param::vector<int32_t> const& f, param::map<int32_t, int32_t> const& g) const;
        Component::Structs::Simple Structs(Component::Structs::Simple const& a, Component::Structs::Simple& b) const;
    };
    template <> struct consume<Component::Params::IClass>
    {
        template <typename D> using type = consume_Component_Params_IClass<D>;
    };
}
#endif
