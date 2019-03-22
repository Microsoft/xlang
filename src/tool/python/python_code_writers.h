#pragma once

namespace xlang
{
    void write_setup_filenames(writer& w, std::vector<std::string> const& namespaces)
    {
        XLANG_ASSERT(namespaces.size() > 0);

        for (auto&& ns : namespaces)
        {
            w.write("'%/src/py.%.cpp', ", settings.module, ns);
        }

        w.write("'%/src/_%.cpp'", settings.module, settings.module);
    }

    void write_python_import(writer& w, TypeDef const& type)
    {
        w.write("% = _ns_module.%\n\n", type.TypeName(), type.TypeName());
    }

    void write_python_enum(writer& w, TypeDef const& type)
    {
        w.write("class %(enum.%):\n", type.TypeName(), is_flags_enum(type) ? "IntFlag" : "IntEnum");
        {
            writer::indent_guard g{ w };

            for (auto&& field : type.FieldList())
            {
                if (auto constant = field.Constant())
                {
                    w.write("% = %\n", bind<write_upper_snake_case>(field.Name()), *constant);
                }
            }
        }

        w.write("\n");
    }

    void write_python_method_name(writer& w, MethodDef const& method)
    {
        if (!method)
        {
            w.write("None");
        }
        else if (is_constructor(method))
        {
            // TODO
            w.write(method.Name());
        }
        else if (method.SpecialName())
        {
            w.write("__%", method.Name());
        }
        else
        {
            write_lower_snake_case(w, method.Name());
        }
    }

    auto get_params(MethodDef const& method)
    {
        std::vector<std::string_view> in_params{};
        std::vector<std::string_view> out_params{};

        method_signature sig{ method };

        if (sig.return_signature())
        {
            out_params.push_back(sig.return_param_name());
        }

        for (auto&& p : sig.params())
        {
            if (is_in_param(p))
            {
                in_params.push_back(p.first.Name());
            }

            if (is_out_param(p))
            {
                out_params.push_back(p.first.Name());
            }
        }

        if (is_constructor(method))
        {
            XLANG_ASSERT(out_params.size() == 0);
            out_params.push_back("_return_value");
        }

        return std::make_tuple(std::move(in_params), std::move(out_params));
    }

    auto get_constructors(TypeDef const& type)
    {
        std::vector<MethodDef> ctors{};

        for (auto&& method : type.MethodList())
        {
            if (is_constructor(method))
            {
                ctors.push_back(method);
            }
        }

        return std::move(ctors);
    }

    auto get_methodsz(TypeDef const& type)
    {
        std::map<std::string_view, std::vector<MethodDef>> methods{};

        auto category = get_category(type);
        if (category == category::class_type)
        {
            for (auto&& method : type.MethodList())
            {
                if (is_constructor(method)) continue;

                auto& v = methods[method.Name()];
                XLANG_ASSERT(std::all_of(v.begin(), v.end(), [&method](auto const& m) { return is_static(m) == is_static(method); }));
                v.push_back(method);
            }
        }
        else if (category == category::interface_type)
        {
            throw_invalid("not impl");
        }
        else
        {
            throw_invalid("only classes and interfaces have methods");
        }

        return std::move(methods);
    }




    auto get_in_params(std::vector<MethodDef> const& methods)
    {
        std::map<std::string_view, uint32_t> params{};

        for (auto&& method : methods)
        {
            auto[inparams, outparams] = get_params(method);
            for (auto&& inparam : inparams)
            {
                if (params.find(inparam) == params.end())
                {
                    params[inparam] = 1;
                }
                else
                {
                    params[inparam] = params[inparam] + 1;
                }
            }
        }

        return std::move(params);
    }


    void write_python_class_init(writer& w, TypeDef const& type)
    {
        auto write_instance_prop = [&w]()
        {
            w.write(R"(@property
def _instance(self):
    return self.__instance
)");
        };

        auto write_wrap_dunder_init = [&w](TypeDef const& type)
        {
            w.write(R"(def __init__(self, *, _instance=None):
    if type(_instance) != type(self).__type:
        raise TypeError("_instance must be a @ native type")
    self.__instance = _instance
)", type.TypeName());
        };

        auto category = get_category(type);
        if (category == category::class_type)
        {
            if (is_static(type))
            {
                w.write(R"(def __new__(cls):
    raise TypeError("% is a static class. It cannot be constructed")
)", type.TypeName());
            }
            else
            {
                if (is_default_constructable(type))
                {
                    w.write(R"(def __init__(self, *, _instance=None):
    if _instance == None:
        self.__instance = type(self).__type._default_ctor()
    else:
        if type(_instance) != type(self).__type:
            raise TypeError("_instance must be a % native type")
        self.__instance = _instance
)", type.TypeName());
                }
                else
                {
                    write_wrap_dunder_init(type);
                }

                write_instance_prop();
            }
        }
        else if (category == category::interface_type)
        {
            write_wrap_dunder_init(type);
            write_instance_prop();
        }
        else
        {
            throw_invalid("only classes and interfaces have class init");
        }
    }

