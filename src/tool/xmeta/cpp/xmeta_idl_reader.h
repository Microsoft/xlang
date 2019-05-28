#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>

#include "antlr4-runtime.h"
#include "XlangParserBaseListener.h"
#include "xlang_model_listener.h"
#include "models/xmeta_models.h"
#include "xlang_error.h"
#include "meta_reader.h"
#include "meta_writer.h"
#include "xmeta_emit.h"

struct ast_to_st_listener;

namespace xlang::xmeta
{
    struct xmeta_idl_reader : public xlang_model_listener
    {
        xmeta_idl_reader(std::string_view const& idl_assembly_name) : m_xlang_model{ idl_assembly_name, std::vector<std::string>{} }
        { }

        xmeta_idl_reader(std::string_view const& idl_assembly_name, std::vector<std::string> const& paths) : m_xlang_model{ idl_assembly_name, paths }
        { }

        void read(std::istream& idl_contents, bool disable_error_reporting = false);
        void read(std::istream& idl_contents, XlangParserBaseListener& listener, bool disable_error_reporting = false);
        void pass2_resolving_circular_semantics();
        void pass1_resolving_refs();

        auto const& get_namespaces() const
        {
            return m_xlang_model.namespaces;
        }

        size_t get_num_semantic_errors()
        {
            return m_error_manager.get_num_of_semantic_errors();
        }

        size_t get_num_syntax_errors()
        {
            return m_error_manager.get_num_of_syntax_errors();
        }

        std::vector<uint8_t> save_to_memory()
        {
            return writer.save_to_memory();
        }

        void save_to_current_path()
        {
            return writer.save_to_file(std::filesystem::current_path().append(std::string(m_xlang_model.m_assembly) + ".xmeta"));
        }

    private:
        xlang_error_manager m_error_manager;
        compilation_unit m_xlang_model;
        xlang::meta::writer::pe_writer writer;

        const std::string event_registration_token = "Xlang.Foundation.EventRegistrationToken";
    };

    struct xlang_model_pass_1 : public xlang_model_listener
    {
        explicit xlang_model_pass_1(symbol_table & symbols, 
                xlang::xmeta::xlang_error_manager & error_manager)
            : m_symbols{ symbols }, m_error_manager{ error_manager }
        {}

        xlang_model_pass_1() = delete;

        void listen_class_model(std::shared_ptr<class_model> const& model) final;
        void listen_interface_model(std::shared_ptr<interface_model> const& model) final;
        void listen_struct_model(std::shared_ptr<struct_model> const& model) final;
        void listen_delegate_model(std::shared_ptr<delegate_model> const& model) final;

    private:
        xlang_error_manager & m_error_manager;
        symbol_table & m_symbols;
    };

    struct xlang_model_pass_2 : public xlang_model_listener
    {
        explicit xlang_model_pass_2(symbol_table & symbols, xlang::xmeta::xlang_error_manager & error_manager)
            : m_symbols{ symbols }, m_error_manager{ error_manager }
        {}
        xlang_model_pass_2() = delete;

        void listen_class_model(std::shared_ptr<class_model> const& model) final;
        void listen_interface_model(std::shared_ptr<interface_model> const& model) final;
        void listen_struct_model(std::shared_ptr<struct_model> const& model) final;

    private:
        xlang_error_manager & m_error_manager;
        symbol_table & m_symbols;
    };
}
