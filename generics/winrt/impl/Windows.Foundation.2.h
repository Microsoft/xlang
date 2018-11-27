﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/impl/Windows.Foundation.1.h"
namespace winrt::Windows::Foundation
{
    struct DeferralCompletedHandler : Windows::Foundation::IUnknown
    {
        DeferralCompletedHandler(std::nullptr_t = nullptr) noexcept {}
        DeferralCompletedHandler(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> DeferralCompletedHandler(L lambda);
        template <typename F> DeferralCompletedHandler(F* function);
        template <typename O, typename M> DeferralCompletedHandler(O* object, M method);
        template <typename O, typename M> DeferralCompletedHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> DeferralCompletedHandler(weak_ref<O>&& object, M method);
        void operator()() const;
    };
    struct WINRT_EBO Deferral : Windows::Foundation::IDeferral
    {
        Deferral(std::nullptr_t) noexcept {}
        Deferral(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IDeferral(ptr, take_ownership_from_abi) {}
        Deferral(Windows::Foundation::DeferralCompletedHandler const& handler);
    };
    struct WINRT_EBO MemoryBuffer : Windows::Foundation::IMemoryBuffer
    {
        MemoryBuffer(std::nullptr_t) noexcept {}
        MemoryBuffer(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IMemoryBuffer(ptr, take_ownership_from_abi) {}
        MemoryBuffer(uint32_t capacity);
    };
    struct PropertyValue
    {
        PropertyValue() = delete;
        static Windows::Foundation::IInspectable CreateEmpty();
        static Windows::Foundation::IInspectable CreateUInt8(uint8_t value);
        static Windows::Foundation::IInspectable CreateInt16(int16_t value);
        static Windows::Foundation::IInspectable CreateUInt16(uint16_t value);
        static Windows::Foundation::IInspectable CreateInt32(int32_t value);
        static Windows::Foundation::IInspectable CreateUInt32(uint32_t value);
        static Windows::Foundation::IInspectable CreateInt64(int64_t value);
        static Windows::Foundation::IInspectable CreateUInt64(uint64_t value);
        static Windows::Foundation::IInspectable CreateSingle(float value);
        static Windows::Foundation::IInspectable CreateDouble(double value);
        static Windows::Foundation::IInspectable CreateChar16(char16_t value);
        static Windows::Foundation::IInspectable CreateBoolean(bool value);
        static Windows::Foundation::IInspectable CreateString(param::hstring const& value);
        static Windows::Foundation::IInspectable CreateInspectable(Windows::Foundation::IInspectable const& value);
        static Windows::Foundation::IInspectable CreateGuid(winrt::guid const& value);
        static Windows::Foundation::IInspectable CreateDateTime(Windows::Foundation::DateTime const& value);
        static Windows::Foundation::IInspectable CreateTimeSpan(Windows::Foundation::TimeSpan const& value);
        static Windows::Foundation::IInspectable CreatePoint(Windows::Foundation::Point const& value);
        static Windows::Foundation::IInspectable CreateSize(Windows::Foundation::Size const& value);
        static Windows::Foundation::IInspectable CreateRect(Windows::Foundation::Rect const& value);
        static Windows::Foundation::IInspectable CreateUInt8Array(array_view<uint8_t const> value);
        static Windows::Foundation::IInspectable CreateInt16Array(array_view<int16_t const> value);
        static Windows::Foundation::IInspectable CreateUInt16Array(array_view<uint16_t const> value);
        static Windows::Foundation::IInspectable CreateInt32Array(array_view<int32_t const> value);
        static Windows::Foundation::IInspectable CreateUInt32Array(array_view<uint32_t const> value);
        static Windows::Foundation::IInspectable CreateInt64Array(array_view<int64_t const> value);
        static Windows::Foundation::IInspectable CreateUInt64Array(array_view<uint64_t const> value);
        static Windows::Foundation::IInspectable CreateSingleArray(array_view<float const> value);
        static Windows::Foundation::IInspectable CreateDoubleArray(array_view<double const> value);
        static Windows::Foundation::IInspectable CreateChar16Array(array_view<char16_t const> value);
        static Windows::Foundation::IInspectable CreateBooleanArray(array_view<bool const> value);
        static Windows::Foundation::IInspectable CreateStringArray(array_view<hstring const> value);
        static Windows::Foundation::IInspectable CreateInspectableArray(array_view<Windows::Foundation::IInspectable const> value);
        static Windows::Foundation::IInspectable CreateGuidArray(array_view<winrt::guid const> value);
        static Windows::Foundation::IInspectable CreateDateTimeArray(array_view<Windows::Foundation::DateTime const> value);
        static Windows::Foundation::IInspectable CreateTimeSpanArray(array_view<Windows::Foundation::TimeSpan const> value);
        static Windows::Foundation::IInspectable CreatePointArray(array_view<Windows::Foundation::Point const> value);
        static Windows::Foundation::IInspectable CreateSizeArray(array_view<Windows::Foundation::Size const> value);
        static Windows::Foundation::IInspectable CreateRectArray(array_view<Windows::Foundation::Rect const> value);
    };
    struct WINRT_EBO Uri : Windows::Foundation::IUriRuntimeClass,
        impl::require<Uri, Windows::Foundation::IStringable, Windows::Foundation::IUriRuntimeClassWithAbsoluteCanonicalUri>
    {
        Uri(std::nullptr_t) noexcept {}
        Uri(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUriRuntimeClass(ptr, take_ownership_from_abi) {}
        Uri(param::hstring const& uri);
        Uri(param::hstring const& baseUri, param::hstring const& relativeUri);
        static hstring UnescapeComponent(param::hstring const& toUnescape);
        static hstring EscapeComponent(param::hstring const& toEscape);
    };
    struct WINRT_EBO WwwFormUrlDecoder : Windows::Foundation::IWwwFormUrlDecoderRuntimeClass
    {
        WwwFormUrlDecoder(std::nullptr_t) noexcept {}
        WwwFormUrlDecoder(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IWwwFormUrlDecoderRuntimeClass(ptr, take_ownership_from_abi) {}
        WwwFormUrlDecoder(param::hstring const& query);
    };
    struct WINRT_EBO WwwFormUrlDecoderEntry : Windows::Foundation::IWwwFormUrlDecoderEntry
    {
        WwwFormUrlDecoderEntry(std::nullptr_t) noexcept {}
        WwwFormUrlDecoderEntry(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IWwwFormUrlDecoderEntry(ptr, take_ownership_from_abi) {}
    };
}

namespace winrt::impl
{
    template <typename D, typename T>
    struct produce<D, Windows::Foundation::IReference<T>> : produce_base<D, Windows::Foundation::IReference<T>>
    {
        int32_t WINRT_CALL get_Value(arg_out<T> value) noexcept final
        {
            try
            {
                typename D::abi_guard guard(this->shim());
                *value = detach_from<T>(this->shim().Value());
                return error_ok;
            }
            catch (...) { return to_hresult(); }
        }
    };

