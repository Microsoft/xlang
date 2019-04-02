#pragma once

namespace xlang
{
    static auto get_start_time()
    {
        return std::chrono::high_resolution_clock::now();
    }

    static auto get_elapsed_time(std::chrono::time_point<std::chrono::high_resolution_clock> const& start)
    {
        return std::chrono::duration_cast<std::chrono::duration<int64_t, std::milli>>(std::chrono::high_resolution_clock::now() - start).count();
    }

    struct method_signature
    {
        explicit method_signature(MethodDef const& method) :
            m_method(method.Signature())
        {
            auto params = method.ParamList();

            if (m_method.ReturnType() && params.first != params.second && params.first.Sequence() == 0)
            {
                m_return = params.first;
                ++params.first;
            }

            for (uint32_t i{}; i != size(m_method.Params()); ++i)
            {
                m_params.emplace_back(params.first + i, &m_method.Params().first[i]);
            }
        }

        std::vector<std::pair<Param, ParamSig const*>>& params()
        {
            return m_params;
        }

        std::vector<std::pair<Param, ParamSig const*>> const& params() const
        {
            return m_params;
        }

        auto const& return_signature() const
        {
            return m_method.ReturnType();
        }

        auto return_param_name() const
        {
            std::string_view name;

            if (m_return)
            {
                name = m_return.Name();
            }
            else
            {
                name = "winrt_impl_result";
            }

            return name;
        }

    private:

        MethodDefSig m_method;
        std::vector<std::pair<Param, ParamSig const*>> m_params;
        Param m_return;
    };

    struct separator
    {
        writer& w;
        bool first{ true };

        void operator()()
        {
            if (first)
            {
                first = false;
            }
            else
            {
                w.write(", ");
            }
        }
    };

    template <typename T>
    bool has_attribute(T const& row, std::string_view const& type_namespace, std::string_view const& type_name)
    {
        return static_cast<bool>(get_attribute(row, type_namespace, type_name));
    }

    template <typename T>
    auto get_attribute_value(CustomAttribute const& attribute, uint32_t const arg)
    {
        return std::get<T>(std::get<ElemSig>(attribute.Value().FixedArgs()[arg].value).value);
    }

    static auto get_abi_name(MethodDef const& method)
    {
        if (auto overload = get_attribute(method, "Windows.Foundation.Metadata", "OverloadAttribute"))
        {
            return get_attribute_value<std::string_view>(overload, 0);
        }
        else
        {
            return method.Name();
        }
    }

    static auto get_name(MethodDef const& method)
    {
        auto name = method.Name();

        if (method.SpecialName())
        {
            return name.substr(name.find('_') + 1);
        }

        return name;
    }

    static bool is_remove_overload(MethodDef const& method)
    {
        return method.SpecialName() && starts_with(method.Name(), "remove_");
    }

    static bool is_add_overload(MethodDef const& method)
    {
        return method.SpecialName() && starts_with(method.Name(), "add_");
    }

    static bool is_put_overload(MethodDef const& method)
    {
        return method.SpecialName() && starts_with(method.Name(), "put_");
    }

    static bool is_noexcept(MethodDef const& method)
    {
        return is_remove_overload(method) || has_attribute(method, "Windows.Foundation.Metadata", "NoExceptionAttribute");
    }

    static bool is_exclusive(TypeDef const& type)
    {
        return has_attribute(type, "Windows.Foundation.Metadata", "ExclusiveToAttribute");
    }

    static bool has_fastabi(TypeDef const& type)
    {
        return settings.fastabi && has_attribute(type, "Windows.Foundation.Metadata", "FastAbiAttribute");
    }

    static bool is_always_disabled(TypeDef const& type)
    {
        if (settings.component_ignore_velocity)
        {
            return false;
        }

        auto feature = get_attribute(type, "Windows.Foundation.Metadata", "FeatureAttribute");

        if (!feature)
        {
            return false;
        }

        // The first argument is a Windows.Foundation.Metadata.FeatureStage enum class.
        auto stage = get_attribute_value<ElemSig::EnumValue>(feature, 0);

        return stage.equals_enumerator("AlwaysDisabled");
    }

