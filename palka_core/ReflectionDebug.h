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
        enum valueType
        {
            INT, FLOAT, DOUBLE, STRING, BOOL, ARRAY, UINT, ENUM, POINTER, NONE
        };

        inline valueType checkType(const rttr::variant& value)
        {
            if (value.is_type<std::string>() || value.is_type<std::string_view>())
                return valueType::STRING;
            else if (value.get_type().is_class())
                return NONE;
            else if (value.is_type<float>())
                return valueType::FLOAT;
            else if (value.is_type<int>())
                return valueType::INT;
            else if (value.is_type<unsigned int>())
                return valueType::UINT;
            else if (value.is_type<double>())
                return valueType::DOUBLE;
            else if (value.is_type<bool>())
                return valueType::BOOL;
            else if (value.get_type().is_array())
                return valueType::ARRAY;
            else if (value.get_type().is_enumeration())
                return valueType::ENUM;
            else if (value.get_type().is_pointer())
                return valueType::POINTER;
            return NONE;
        }

        inline bool wrapped_check(const rttr::variant& value)
        {
            if (value.get_type().is_wrapper())
                return true;
            else
                return false;
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
                    if (!is_array && ImGui::BeginPopupContextItem(prop_value.get_type().get_name().data()))
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
                case UINT:
                {
                    auto i = prop_value.get_value<unsigned int>();
                    ImGui::Text("%s = %i", name.data(), i);
                    if (!is_array && ImGui::BeginPopupContextItem(prop_value.get_type().get_name().data()))
                    {
                        unsigned int changedValue = i;
                        if (ImGui::Selectable("Set to zero")) changedValue = 0.0f;
                        ImGui::PushItemWidth(200);
                        int min = 0;
                        int max = 2100;
                        ImGui::DragScalar(name.data(), ImGuiDataType_U32, &changedValue, 1.f, &min, &max);
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
                    if (!is_array && ImGui::BeginPopupContextItem(prop_value.get_type().get_name().data()))
                    {
                        float changedValue = i;
                        if (ImGui::Selectable("Set to zero")) changedValue = 0.0f;
                        ImGui::PushItemWidth(200);
                        ImGui::DragFloat(name.data(), &changedValue, 1.f, -2000.f, 2000.f);
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
                    if (!is_array && ImGui::BeginPopupContextItem(prop_value.get_type().get_name().data()))
                    {
                        bool changedValue = i;
                        if (ImGui::Selectable("Set to zero")) changedValue = false;
                        ImGui::PushItemWidth(200);
                        ImGui::Checkbox(name.data(), &changedValue);
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
                case ENUM:
                {
                    auto i = prop_value.to_string();
                    ImGui::Text("%s = %s", name.data(), i.c_str());
                    enumeration enum_align = prop_value.get_type().get_enumeration();
                    if (!is_array && ImGui::BeginPopupContextItem(prop_value.get_type().get_name().data()))
                    {
                        static auto changedValue = i;
                        if (ImGui::Selectable("Set to zero")) changedValue = "";
                        ImGui::PushItemWidth(200);
                        auto values = enum_align.get_names();
                        if (ImGui::BeginCombo("##combo", changedValue.c_str()))
                        {
                            for (auto& v : values)
                            {
                                bool is_selected = (changedValue == v);
                                if (ImGui::Selectable(v.data(), is_selected))
                                    changedValue = v.data();
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                        if (changedValue != i)
                        {
                            prop.set_value(instance, enum_align.name_to_value(changedValue));
                            v_change = true;
                        }
                        ImGui::PopItemWidth();
                        ImGui::EndPopup();
                    }
                }
                    break;
                case POINTER:
                {

                }
                    break;
                default:

                    break;
            }
            ImGui::Spacing();
            ImGui::PopID();
            return v_change;
        }

        template<class T>
        inline rttr::variant reflect(const rttr::variant& value, T& instance, std::string_view name = "", int id = 0)
        {
            static bool v_change = false;
            rttr::type type = value.get_type();
            rttr::variant _value;
            ImGui::PushID(id);
            if (type.is_valid() && type.is_class())
            {
                if (type.is_wrapper())
                {
                    _value = value.extract_wrapped_value();
                    type = _value.get_type();
                } else
                    _value = value;
                if (ImGui::TreeNode((void*) (id + type.get_id()), "%s", (name.empty()) ? type.get_name().to_string().c_str() : name.data()))
                {
                    for (auto& prop : type.get_properties())
                    {
                        rttr::variant prop_value = prop.get_value(_value);
                        rttr::type prop_type = prop.get_type();
                        std::string_view prop_name = prop.get_name().data();
                        if (prop_type.is_valid() && prop_type.is_class() && checkType(prop_value) == NONE)
                        {
                            auto top_value = reflect(prop_value, instance, prop.get_name().to_string(), ++id);
                            if (_value.get_type() == rttr::type::get(instance))
                            {
                                if (v_change)
                                {
                                    _value.get_type().set_property_value(prop.get_name(), instance, top_value);
                                    v_change = false;
                                }
                            } else
                            {
                                if (v_change)
                                    _value.get_type().set_property_value(prop.get_name(), _value, top_value);
                            }
                        } else
                        {
                            bool ret = property_get(prop.get_name().to_string(), prop, _value); //this is a top-level property and you need to notify about its change,
                                                                                                // so if we changed it, we change it for _value, if _value is the original object,
                                                                                                // then we apply the changes immediately to it
                                                                                                //If _value is a nested object, then we must apply all the changes higher up the hierarchy, so v_change=true
                            v_change = (v_change) ? v_change : ret;
                            if (ret && !prop_type.is_class())
                            {
                                auto _val = prop.get_value(_value);
                                if (_value.get_type() == rttr::type::get(instance))
                                {
                                    _value.get_type().set_property_value(prop_name.data(), instance, _val);
                                    v_change = false;
                                } else
                                    _value.get_type().set_property_value(prop_name.data(), _value, _val);
                            }
                        }
                    }
                    ImGui::TreePop();
                }
            } else
            {
                assert(!"this is not a class");
            }
            ImGui::PopID();
            return {_value};
        }
    }

    template<class T>
    inline void debug(const T& val, std::string name = "")
    {
        ImGui::Begin("ReflectionDebug");
        utility::reflect(rttr::variant(val), val, name);
        ImGui::End();
    }
}
#endif //PALKA_REFLECTIONDEBUG_H