    template <typename D, typename T>
    struct produce<D, Windows::Foundation::IReferenceArray<T>> : produce_base<D, Windows::Foundation::IReferenceArray<T>>
    {
        int32_t WINRT_CALL get_Value(uint32_t* __valueSize, arg_out<T>* value) noexcept final
        {
            try
            {
                *__valueSize = 0;
                *value = nullptr;
                typename D::abi_guard guard(this->shim());
                std::tie(*__valueSize, *value) = detach_abi(this->shim().Value());
                return error_ok;
            }
            catch (...) { return to_hresult(); }
        }
    };

    template <typename T>
    struct reference final : implements<reference<T>, Windows::Foundation::IReference<T>, Windows::Foundation::IPropertyValue>
    {
        reference(T const& value) : m_value(value)
        {
        }

        T Value() const
        {
            return m_value;
        }

        Windows::Foundation::PropertyType Type() const noexcept
        {
            return Windows::Foundation::PropertyType::OtherType;
        }

        static constexpr bool IsNumericScalar() noexcept
        {
            return std::is_arithmetic_v<T> || std::is_enum_v<T>;
        }

        uint8_t GetUInt8() const
        {
            return to_scalar<uint8_t>();
        }

        int16_t GetInt16() const
        {
            return to_scalar<int16_t>();
        }