    void write_python_method_first_param(writer& w, MethodDef const& method)
    {
        if (is_static(method))
        {
            w.write("cls");
        }
        else
        {
            w.write("self");
        }
    }

    void write_python_method_params(writer& w, MethodDef const& method)
    {
        separator s{ w };
        s();
        write_python_method_first_param(w, method);

        auto[inparams, outparams] = get_params(method);
        for (auto&& inp : inparams)
        {
            s();
            w.write(inp);
            // TODO: type hint
        }
    }

    void write_python_method_body_return_values(writer& w, method_signature const& signature)
    {
        bool write_equals = false;
        separator s{ w };

        if (signature.return_signature())
        {
            s();
            w.write(signature.return_param_name());
            write_equals = true;
        }

        for (auto&& p : signature.params())
        {
            if (is_out_param(p))
            {
                s();
                w.write(p.first.Name());
                write_equals = true;
            }
        }

        if (write_equals)
        {
            w.write(" = ");
        }
    }

    void write_python_method_body_call_args(writer& w, method_signature const& signature)
    {
        separator s{ w };
        for (auto&& p : signature.params())
        {
            if (is_in_param(p))
            {
                s();
                w.write("_%", p.first.Name());
            }
        }
    }

    void write_python_method_body_calling_context(writer& w, MethodDef const& method)
    {
        if (is_static(method))
        {
            w.write("cls.__type");
        }
        else
        {
            w.write("self.__instance");
        }
    }

    void write_return_value_convert(writer& w, std::string_view name, TypeSig const& signature)
    {
        call(get_type_semantics(signature),
            [&](type_definition const& type)
        {
            switch (get_category(type))
            {
            case category::class_type:
            case category::interface_type:
                w.write("% = %(_instance=%)\n", name, type.TypeName(), name);
                break;
            case category::enum_type:
                break;
            default:
                w.write("# % category not implemented % \n", name, type);
                w.write("raise NotImplementedError\n");
            }
        },
            [](fundamental_type) {},
            [&](auto)
        {
            w.write("# % not implemented \n", name);
            w.write("raise NotImplementedError\n");
        });
    }

    void write_return_value_convert(writer& w, method_signature::param_t const& param)
    {
        switch (get_param_category(param))
        {
        case param_category::fill_array:
            w.write("# return fill array % not impl\n", param.first.Name());
            w.write("raise NotImplementedError\n");
            break;
        case param_category::receive_array:
            w.write("# return recieve array % not impl\n", param.first.Name());
            w.write("raise NotImplementedError\n");
            break;
        case param_category::out:
            write_return_value_convert(w, param.first.Name(), param.second->Type());
            break;
        default:
            throw_invalid("invalid out param category");
        }
    }

    void write_in_param_convert(writer& w, method_signature::param_t const& param, std::string_view arg_name = "")
    {
        auto name = param.first.Name();

        if (arg_name.size() == 0)
        {
            arg_name = name;
        }

        switch (get_param_category(param))
        {
        case param_category::fill_array:
            w.write("# % fill array\n_% = %\n", name, name, arg_name);
            break;
        case param_category::pass_array:
            w.write("# pass array % not impl\n", name);
            w.write("raise NotImplementedError\n");
            break;
        case param_category::in:
            call(get_type_semantics(param.second->Type()),
                [&](type_definition const& type)
            {
                switch (get_category(type))
                {
                case category::class_type:
                case category::interface_type:
                    w.write("_% = %._instance\n", name, arg_name);
                    break;
                default:
                    w.write("# % category not implemented % \n", name, type);
                    w.write("raise NotImplementedError\n");
                    //w.write("_% = %\n", name, arg_name);
                }
            },
                [&](fundamental_type)
            {
                w.write("_% = %\n", name, arg_name);
            },
                [&](auto)
            {
                w.write("# % not implemented \n", name);
                w.write("raise NotImplementedError\n");
                //w.write("_% = %\n", name, arg_name);
            });
            break;
        default:
            throw_invalid("invalid in param category");
        }
    }

