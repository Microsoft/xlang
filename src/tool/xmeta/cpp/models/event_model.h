#pragma once

#include <string_view>

#include "base_model.h"
#include "method_model.h"
#include "model_types.h"

namespace xlang::xmeta
{
    struct event_semantics
    {
        bool is_protected = false;
        bool is_static = false;
    };

    struct event_model : base_model
    {
        event_model() = delete;
        event_model(std::string_view const& id, 
                size_t decl_line, 
                std::string_view const& assembly_name, 
                event_semantics const& sem, 
                std::shared_ptr<method_model> const& add_method, 
                std::shared_ptr<method_model> const& remove_method,
                type_ref&& t) :
            base_model{ id, decl_line, assembly_name },
            m_semantic{ sem },
            m_add_method{ add_method },
            m_remove_method{ remove_method },
            m_type{ std::move(t) }
        { }

        auto const& get_add_method() const noexcept
        {
            return m_add_method;
        }

        auto const& get_remove_method() const noexcept
        {
            return m_remove_method;
        }

        auto const& get_semantic() const noexcept
        {
            return m_semantic;
        }

        auto const& get_type() const noexcept
        {
            return m_type;
        }

    private:
        event_semantics m_semantic;
        type_ref m_type;

        std::shared_ptr<method_model> m_add_method;
        std::shared_ptr<method_model> m_remove_method;
    };
}