        uint16_t GetUInt16() const
        {
            return to_scalar<uint16_t>();
        }

        int32_t GetInt32() const
        {
            return to_scalar<int32_t>();
        }

        uint32_t GetUInt32() const
        {
            return to_scalar<uint32_t>();
        }

        int64_t GetInt64() const
        {
            return to_scalar<int64_t>();
        }

        uint64_t GetUInt64() const
        {
            return to_scalar<uint64_t>();
        }

        float GetSingle() { throw hresult_not_implemented(); }
        double GetDouble() { throw hresult_not_implemented(); }
        char16_t GetChar16() { throw hresult_not_implemented(); }
        bool GetBoolean() { throw hresult_not_implemented(); }
        hstring GetString() { throw hresult_not_implemented(); }
        guid GetGuid() { throw hresult_not_implemented(); }
        Windows::Foundation::DateTime GetDateTime() { throw hresult_not_implemented(); }
        Windows::Foundation::TimeSpan GetTimeSpan() { throw hresult_not_implemented(); }
        Windows::Foundation::Point GetPoint() { throw hresult_not_implemented(); }
        Windows::Foundation::Size GetSize() { throw hresult_not_implemented(); }
        Windows::Foundation::Rect GetRect() { throw hresult_not_implemented(); }
        void GetUInt8Array(com_array<uint8_t> &) { throw hresult_not_implemented(); }
        void GetInt16Array(com_array<int16_t> &) { throw hresult_not_implemented(); }
        void GetUInt16Array(com_array<uint16_t> &) { throw hresult_not_implemented(); }
        void GetInt32Array(com_array<int32_t> &) { throw hresult_not_implemented(); }
        void GetUInt32Array(com_array<uint32_t> &) { throw hresult_not_implemented(); }
        void GetInt64Array(com_array<int64_t> &) { throw hresult_not_implemented(); }
        void GetUInt64Array(com_array<uint64_t> &) { throw hresult_not_implemented(); }
        void GetSingleArray(com_array<float> &) { throw hresult_not_implemented(); }
        void GetDoubleArray(com_array<double> &) { throw hresult_not_implemented(); }
        void GetChar16Array(com_array<char16_t> &) { throw hresult_not_implemented(); }
        void GetBooleanArray(com_array<bool> &) { throw hresult_not_implemented(); }
        void GetStringArray(com_array<hstring> &) { throw hresult_not_implemented(); }
        void GetInspectableArray(com_array<Windows::Foundation::IInspectable> &) { throw hresult_not_implemented(); }
        void GetGuidArray(com_array<guid> &) { throw hresult_not_implemented(); }
        void GetDateTimeArray(com_array<Windows::Foundation::DateTime> &) { throw hresult_not_implemented(); }
        void GetTimeSpanArray(com_array<Windows::Foundation::TimeSpan> &) { throw hresult_not_implemented(); }
        void GetPointArray(com_array<Windows::Foundation::Point> &) { throw hresult_not_implemented(); }
        void GetSizeArray(com_array<Windows::Foundation::Size> &) { throw hresult_not_implemented(); }
        void GetRectArray(com_array<Windows::Foundation::Rect> &) { throw hresult_not_implemented(); }

    private:

