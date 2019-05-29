#pragma once

#include <memory>
#include <string_view>
#include <set>
#include "namespace_member_model.h"
#include "property_model.h"

namespace xlang::xmeta
{
    struct class_or_interface_model : namespace_member_model
    {
        class_or_interface_model() = delete;
        class_or_interface_model(std::string_view const& id, size_t decl_line, std::string_view const& assembly_name, std::shared_ptr<namespace_body_model> const& containing_ns_body) :
            namespace_member_model{ id, decl_line, assembly_name, containing_ns_body }
        { }

        class_or_interface_model(std::string_view const& id, size_t decl_line, std::string_view const& assembly_name, std::string_view const& containing_namespace_name) :
            namespace_member_model{ id, decl_line, assembly_name, containing_namespace_name }
        { }

        auto const& get_interface_bases() const noexcept
        {
            return m_interface_base_refs;
        }

        auto const& get_properties() const noexcept
        {
            return m_properties;
        }

        auto const& get_methods() const noexcept
        {
            return m_methods;
        }

        auto const& get_events() const noexcept
        {
            return m_events;
        }

        void add_interface_base_ref(std::string_view const& interface_base_ref)
        {
            m_interface_base_refs.emplace_back(interface_base_ref);
        }

        compilation_error add_member(std::shared_ptr<property_model> const& member)
        {
            if (member_id_exists(member->get_id()))
            {
                return compilation_error::symbol_exists;
            }
            m_properties.emplace_back(member);
            return compilation_error::passed;
        }

        compilation_error add_member(std::shared_ptr<method_model> const& member)
        {
            // TODO: the case with overloading
            if (member_id_exists(member->get_id()))
            {
                return compilation_error::symbol_exists;
            }
            m_methods.emplace_back(member);
            return compilation_error::passed;
        }

        compilation_error add_member(std::shared_ptr<event_model> const& member)
        {
            if (member_id_exists(member->get_id()))
            {
                return compilation_error::symbol_exists;
            }
            m_events.emplace_back(member);
            return compilation_error::passed;
        }

        auto const& get_property_member(std::string const& member_id)
        {
            return *get_it(m_properties, member_id);
        }

        bool member_id_exists(std::string_view const& id)
        {
            return contains_id(m_properties, id) ||
                contains_id(m_methods, id) ||
                contains_id(m_events, id);
        }

        bool property_id_exists(std::string_view const& id)
        {
            return contains_id(m_properties, id);
        }

        void validate(xlang_error_manager & error_manager)
        {
            for (auto const& prop : m_properties)
            {
                prop->validate(error_manager);
            }
        }

        void resolve(symbol_table & symbols, xlang_error_manager & error_manager)
        {
            for (auto & m_method : m_methods)
            {
                m_method->resolve(symbols, error_manager, this->get_containing_namespace_body()->get_containing_namespace()->get_fully_qualified_id());
            }
            for (auto & m_property : m_properties)
            {
                m_property->resolve(symbols, error_manager, this->get_containing_namespace_body()->get_containing_namespace()->get_fully_qualified_id());
            }
            for (auto & m_event : m_events)
            {
                m_event->resolve(symbols, error_manager, this->get_containing_namespace_body()->get_containing_namespace()->get_fully_qualified_id());
            }

            for (auto & interface_base : m_interface_base_refs)
            {
                assert(!interface_base.get_semantic().is_resolved());
                std::string ref_name = interface_base.get_semantic().get_ref_name();
                std::string symbol = ref_name.find(".") != std::string::npos
                    ? ref_name : this->get_containing_namespace_body()->get_containing_namespace()->get_fully_qualified_id() + "." + ref_name;

                auto iter = symbols.get_symbol(symbol);
                if (std::holds_alternative<std::monostate>(iter))
                {
                    error_manager.write_unresolved_type_error(get_decl_line(), symbol);
                }
                else
                {
                    if (std::holds_alternative<std::shared_ptr<interface_model>>(iter))
                    {
                        interface_base.set_semantic(iter);
                    }
                    else
                    {
                        error_manager.write_not_an_interface_error(get_decl_line(), symbol);
                    }
                }
            }
        }

    private:
        std::vector<type_ref> m_interface_base_refs;
        // TODO: Add type parameters (generic types)

        // Members
        std::vector<std::shared_ptr<property_model>> m_properties;
        std::vector<std::shared_ptr<method_model>> m_methods;
        std::vector<std::shared_ptr<event_model>> m_events;
    };
}
