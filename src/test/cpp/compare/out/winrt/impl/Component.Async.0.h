﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#ifndef WINRT_HEADER_Component_Async_0
#define WINRT_HEADER_Component_Async_0
#include "winrt/base.h"
namespace winrt::Windows::Foundation
{
    struct IAsyncAction;
    template <typename TProgress> struct IAsyncActionWithProgress;
    template <typename TResult, typename TProgress> struct IAsyncOperationWithProgress;
    template <typename TResult> struct IAsyncOperation;
}
namespace winrt::Component::Async
{
    struct IClassStatics;
    struct Class;
}
namespace winrt::impl
{
    template <> struct category<Component::Async::IClassStatics>
    {
        using type = interface_category;
    };
    template <> struct category<Component::Async::Class>
    {
        using type = class_category;
    };
    template <> struct name<Component::Async::IClassStatics>
    {
        static constexpr auto & value{ L"Component.Async.IClassStatics" };
    };
    template <> struct name<Component::Async::Class>
    {
        static constexpr auto & value{ L"Component.Async.Class" };
    };
    template <> struct guid_storage<Component::Async::IClassStatics>
    {
        static constexpr guid value{ 0x2CDA5F40,0x9F27,0x5847,{ 0x9A,0xDE,0x36,0xF3,0x55,0x10,0xF9,0x64 } };
    };
    template <> struct abi<Component::Async::IClassStatics>
    {
        struct type : inspectable_abi
        {
            virtual int32_t WINRT_CALL Action(void**) noexcept = 0;
            virtual int32_t WINRT_CALL ActionWithProgress(void**) noexcept = 0;
            virtual int32_t WINRT_CALL Operation(void**) noexcept = 0;
            virtual int32_t WINRT_CALL OperationWithProgress(void**) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Component_Async_IClassStatics
    {
        Windows::Foundation::IAsyncAction Action() const;
        Windows::Foundation::IAsyncActionWithProgress<int32_t> ActionWithProgress() const;
        Windows::Foundation::IAsyncOperation<hstring> Operation() const;
        Windows::Foundation::IAsyncOperationWithProgress<hstring, int32_t> OperationWithProgress() const;
    };
    template <> struct consume<Component::Async::IClassStatics>
    {
        template <typename D> using type = consume_Component_Async_IClassStatics<D>;
    };
}
#endif