    static bool is_always_enabled(TypeDef const& type)
    {
        auto feature = get_attribute(type, "Windows.Foundation.Metadata", "FeatureAttribute");

        if (!feature)
        {
            return true;
        }

        // The first argument is a Windows.Foundation.Metadata.FeatureStage enum class.
        auto stage = get_attribute_value<ElemSig::EnumValue>(feature, 0);

        return stage.equals_enumerator("AlwaysEnabled");
    }

    static coded_index<TypeDefOrRef> get_default_interface(TypeDef const& type)
    {
        auto impls = type.InterfaceImpl();

        for (auto&& impl : impls)
        {
            if (has_attribute(impl, "Windows.Foundation.Metadata", "DefaultAttribute"))
            {
                return impl.Interface();
            }
        }

        if (!empty(impls))
        {
            throw_invalid("Type '", type.TypeNamespace(), ".", type.TypeName(), "' does not have a default interface");
        }

        return {};
    }

    static bool is_async(MethodDef const& method, method_signature const& method_signature)
    {
        if (is_put_overload(method))
        {
            return true;
        }

        if (!method_signature.return_signature())
        {
            return false;
        }

        bool async{};

        call(method_signature.return_signature().Type().Type(),
            [&](GenericTypeInstSig const& type)
        {
            auto generic_type = type.GenericType().TypeRef();

            if (generic_type.TypeNamespace() == "Windows.Foundation")
            {
                auto type_name = generic_type.TypeName();

                async =
                    type_name == "IAsyncAction" ||
                    type_name == "IAsyncOperation`1" ||
                    type_name == "IAsyncActionWithProgress`1" ||
                    type_name == "IAsyncOperationWithProgress`2";
            }
        },
            [](auto&&) {});

        return async;
    }

    static TypeDef get_base_class(TypeDef const& derived)
    {
        auto extends = derived.Extends();

        if (!extends)
        {
            return{};
        }

        auto base = extends.TypeRef();
        auto type_name = base.TypeName();
        auto type_namespace = base.TypeNamespace();

        if (type_name == "Object" && type_namespace == "System")
        {
            return {};
        }

        return find_required(base);
    };


    static auto get_bases(TypeDef const& type)
    {
        std::vector<TypeDef> bases;

        for (auto base = get_base_class(type); base; base = get_base_class(base))
        {
            bases.push_back(base);
        }

        return bases;
    }

    static std::pair<uint16_t, uint16_t> get_version(TypeDef const& type)
    {
        uint32_t version{};

        for (auto&& attribute : type.CustomAttribute())
        {
            auto name = attribute.TypeNamespaceAndName();

            if (name.first != "Windows.Foundation.Metadata")
            {
                continue;
            }

            if (name.second == "ContractVersionAttribute")
            {
                version = get_attribute_value<uint32_t>(attribute, 1);
                break;
            }

            if (name.second == "VersionAttribute")
            {
                version = get_attribute_value<uint32_t>(attribute, 0);
                break;
            }
        }

        return { HIWORD(version), LOWORD(version) };
    }

    struct interface_info
    {
        TypeDef type;
        bool is_default{};
        bool defaulted{};
        bool overridable{};
        bool base{};
        bool exclusive{};
        bool fastabi{};
        std::pair<uint16_t, uint16_t> version{};
        std::vector<std::vector<std::string>> generic_param_stack{};
    };

    using get_interfaces_t = std::vector<std::pair<std::string, interface_info>>;

    static interface_info* find(get_interfaces_t& interfaces, std::string_view const& name)
    {
        auto pair = std::find_if(interfaces.begin(), interfaces.end(), [&](auto&& pair)
        {
            return pair.first == name;
        });

        if (pair == interfaces.end())
        {
            return nullptr;
        }

        return &pair->second;
    }

    static void insert_or_assign(get_interfaces_t& interfaces, std::string_view const& name, interface_info&& info)
    {
        if (auto existing = find(interfaces, name))
        {
            *existing = std::move(info);
        }
        else
        {
            interfaces.emplace_back(name, info);
        }
    }

