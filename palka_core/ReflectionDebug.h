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

        inline void property_get(std::string_view name, const rttr::variant& _prop_value)
        {
            auto prop_value = wrapped_check(_prop_value) ? _prop_value.extract_wrapped_value() : _prop_value;
            ImGui::PushID(&prop_value);
            switch (checkType(prop_value))
            {
                case INT:
                {
                    auto i = prop_value.get_value<int>();
                    ImGui::Text("%s = %i", name.data(), i);
                }
                    break;
                case FLOAT:
                {
                    auto i = prop_value.get_value<float>();
                    ImGui::Text("%s = %f", name.data(), i);
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
                                        property_get(format, view_array.get_value(index));
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
                                property_get(format, i);
                            }
                        }
                        ImGui::TreePop();
                    }
                }
                    break;
            }
            ImGui::Spacing();
            ImGui::PopID();
        }

        inline void reflect(const rttr::variant& value, int id = 0, std::string_view name = "")
        {
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
                        if (prop_type.is_valid() && prop_type.is_class())
                            reflect(prop_value, ++id, prop.get_name().to_string());
                        else
                            property_get(prop.get_name().to_string(), prop_value);
                    }
                    ImGui::TreePop();
                }
            } else
                property_get(type.get_name().to_string(), value);
            ImGui::PopID();
        }
    }

    template<class T>
    inline void draw(const T& val)
    {
        ImGui::Begin("Debug");
        utility::reflect(rttr::variant(val));
        ImGui::End();
    }
}
#endif //PALKA_REFLECTIONDEBUG_H