        template <typename To>
        To to_scalar() const
        {
            if constexpr (IsNumericScalar())
            {
                return static_cast<To>(m_value);
            }
            else
            {
                throw hresult_not_implemented();
            }
        }

        T m_value;
    };

    template <typename T>
    struct reference_traits
    {
        static auto make(T const& value) { return winrt::make<impl::reference<T>>(value); }
    };

    template <>
    struct reference_traits<uint8_t>
    {
        static auto make(uint8_t value) { return Windows::Foundation::PropertyValue::CreateUInt8(value); }
    };

    template <>
    struct reference_traits<uint16_t>
    {
        static auto make(uint16_t value) { return Windows::Foundation::PropertyValue::CreateUInt16(value); }
    };

    template <>
    struct reference_traits<int16_t>
    {
        static auto make(int16_t value) { return Windows::Foundation::PropertyValue::CreateInt16(value); }
    };

    template <>
    struct reference_traits<uint32_t>
    {
        static auto make(uint32_t value) { return Windows::Foundation::PropertyValue::CreateUInt32(value); }
    };

    template <>
    struct reference_traits<int32_t>
    {
        static auto make(int32_t value) { return Windows::Foundation::PropertyValue::CreateInt32(value); }
    };

    template <>
    struct reference_traits<uint64_t>
    {
        static auto make(uint64_t value) { return Windows::Foundation::PropertyValue::CreateUInt64(value); }
    };

    template <>
    struct reference_traits<int64_t>
    {
        static auto make(int64_t value) { return Windows::Foundation::PropertyValue::CreateInt64(value); }
    };

    template <>
    struct reference_traits<float>
    {
        static auto make(float value) { return Windows::Foundation::PropertyValue::CreateSingle(value); }
    };

    template <>
    struct reference_traits<double>
    {
        static auto make(double value) { return Windows::Foundation::PropertyValue::CreateDouble(value); }
    };

    template <>
    struct reference_traits<char16_t>
    {
        static auto make(char16_t value) { return Windows::Foundation::PropertyValue::CreateChar16(value); }
    };

    template <>
    struct reference_traits<bool>
    {
        static auto make(bool value) { return Windows::Foundation::PropertyValue::CreateBoolean(value); }
    };

    template <>
    struct reference_traits<hstring>
    {
        static auto make(hstring const& value) { return Windows::Foundation::PropertyValue::CreateString(value); }
    };

    template <>
    struct reference_traits<Windows::Foundation::IInspectable>
    {
        static auto make(Windows::Foundation::IInspectable const& value) { return Windows::Foundation::PropertyValue::CreateInspectable(value); }
    };

    template <>
    struct reference_traits<guid>
    {
        static auto make(guid const& value) { return Windows::Foundation::PropertyValue::CreateGuid(value); }
    };

    template <>
    struct reference_traits<Windows::Foundation::DateTime>
    {
        static auto make(Windows::Foundation::DateTime value) { return Windows::Foundation::PropertyValue::CreateDateTime(value); }
    };

    template <>
    struct reference_traits<Windows::Foundation::TimeSpan>
    {
        static auto make(Windows::Foundation::TimeSpan value) { return Windows::Foundation::PropertyValue::CreateTimeSpan(value); }
    };

    template <>
    struct reference_traits<Windows::Foundation::Point>
    {
        static auto make(Windows::Foundation::Point const& value) { return Windows::Foundation::PropertyValue::CreatePoint(value); }
    };

    template <>
    struct reference_traits<Windows::Foundation::Size>
    {
        static auto make(Windows::Foundation::Size const& value) { return Windows::Foundation::PropertyValue::CreateSize(value); }
    };