    static void get_interfaces_impl(writer& w, get_interfaces_t& result, bool defaulted, bool overridable, bool base, std::vector<std::vector<std::string>> const& generic_param_stack, std::pair<InterfaceImpl, InterfaceImpl>&& children)
    {
        for (auto&& impl : children)
        {
            interface_info info;
            auto type = impl.Interface();
            auto name = w.write_temp("%", type);
            info.is_default = has_attribute(impl, "Windows.Foundation.Metadata", "DefaultAttribute");
            info.defaulted = !base && (defaulted || info.is_default);

            {
                // This is for correctness rather than an optimization (but helps performance as well).
                // If the interface was not previously inserted, carry on and recursively insert it.
                // If a previous insertion was defaulted we're done as it is correctly captured.
                // If a newly discovered instance of a previous insertion is not defaulted, we're also done.
                // If it was previously captured as non-defaulted but now found as defaulted, we carry on and
                // rediscover it as we need it to be defaulted recursively.

                if (auto found = find(result, name))
                {
                    if (found->defaulted || !info.defaulted)
                    {
                        continue;
                    }
                }
            }

            info.overridable = overridable || has_attribute(impl, "Windows.Foundation.Metadata", "OverridableAttribute");
            info.base = base;
            info.generic_param_stack = generic_param_stack;
            writer::generic_param_guard guard;

            switch (type.type())
            {
                case TypeDefOrRef::TypeDef:
                {
                    info.type = type.TypeDef();
                    break;
                }
                case TypeDefOrRef::TypeRef:
                {
                    info.type = find_required(type.TypeRef());
                    w.add_depends(info.type);
                    break;
                }
                case TypeDefOrRef::TypeSpec:
                {
                    auto type_signature = type.TypeSpec().Signature();

                    std::vector<std::string> names;

                    for (auto&& arg : type_signature.GenericTypeInst().GenericArgs())
                    {
                        names.push_back(w.write_temp("%", arg));
                    }

                    info.generic_param_stack.push_back(std::move(names));

                    guard = w.push_generic_params(type_signature.GenericTypeInst());
                    auto signature = type_signature.GenericTypeInst();
                    info.type = find_required(signature.GenericType().TypeRef());

                    break;
                }
            }

            info.exclusive = is_exclusive(info.type);
            info.version = get_version(info.type);
            get_interfaces_impl(w, result, info.defaulted, info.overridable, base, info.generic_param_stack, info.type.InterfaceImpl());
            insert_or_assign(result, name, std::move(info));
        }
    };

    static auto get_interfaces(writer& w, TypeDef const& type)
    {
        w.abi_types = false;
        get_interfaces_t result;
        get_interfaces_impl(w, result, false, false, false, {}, type.InterfaceImpl());

        for (auto&& base : get_bases(type))
        {
            get_interfaces_impl(w, result, false, false, true, {}, base.InterfaceImpl());
        }

        if (!has_fastabi(type))
        {
            return result;
        }

        auto count = std::count_if(result.begin(), result.end(), [](auto&& pair)
        {
            return pair.second.exclusive && !pair.second.base && !pair.second.overridable;
        });

        std::partial_sort(result.begin(), result.begin() + count, result.end(), [](auto&& left_pair, auto&& right_pair)
        {
            auto& left = left_pair.second;
            auto& right = right_pair.second;

            if (left.base != right.base)
            {
                return !left.base;
            }

            if (left.is_default != right.is_default)
            {
                return left.is_default;
            }

            if (left.overridable != right.overridable)
            {
                return !left.overridable;
            }

            if (left.exclusive != right.exclusive)
            {
                return left.exclusive;
            }

            auto left_enabled = is_always_enabled(left.type);
            auto right_enabled = is_always_enabled(right.type);

            if (left_enabled != right_enabled)
            {
                return left_enabled;
            }

            if (left.version != right.version)
            {
                return left.version < right.version;
            }

            return left_pair.first < right_pair.first;
        });

        std::for_each_n(result.begin(), count, [](auto && pair)
        {
            pair.second.fastabi = true;
        });

        return result;
    }

    struct factory_info
    {
        TypeDef type;
        bool activatable{};
        bool statics{};
        bool composable{};
        bool visible{};
    };

