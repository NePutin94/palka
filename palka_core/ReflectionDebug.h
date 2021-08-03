//
// Created by NePutin on 7/10/2021.
//
#ifndef PALKA_REFLECTIONDEBUG_H
#define PALKA_REFLECTIONDEBUG_H

#include <imgui.h>
#include <string>
#include <rttr/type>
#include <rttr/visitor.h>
#include <rttr/variant.h>

namespace palka
{
    namespace utility
    {
        struct DebugTree
        {
        RTTR_ENABLE()
        };

        enum valueType
        {
            INT, FLOAT, DOUBLE, STRING, BOOL, ARRAY
        };

        inline valueType checkType(const rttr::variant& value)
        {
            if (value.is_type<float>())
                return valueType::FLOAT;
            else if (value.is_type<std::string>() || value.is_type<std::string_view>())
                return valueType::STRING;
            else if (value.is_type<int>())
                return valueType::INT;
            else if (value.is_type<double>())
                return valueType::DOUBLE;
            else if (value.is_type<bool>())
                return valueType::BOOL;
            else if (value.get_type().is_array())
                return valueType::ARRAY;
        }

        inline bool wrapped_check(const rttr::variant& value)
        {
            if (value.get_type().is_wrapper())
                return true;
            else
                return false;
        }

        template<class T>
        inline void toplevel_property_get(std::string_view name, const rttr::property& prop, const T& instance)
        {

        }

        inline bool property_get(std::string_view name, const rttr::property& prop, const rttr::variant& instance, bool is_array = false)
        {
            bool v_change = false;
            rttr::variant prop_value;
            if (is_array)
            {
                prop_value = wrapped_check(instance) ? instance.extract_wrapped_value() : instance;
            } else
            {
                auto _prop_value = prop.get_value(instance);
                prop_value = wrapped_check(_prop_value) ? _prop_value.extract_wrapped_value() : _prop_value;
            }
            ImGui::PushID(&prop_value);
            switch (checkType(prop_value))
            {
                case INT:
                {
                    auto i = prop_value.get_value<int>();
                    ImGui::Text("%s = %i", name.data(), i);
                    if (!is_array && ImGui::BeginPopupContextItem(instance.get_type().get_name().data()))
                    {
                        int changedValue = i;
                        if (ImGui::Selectable("Set to zero")) changedValue = 0.0f;
                        ImGui::PushItemWidth(200);
                        ImGui::DragInt(name.data(), &changedValue, 1.f, -900.f, 900.f);
                        if (changedValue != i)
                        {
                            prop.set_value(instance, changedValue);
                            v_change = true;
                        }
                        ImGui::PopItemWidth();
                        ImGui::EndPopup();
                    }
                }
                    break;
                case FLOAT:
                {
                    auto i = prop_value.get_value<float>();
                    ImGui::Text("%s = %f", name.data(), i);
                    if (!is_array && ImGui::BeginPopupContextItem(instance.get_type().get_name().data()))
                    {
                        float changedValue = i;
                        if (ImGui::Selectable("Set to zero")) changedValue = 0.0f;
                        ImGui::PushItemWidth(200);
                        ImGui::DragFloat(name.data(), &changedValue, 1.f, -900.f, 900.f);
                        if (changedValue != i)
                        {
                            prop.set_value(instance, changedValue);
                            v_change = true;
                        }
                        ImGui::PopItemWidth();
                        ImGui::EndPopup();
                    }
                }
                    break;
                case DOUBLE:
                {
                    auto i = prop_value.get_value<double>();
                    ImGui::Text("%s = %f", name.data(), i);
                }
                    break;
                case STRING:
                {
                    auto i = prop_value.get_value<std::string>();
                    ImGui::Text("%s = %s", name.data(), i.c_str());
                }
                    break;
                case BOOL:
                {
                    auto i = prop_value.get_value<bool>();
                    ImGui::Text("%s = %s", name.data(), (i) ? "true" : "false");
                }
                    break;
                case ARRAY:
                {
                    auto view_array = prop_value.create_sequential_view();
                    auto arr_size = view_array.get_size();
                    auto arr_val_type = view_array.get_value_type();
                    auto arr_val_type_s = view_array.get_value_type().get_name().to_string();
                    std::string out;
                    if (ImGui::TreeNode(&prop_value, "%s, size %llu", name.data(), arr_size))
                    {
                        if (arr_size == 16) //matrix view
                        {
                            if (ImGui::BeginTable("matrixView", 4, ImGuiTableFlags_SizingFixedFit))
                            {
                                int index = 0;
                                for (int i = 0; i < 4; ++i)
                                {
                                    index = i;
                                    ImGui::TableNextRow();
                                    for (int j = 0; j < 4; ++j)
                                    {
                                        ImGui::TableSetColumnIndex(j);
                                        std::string format = "[" + std::to_string(index) + "]";
                                        property_get(format, prop, view_array.get_value(index), true);
                                        index += 4;
                                    }
                                }
                                ImGui::EndTable();
                            }
                        } else
                        {
                            size_t count = 0;
                            for (auto& i : view_array)
                            {
                                std::string format = "[" + std::to_string(++count) + "]";
                                property_get(format, prop, i, true);
                            }
                        }
                        ImGui::TreePop();
                    }
                }
                    break;
            }
            ImGui::Spacing();
            ImGui::PopID();
            return v_change;
        }