    template <>
    struct reference_traits<Windows::Foundation::Rect>
    {
        static auto make(Windows::Foundation::Rect const& value) { return Windows::Foundation::PropertyValue::CreateRect(value); }
    };
}

WINRT_EXPORT namespace winrt::Windows::Foundation
{
    template <typename T>
    struct IReference :
        IInspectable,
        impl::consume_t<IReference<T>>,
        impl::require<IReference<T>, IPropertyValue>
    {
        static_assert(impl::has_category_v<T>, "T must be WinRT type.");
        IReference(std::nullptr_t = nullptr) noexcept {}
        IReference(void* ptr, take_ownership_from_abi_t) noexcept : IInspectable(ptr, take_ownership_from_abi) {}

        IReference(T const& value) : IReference<T>(impl::reference_traits<T>::make(value))
        {
        }

    private:

        IReference<T>(IInspectable const& value) : IReference<T>(value.as<IReference<T>>())
        {
        }
    };

    template <typename T>
    bool operator==(IReference<T> const& left, IReference<T> const& right)
    {
        if (get_abi(left) == get_abi(right))
        {
            return true;
        }

        if (!left || !right)
        {
            return false;
        }

        return left.Value() == right.Value();
    }

    template <typename T>
    bool operator!=(IReference<T> const& left, IReference<T> const& right)
    {
        return !(left == right);
    }

    template <typename T>
    struct WINRT_EBO IReferenceArray :
        IInspectable,
        impl::consume_t<IReferenceArray<T>>,
        impl::require<IReferenceArray<T>, IPropertyValue>
    {
        static_assert(impl::has_category_v<T>, "T must be WinRT type.");
        IReferenceArray<T>(std::nullptr_t = nullptr) noexcept {}
        IReferenceArray(void* ptr, take_ownership_from_abi_t) noexcept : IInspectable(ptr, take_ownership_from_abi) {}
    };
}

WINRT_EXPORT namespace winrt
{
    inline Windows::Foundation::IInspectable box_value(param::hstring const& value)
    {
        return Windows::Foundation::IReference<hstring>(*(hstring*)(&value));
    }

    template <typename T, typename = std::enable_if_t<!std::is_convertible_v<T, param::hstring>>>
    Windows::Foundation::IInspectable box_value(T const& value)
    {
        if constexpr (std::is_base_of_v<Windows::Foundation::IInspectable, T>)
        {
            return value;
        }
        else
        {
            return Windows::Foundation::IReference<T>(value);
        }
    }

    template <typename T>
    T unbox_value(Windows::Foundation::IInspectable const& value)
    {
        if constexpr (std::is_base_of_v<Windows::Foundation::IInspectable, T>)
        {
            return value.as<T>();
        }
        else if constexpr (std::is_enum_v<T>)
        {
            if (auto temp = value.try_as<Windows::Foundation::IReference<T>>())
            {
                return temp.Value();
            }
            else
            {
                return static_cast<T>(value.as<Windows::Foundation::IReference<std::underlying_type_t<T>>>().Value());
            }
        }
        else
        {
            return value.as<Windows::Foundation::IReference<T>>().Value();
        }
    }

    template <typename T>
    hstring unbox_value_or(Windows::Foundation::IInspectable const& value, param::hstring const& default_value)
    {
        if (value)
        {
            if (auto temp = value.try_as<Windows::Foundation::IReference<hstring>>())
            {
                return temp.Value();
            }
        }

        return *(hstring*)(&default_value);
    }

    template <typename T, typename = std::enable_if_t<!std::is_same_v<T, hstring>>>
    T unbox_value_or(Windows::Foundation::IInspectable const& value, T const& default_value)
    {
        if (value)
        {
            if constexpr (std::is_base_of_v<Windows::Foundation::IInspectable, T>)
            {
                if (auto temp = value.try_as<T>())
                {
                    return temp;
                }
            }
            else if constexpr (std::is_enum_v<T>)
            {
                if (auto temp = value.try_as<Windows::Foundation::IReference<T>>())
                {
                    return temp.Value();
                }

                if (auto temp = value.try_as<Windows::Foundation::IReference<std::underlying_type_t<T>>>())
                {
                    return static_cast<T>(temp.Value());
                }
            }
            else
            {
                if (auto temp = value.try_as<Windows::Foundation::IReference<T>>())
                {
                    return temp.Value();
                }
            }
        }

        return default_value;
    }
}namespace std
{
    template<> struct hash<winrt::Windows::Foundation::IUnknown> : winrt::impl::hash_base<winrt::Windows::Foundation::IUnknown> {};
    template<> struct hash<winrt::Windows::Foundation::IInspectable> : winrt::impl::hash_base<winrt::Windows::Foundation::IInspectable> {};
    template<> struct hash<winrt::Windows::Foundation::IActivationFactory> : winrt::impl::hash_base<winrt::Windows::Foundation::IActivationFactory> {};
    template<> struct hash<winrt::Windows::Foundation::IAsyncInfo> : winrt::impl::hash_base<winrt::Windows::Foundation::IAsyncInfo> {};
    template<> struct hash<winrt::Windows::Foundation::IAsyncAction> : winrt::impl::hash_base<winrt::Windows::Foundation::IAsyncAction> {};
    template<typename TProgress> struct hash<winrt::Windows::Foundation::IAsyncActionWithProgress<TProgress>> : winrt::impl::hash_base<winrt::Windows::Foundation::IAsyncActionWithProgress<TProgress>> {};
    template<typename TResult> struct hash<winrt::Windows::Foundation::IAsyncOperation<TResult>> : winrt::impl::hash_base<winrt::Windows::Foundation::IAsyncOperation<TResult>> {};
    template<typename TResult, typename TProgress> struct hash<winrt::Windows::Foundation::IAsyncOperationWithProgress<TResult, TProgress>> : winrt::impl::hash_base<winrt::Windows::Foundation::IAsyncOperationWithProgress<TResult, TProgress>> {};
    template<> struct hash<winrt::Windows::Foundation::AsyncActionCompletedHandler> : winrt::impl::hash_base<winrt::Windows::Foundation::AsyncActionCompletedHandler> {};
    template<typename TProgress> struct hash<winrt::Windows::Foundation::AsyncActionProgressHandler<TProgress>> : winrt::impl::hash_base<winrt::Windows::Foundation::AsyncActionProgressHandler<TProgress>> {};
    template<typename TProgress> struct hash<winrt::Windows::Foundation::AsyncActionWithProgressCompletedHandler<TProgress>> : winrt::impl::hash_base<winrt::Windows::Foundation::AsyncActionWithProgressCompletedHandler<TProgress>> {};
    template<typename TResult> struct hash<winrt::Windows::Foundation::AsyncOperationCompletedHandler<TResult>> : winrt::impl::hash_base<winrt::Windows::Foundation::AsyncOperationCompletedHandler<TResult>> {};
    template<typename TResult, typename TProgress> struct hash<winrt::Windows::Foundation::AsyncOperationProgressHandler<TResult, TProgress>> : winrt::impl::hash_base<winrt::Windows::Foundation::AsyncOperationProgressHandler<TResult, TProgress>> {};
    template<typename TResult, typename TProgress> struct hash<winrt::Windows::Foundation::AsyncOperationWithProgressCompletedHandler<TResult, TProgress>> : winrt::impl::hash_base<winrt::Windows::Foundation::AsyncOperationWithProgressCompletedHandler<TResult, TProgress>> {};
    template<typename T> struct hash<winrt::Windows::Foundation::IReference<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::IReference<T>> {};
    template<typename T> struct hash<winrt::Windows::Foundation::EventHandler<T>> : winrt::impl::hash_base<winrt::Windows::Foundation::EventHandler<T>> {};
    template<typename TSender, typename TArgs> struct hash<winrt::Windows::Foundation::TypedEventHandler<TSender, TArgs>> : winrt::impl::hash_base<winrt::Windows::Foundation::TypedEventHandler<TSender, TArgs>> {};
}