    void write_python_method_body(writer& w, MethodDef const& method, std::string_view args = "")
    {
        method_signature signature{ method };

        int count = 0;
        for (auto&& p : signature.params())
        {
            if (is_in_param(p))
            {
                std::string arg{};
                if (!args.empty())
                {
                    arg = w.write_temp("%[%]", args, std::to_string(count++));
                }
                write_in_param_convert(w, p, arg);
            }
        }

        w.write("%%.%(%)\n",
            bind<write_python_method_body_return_values>(signature),
            bind<write_python_method_body_calling_context>(method),
            get_method_abi_name(method),
            bind<write_python_method_body_call_args>(signature));

        std::vector<std::string_view> return_tuple{};

        if (signature.return_signature())
        {
            write_return_value_convert(w, signature.return_param_name(), signature.return_signature().Type());
            return_tuple.push_back(signature.return_param_name());
        }

        for (auto&& p : signature.params())
        {
            if (is_out_param(p))
            {
                write_return_value_convert(w, p);
                return_tuple.push_back(p.first.Name());
            }
        }

        if (return_tuple.size() > 0)
        {
            w.write("return (%)\n", bind_list(", ", return_tuple));
        }
    }

    void write_python_method(writer& w, MethodDef const& method, bool is_overload)
    {
        if (is_static(method))
        {
            w.write("@classmethod\n");
        }

        if (is_overload)
        {
            w.write("@typing.overload\n");
        }

        w.write("def %(%):\n", bind<write_python_method_name>(method), bind<write_python_method_params>(method));
        writer::indent_guard g{ w };
        if (is_overload)
        {
            w.write("pass\n");
        }
        else
        {
            write_python_method_body(w, method);
        }
    }

    void write_python_methods(writer& w, TypeDef const& type)
    {
        //auto overloads = get_overloaded_method_names(type);

        std::map<std::string_view, std::vector<MethodDef>> overloaded_methods{};

        //enumerate_required_types(type, [&](TypeDef const& type)
        //{
        //    auto guard{ w.push_generic_params(type.GenericParam()) };

        //    for (auto&& method : type.MethodList())
        //    {
        //        if (is_constructor(method)) continue;

        //        auto overloaded = contains(overloads, method.Name());

        //        if (overloaded)
        //        {
        //            auto& v = overloaded_methods[method.Name()];
        //            XLANG_ASSERT(std::all_of(v.begin(), v.end(), [&method](auto const& m) { return is_static(m) == is_static(method); }));
        //            v.push_back(method);
        //        }

        //        write_python_method(w, method, overloaded);
        //    }
        //});

        for (auto&&[name, methods] : overloaded_methods)
        {
            w.write("# overload\ndef %(%, *args):\n", 
                bind<write_python_method_name>(methods[0]), 
                bind<write_python_method_first_param>(methods[0]));

            writer::indent_guard g{ w };
            w.write("_count = len(args)\n");
            for (auto&& method : methods)
            {
                method_signature sig{ method };
                w.write("if _count == %:\n", std::to_string(sig.params().size()));
                writer::indent_guard gg{ w };
                write_python_method_body(w, method, "args");
            }
            w.write("raise TypeError(\"invalid argument count\")\n");
        }
    }

    void write_python_properties(writer& w, TypeDef const& type)
    {
        //enumerate_required_types(type, [&](TypeDef const& type)
        //{
        //    auto guard{ w.push_generic_params(type.GenericParam()) };

        //    for (auto&& prop : type.PropertyList())
        //    {
        //        auto[getter, setter] = get_property_methods(prop);

        //        if (is_static(getter))
        //        {
        //            w.write("# staticprop %", prop.Name());
        //        }
        //        else
        //        {
        //            w.write("% = property(fget=%, fset=%)\n",
        //                bind<write_lower_snake_case>(prop.Name()),
        //                bind<write_python_method_name>(getter),
        //                bind<write_python_method_name>(setter));
        //        }
        //    }
        //});
    }

    void write_python_class(writer& w, TypeDef const& type)
    {
        if (is_exclusive_to(type)) return;

        w.write("class @:\n", type.TypeName());
        {
            writer::indent_guard g{ w };

            w.write("__type = _ns_module.@\n", type.TypeName());
            write_python_class_init(w, type);
            write_python_methods(w, type);
            write_python_properties(w, type);

            if (has_dunder_str_method(type))
            {
                w.write("__str__ = to_string\n");
            }

            if (has_dunder_len_method(type))
            {
                w.write("__len__ = __get_Size\n");
            }


        }
        w.write("\n");
    }

    //void write_python_interface(writer& w, TypeDef const& type)
    //{
    //    if (is_exclusive_to(type)) return;

    //    auto guard{ w.push_generic_params(type.GenericParam()) };

    //    w.write("class @:\n", type.TypeName());
    //    {
    //        writer::indent_guard g{ w };
    //        w.write("__type = _ns_module.@\n", type.TypeName());
    //        write_python_class_init(w, type);

    //        if (has_dunder_str_method(type))
    //        {
    //            w.write("__str__ = to_string\n");
    //        }

    //        if (has_dunder_len_method(type))
    //        {
    //            w.write("__len__ = __get_Size\n");
    //        }

    //    }
    //    w.write("\n");
    //}
}