    static auto get_factories(writer& w, TypeDef const& type)
    {
        auto get_system_type = [&](auto&& signature) -> TypeDef
        {
            for (auto&& arg : signature.FixedArgs())
            {
                if (auto type_param = std::get_if<ElemSig::SystemType>(&std::get<ElemSig>(arg.value).value))
                {
                    return type.get_cache().find_required(type_param->name);
                }
            }

            return {};
        };

        std::map<std::string, factory_info> result;

        for (auto&& attribute : type.CustomAttribute())
        {
            auto attribute_name = attribute.TypeNamespaceAndName();

            if (attribute_name.first != "Windows.Foundation.Metadata")
            {
                continue;
            }

            auto signature = attribute.Value();
            factory_info info;

            if (attribute_name.second == "ActivatableAttribute")
            {
                info.type = get_system_type(signature);
                info.activatable = true;
            }
            else if (attribute_name.second == "StaticAttribute")
            {
                info.type = get_system_type(signature);
                info.statics = true;
            }
            else if (attribute_name.second == "ComposableAttribute")
            {
                info.type = get_system_type(signature);
                info.composable = true;

                for (auto&& arg : signature.FixedArgs())
                {
                    if (auto visibility = std::get_if<ElemSig::EnumValue>(&std::get<ElemSig>(arg.value).value))
                    {
                        info.visible = std::get<int32_t>(visibility->value) == 2;
                        break;
                    }
                }
            }
            else
            {
                continue;
            }

            std::string name;

            if (info.type)
            {
                name = w.write_temp("%", info.type);
            }

            result[name] = std::move(info);
        }

        return result;
    }

    static bool wrap_abi(TypeSig const& signature)
    {
        bool wrap{};

        call(signature.Type(),
            [&](ElementType type)
        {
            wrap = type == ElementType::String || type == ElementType::Object;
        },
            [&](auto&&)
        {
            wrap = true;
        });

        return wrap;
    }

    static bool is_object(TypeSig const& signature)
    {
        bool object{};

        call(signature.Type(),
            [&](ElementType type)
        {
            if (type == ElementType::Object)
            {
                object = true;
            }
        },
            [](auto&&) {});

        return object;
    }

    static auto get_delegate_method(TypeDef const& type)
    {
        auto methods = type.MethodList();

        auto method = std::find_if(begin(methods), end(methods), [](auto&& method)
        {
            return method.Name() == "Invoke";
        });

        if (method == end(methods))
        {
            throw_invalid("Delegate's Invoke method not found");
        }

        return method;
    }

    static std::string get_field_abi(writer& w, Field const& field)
    {
        auto signature = field.Signature();
        auto const& type = signature.Type();
        std::string name = w.write_temp("%", type);

        if (starts_with(name, "struct "))
        {
            auto ref = std::get<coded_index<TypeDefOrRef>>(type.Type());
            XLANG_ASSERT(ref.type() == TypeDefOrRef::TypeRef);

            name = "struct{";

            for (auto&& nested : find_required(ref.TypeRef()).FieldList())
            {
                name += " " + get_field_abi(w, nested) + " ";
                name += nested.Name();
                name += ";";
            }

            name += " }";
        }

        return name;
    }

    static std::string get_component_filename(TypeDef const& type)
    {
        std::string result{ type.TypeNamespace() };
        result += '.';
        result += type.TypeName();

        if (!settings.component_name.empty() && starts_with(result, settings.component_name))
        {
            result = result.substr(settings.component_name.size());

            if (starts_with(result, "."))
            {
                result.erase(result.begin());
            }
        }

        return result;
    }

    static std::string get_generated_component_filename(TypeDef const& type)
    {
        auto result = get_component_filename(type);

        if (!settings.component_prefix)
        {
            std::replace(result.begin(), result.end(), '.', '/');
        }

        return result;
    }

    static bool has_factory_members(writer& w, TypeDef const& type)
    {
        for (auto&&[factory_name, factory] : get_factories(w, type))
        {
            if (!factory.type || !empty(factory.type.MethodList()))
            {
                return true;
            }
        }

        return false;
    }

    static bool is_composable(writer& w, TypeDef const& type)
    {
        for (auto&&[factory_name, factory] : get_factories(w, type))
        {
            if (factory.composable)
            {
                return true;
            }
        }

        return false;
    }

    static bool has_composable_constructors(writer& w, TypeDef const& type)
    {
        for (auto&&[interface_name, factory] : get_factories(w, type))
        {
            if (factory.composable && !empty(factory.type.MethodList()))
            {
                return true;
            }
        }

        return false;
    }

    static bool has_projected_types(cache::namespace_members const& members)
    {
        return
            !members.interfaces.empty() ||
            !members.classes.empty() ||
            !members.enums.empty() ||
            !members.structs.empty() ||
            !members.delegates.empty();
    }
}