        template<class T>
        inline std::pair<rttr::variant, bool> reflect(const rttr::variant& value, T& instance, int id = 0, std::string_view name = "")
        {
            bool v_change = false;
            auto type = value.get_type();
            ImGui::PushID(id);
            if (type.is_valid() && type.is_class())
            {
                if (ImGui::TreeNode((void*) (id + type.get_id()), "%s", (name.empty()) ? type.get_name().to_string().c_str() : name.data()))
                {
                    for (auto& prop : type.get_properties())
                    {
                        rttr::variant prop_value = prop.get_value(value);
                        rttr::type prop_type = prop.get_type();
                        auto test = prop.get_name();
                        if (prop_type.is_valid() && prop_type.is_class())
                        {
                            auto val23 = reflect(prop_value, instance, ++id, prop.get_name().to_string());
                            if (value.get_type() == rttr::type::get(instance))
                            {
                                if (val23.second)
                                    value.get_type().set_property_value(prop.get_name(), instance, val23.first);
                                else
                                {
                                    if (val23.second)
                                        value.get_type().set_property_value(prop.get_name(), value, val23.first);
                                }
                            }
                        } else
                        {
                            bool t = property_get(prop.get_name().to_string(), prop, value);
                            v_change = (v_change) ? v_change : t;
                            if (v_change && !prop_type.is_class() && value.get_type() == rttr::type::get(instance))
                            {
                                if (prop_type == rttr::type::get<int>())
                                {
                                    int _val = prop.get_value(value).to_int();
                                    value.get_type().set_property_value(prop.get_name(), instance, _val);
                                } else if (prop_type == rttr::type::get<float>())
                                {
                                    float _val = prop.get_value(value).to_float();
                                    value.get_type().set_property_value(prop.get_name(), instance, _val);
                                } else if (prop_type == rttr::type::get<double>())
                                {
                                    double _val = prop.get_value(value).to_double();
                                    value.get_type().set_property_value(prop.get_name(), instance, _val);
                                } else if (prop_type == rttr::type::get<std::string>())
                                {
                                    std::string _val = prop.get_value(value).to_string();
                                    value.get_type().set_property_value(prop.get_name(), instance, _val);
                                } else if (prop_type == rttr::type::get<bool>())
                                {
                                    bool _val = prop.get_value(value).to_bool();
                                    value.get_type().set_property_value(prop.get_name(), instance, _val);
                                }
                                v_change = false;
                            }
                        }
                    }
                    ImGui::TreePop();
                }
            } else
            {
                //property_get(type.get_name().to_string(), value);
                int z = 1;
            }
            ImGui::PopID();
            return {value, v_change};
        }
    }

    template<class T>
    inline void draw(const T& val)
    {
        ImGui::Begin("Debug");
        utility::reflect(rttr::variant(val), val);
        ImGui::End();
    }
}
#endif //PALKA_REFLECTIONDEBUG_H
