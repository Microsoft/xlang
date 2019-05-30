#pragma once

#include <assert.h>
#include <memory>
#include <string>
#include <variant>

namespace xlang::xmeta
{
    // model_ref is meant to hold unresolved and then resolved reference state. When unresolved,
    // it holds a string representing the name of the reference. Otherwise, it holds generic state,
    // which is typically a smart pointer to the type or member being referenced.
    template <typename T, typename... Ts>
    struct model_ref
    {
        using resolved_type = std::conditional_t<sizeof...(Ts) == 0, T, std::variant<T, Ts...>>;

        model_ref() = delete;
        model_ref& operator=(model_ref const& other) = default;

        explicit model_ref(std::string_view const& name) :
            m_ref{ std::string(name) }
        { }

        explicit model_ref(resolved_type const& val) :
            m_ref{ val }
        { }

        bool is_resolved() const noexcept
        {
            return m_ref.index() != 0;
        }

        template<typename H>
        bool holds_type() const noexcept
        {
            return std::holds_alternative<H>(std::get<resolved_type>(m_ref));
        }

        auto const& get_resolved_target() const noexcept
        {
            if (!std::holds_alternative<resolved_type>(m_ref))
            {
                xlang::throw_invalid("Model Ref is not resolved");
            }
            return std::get<resolved_type>(m_ref);
        }

        std::string const& get_ref_name() const noexcept
        {
            if (std::holds_alternative<std::string>(m_ref))
            {
                return std::get<std::string>(m_ref);
            }
            return ref_name;
        }

        template<typename R>
        void resolve(R const& value) noexcept
        {
            if (std::holds_alternative<std::string>(m_ref))
            {
                ref_name = std::get<std::string>(m_ref);
            }
            m_ref = value;
        }

    private:
        std::variant<std::string, resolved_type> m_ref;
        std::string ref_name;
    };
}
