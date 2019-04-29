#include "xlang_model_walker.h"
#include <map>
#include <vector>

namespace xlang::xmeta
{
    void xlang_model_walker::register_listener(xlang_model_listener & listener)
    {
        m_listener = listener;
    }

    void xlang_model_walker::walk()
    {
        for (auto const& [key, val] : m_namespaces)
        {
            enter_namespace_model(val);
        }
    }

    void xlang_model_walker::enter_namespace_model(std::shared_ptr<namespace_model> const& model)
    {
        m_listener.listen_namespace_model(model);
        for (auto const& ns_body : model->get_namespace_bodies())
        {
            for (auto const&[key, val] : ns_body->get_classes())
            {
                enter_class_model(val);
            }

            for (auto const&[key, val] : ns_body->get_structs())
            {
                enter_struct_model(val);
            }

            for (auto const&[key, val] : ns_body->get_interfaces())
            {
                enter_interface_model(val);
            }

            for (auto const&[key, val] : ns_body->get_enums())
            {
                enter_enum_model(val);
            }

            for (auto const&[key, val] : ns_body->get_delegates())
            {
                enter_delegate_model(val);
            }
        }
        for (auto const&[key, val] : model->get_child_namespaces())
        {
            enter_namespace_model(val);
        }
    }

    void xlang_model_walker::enter_class_model(std::shared_ptr<class_model> const& model)
    {
        m_listener.listen_class_model(model);
    }

    void xlang_model_walker::enter_struct_model(std::shared_ptr<struct_model> const& model)
    {
        m_listener.listen_struct_model(model);
    }

    void xlang_model_walker::enter_interface_model(std::shared_ptr<interface_model> const& model)
    {
        m_listener.listen_interface_model(model);
    }

    void xlang_model_walker::enter_enum_model(std::shared_ptr<enum_model> const& model)
    {
        m_listener.listen_enum_model(model);
    }

    void xlang_model_walker::enter_delegate_model(std::shared_ptr<delegate_model> const& model)
    {
        m_listener.listen_delegate_model(model);
    }
}
