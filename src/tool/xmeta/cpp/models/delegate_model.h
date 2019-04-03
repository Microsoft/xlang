#pragma once

#include <string_view>
#include <vector>

#include "base_model.h"

namespace xlang::xmeta
{
    struct delegate_model : base_model
    {
        delegate_model(std::string_view const& id, size_t decl_line) : base_model{ id, decl_line } { }
        delegate_model() = delete;

        xmeta_type return_type;
        std::vector<std::string_view> type_parameters;
        std::vector<formal_parameter_t> formal_parameters;
    };
}
