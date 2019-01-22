#pragma once

#include "impl/base.h"

namespace xlang::text
{
    template <typename T>
    struct writer_base
    {
        writer_base(writer_base const&) = delete;
        writer_base& operator=(writer_base const&) = delete;

        writer_base()
        {
            m_first.reserve(16 * 1024);
        }

        template <typename... Args>
        void write(std::string_view const& value, Args const&... args)
        {
#if defined(XLANG_DEBUG)
            auto expected = count_placeholders(value);
            auto actual = sizeof...(Args);
            XLANG_ASSERT(expected == actual);
#endif
            write_segment(value, args...);
        }

        template <typename... Args>
        std::string write_temp(std::string_view const& value, Args const&... args)
        {
#if defined(XLANG_DEBUG)
            bool restore_debug_trace = debug_trace;
            debug_trace = false;
#endif
            auto const size = m_first.size();

            XLANG_ASSERT(count_placeholders(value) == sizeof...(Args));
            write_segment(value, args...);

            std::string result{ m_first.data() + size, m_first.size() - size };
            m_first.resize(size);

#if defined(XLANG_DEBUG)
            debug_trace = restore_debug_trace;
#endif
            return result;
        }

        void write_impl(std::string_view const& value)
        {
            m_first.insert(m_first.end(), value.begin(), value.end());

#if defined(XLANG_DEBUG)
            if (debug_trace)
            {
                ::printf("%.*s", static_cast<int>(value.size()), value.data());
            }
#endif
        }

        void write_impl(char const value)
        {
            m_first.push_back(value);

#if defined(XLANG_DEBUG)
            if (debug_trace)
            {
                ::printf("%c", value);
            }
#endif
        }

        void write(std::string_view const& value)
        {
            static_cast<T*>(this)->write_impl(value);
        }

        void write(char const value)
        {
            static_cast<T*>(this)->write_impl(value);
        }

        void write_code(std::string_view const& value)
        {
            write(value);
        }

        template <typename F, typename = std::enable_if_t<std::is_invocable_v<F, T&>>>
        void write(F const& f)
        {
            f(*static_cast<T*>(this));
        }

        void write(int32_t const value)
        {
            write(std::to_string(value));
        }

        void write(int64_t const value)
        {
            write(std::to_string(value));
        }

        void write(uint64_t const value)
        {
            write(std::to_string(value));
        }

        template <typename... Args>
        void write_printf(char const* format, Args const&... args)
        {
            char buffer[128];
#if XLANG_PLATFORM_WINDOWS
            size_t const size = sprintf_s(buffer, format, args...);
#else
            size_t const size = snprintf(buffer, sizeof(buffer), format, args...);
#endif
            write(std::string_view{ buffer, size });
        }

        template <auto F, typename List, typename... Args>
        void write_each(List const& list, Args const&... args)
        {
            for (auto&& item : list)
            {
                F(*static_cast<T*>(this), item, args...);
            }
        }
        
        void swap() noexcept
        {
            std::swap(m_second, m_first);
        }

        void flush_to_console() noexcept
        {
            printf("%.*s", static_cast<int>(m_first.size()), m_first.data());
            printf("%.*s", static_cast<int>(m_second.size()), m_second.data());
            m_first.clear();
            m_second.clear();
        }

        void flush_to_file(std::string const& filename)
        {
            if (static_cast<T*>(this)->skip_flush_to_file(filename))
            {
                return;
            }

            std::ofstream file{ filename, std::ios::out | std::ios::binary };
            file.write(reinterpret_cast<char const*>(m_bom.data()), m_bom.size());
            file.write(m_first.data(), m_first.size());
            file.write(m_second.data(), m_second.size());
            m_first.clear();
            m_second.clear();
        }

        void flush_to_file(std::experimental::filesystem::path const& filename)
        {
            flush_to_file(filename.string());
        }

        char back()
        {
            return m_first.empty() ? char{} : m_first.back();
        }

        bool file_equal(std::string const& filename) const
        {
            if (!std::experimental::filesystem::exists(filename))
            {
                return false;
            }

            meta::reader::file_view file{ filename };

            if (file.size() != m_bom.size() + m_first.size() + m_second.size())
            {
                return false;
            }

            if (!std::equal(m_bom.begin(), m_bom.end(), file.begin(), file.begin() + m_bom.size()))
            {
                return false;
            }

            if (!std::equal(m_first.begin(), m_first.end(), file.begin() + m_bom.size(), file.begin() + m_bom.size() + m_first.size()))
            {
                return false;
            }

            return std::equal(m_second.begin(), m_second.end(), file.begin() + m_bom.size() + m_first.size(), file.end());
        }

#if defined(XLANG_DEBUG)
        bool debug_trace{};
#endif

    private:

        static constexpr std::array<uint8_t, 3> m_bom{ 0xEF, 0xBB, 0xBF };

        constexpr bool skip_flush_to_file(std::string const&) const noexcept
        {
            return false;
        }

        static constexpr uint32_t count_placeholders(std::string_view const& format) noexcept
        {
            uint32_t count{};
            bool escape{};

            for (auto c : format)
            {
                if (c == '^')
                {
                    escape = true;
                    continue;
                }

                if ((c == '%' || c == '@') && !escape)
                {
                    ++count;
                }

                escape = false;
            }

            return count;
        }

        void write_segment(std::string_view const& value)
        {
            write(value);
        }

        template <typename First, typename... Rest>
        void write_segment(std::string_view const& value, First const& first, Rest const&... rest)
        {
            auto offset = value.find_first_of("^%@");
            XLANG_ASSERT(offset != std::string_view::npos);
            write(value.substr(0, offset));

            if (value[offset] == '^')
            {
                auto next = value[offset + 1];

                if (next == '%' || next == '@')
                {
                    write(next);
                    offset++;
                }
                else
                {
                    write('^');
                }

                write_segment(value.substr(offset + 1), first, rest...);
            }
            else
            {
                if (value[offset] == '%')
                {
                    static_cast<T*>(this)->write(first);
                }
                else
                {
                    if constexpr (std::is_convertible_v<First, std::string_view>)
                    {
                        static_cast<T*>(this)->write_code(first);
                    }
                    else
                    {
                        XLANG_ASSERT(false); // '@' placeholders are only for text.
                    }
                }

                write_segment(value.substr(offset + 1), rest...);
            }
        }

        std::vector<char> m_second;
        std::vector<char> m_first;
    };

    template <auto F, typename... Args>
    auto bind(Args&&... args)
    {
        return [&](auto& writer)
        {
            F(writer, args...);
        };
    }

    template <auto F, typename List, typename... Args>
    auto bind_each(List const& list, Args const&... args)
    {
        return [&](auto& writer)
        {
            for (auto&& item : list)
            {
                F(writer, item, args...);
            }
        };
    }

    template <auto F, typename T>
    auto bind_list(std::string_view const& delimiter, T const& list)
    {
        return [&](auto& writer)
        {
            bool first{ true };

            for (auto&& item : list)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    writer.write(delimiter);
                }

                F(writer, item);
            }
        };
    }

    template <typename T>
    auto bind_list(std::string_view const& delimiter, T const& list)
    {
        return [&](auto& writer)
        {
            bool first{ true };

            for (auto&& item : list)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    writer.write(delimiter);
                }

                writer.write(item);
            }
        };
    }
}
