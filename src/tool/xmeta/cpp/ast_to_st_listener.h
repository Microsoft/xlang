#pragma once

#include <optional>
#include <string_view>
#include "XlangParserBaseListener.h"
#include "models/xmeta_models.h"
#include "XlangParser.h"

namespace xlang::xmeta
{
    struct xmeta_idl_reader;
}

enum class listener_error : bool
{
    passed = true,
    failed = false
};

struct ast_to_st_listener : XlangParserBaseListener
{
    ast_to_st_listener() = delete;
    ast_to_st_listener(xlang::xmeta::compilation_unit & xlang_model, xlang::xmeta::xlang_error_manager & error_manager);

    void enterClass_declaration(XlangParser::Class_declarationContext * ctx) override;
    void enterInterface_declaration(XlangParser::Interface_declarationContext *ctx) override;
    void enterDelegate_declaration(XlangParser::Delegate_declarationContext* ctx) override;
    void enterEnum_declaration(XlangParser::Enum_declarationContext *ctx) override;
    void enterStruct_declaration(XlangParser::Struct_declarationContext *ctx) override;

    void enterNamespace_declaration(XlangParser::Namespace_declarationContext *ctx) override;
    void exitNamespace_declaration(XlangParser::Namespace_declarationContext *ctx) override;

    void set_cur_namespace_body(std::shared_ptr<xlang::xmeta::namespace_body_model> const& cur_namespace_body)
    {
        this->m_cur_namespace_body = cur_namespace_body;
    }

private:
    xlang::xmeta::compilation_unit & xlang_model;
    xlang::xmeta::xlang_error_manager & error_manager;

    std::string_view m_cur_assembly;

    listener_error extract_enum_member(XlangParser::Enum_member_declarationContext *ast_enum_member, std::shared_ptr<xlang::xmeta::enum_model> const& new_enum);
    listener_error resolve_enum_val(xlang::xmeta::enum_member & member, std::shared_ptr<xlang::xmeta::enum_model> const& new_enum, std::set<std::string_view>& depentents);
  
    listener_error extract_type(XlangParser::TypeContext* tc, xlang::xmeta::type_ref& tr);
    listener_error extract_type(XlangParser::Return_typeContext* rtc, std::optional<xlang::xmeta::type_ref>& tr);

    void extract_formal_params(std::vector<XlangParser::Fixed_parameterContext*> const& ast_formal_params, 
        std::variant<std::shared_ptr<xlang::xmeta::delegate_model>, std::shared_ptr<xlang::xmeta::method_model>> const& model);

    listener_error extract_property_accessors(std::string const& property_id,
        xlang::xmeta::type_ref & tr,
        size_t decl_line,
        XlangParser::Property_accessorsContext* property_accessors,
        std::shared_ptr<xlang::xmeta::class_or_interface_model> const& model,
        xlang::xmeta::property_semantics const& property_sem = xlang::xmeta::property_semantics());
    
    listener_error extract_event_accessors(std::string const& event_id,
        xlang::xmeta::type_ref & tr,
        size_t decl_line,
        XlangParser::Event_accessorsContext* property_accessors,
        std::shared_ptr<xlang::xmeta::class_or_interface_model> const& model,
        xlang::xmeta::event_semantics const& event_sem = xlang::xmeta::event_semantics());

    std::shared_ptr<xlang::xmeta::namespace_body_model> m_cur_namespace_body;
    std::shared_ptr<xlang::xmeta::class_model> m_cur_class;
    std::shared_ptr<xlang::xmeta::interface_model> m_cur_interface;
    std::shared_ptr<xlang::xmeta::struct_model> m_cur_struct;

    void push_namespace(std::string_view const& name, size_t decl_line);
    void pop_namespace();

    bool namespace_exist(std::string_view const ref_name);
};
