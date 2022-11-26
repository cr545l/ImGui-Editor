#ifndef __IMGUI_EX_H__
#define __IMGUI_EX_H__

#include <magic_enum.hpp>
#include <algorithm>

namespace imgui_editor
{
    template<typename ... Args>
    std::string string_format(const std::string& format, Args ... args)
    {
        int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        assert( 0< size );
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }
}

namespace ImGui
{
    bool InputTexts(const char* baseLabel, std::vector<std::string>& value, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    
    template <typename T>
    bool Combo(const char* label, T* value, bool bit_flag = true)
    {
        constexpr std::string_view type_name =  magic_enum::enum_type_name<T>();

        bool result = false;
        std::string name = "";
        if(bit_flag)
        {
            magic_enum::enum_for_each<T>([&](T t) {
                if (static_cast<int>(t) & static_cast<int>(*value))
                {
                    if (name.length())
                    {
                        name += "|";
                    }
                    std::string n = std::string(magic_enum::enum_name(t));
                    n = n.substr(type_name.length(), n.length() - type_name.length());
                    std::replace(n.begin(), n.end(), '_', ' ');
                    name += n;
                }

            std::string name = std::string(magic_enum::enum_name(t));
            // name = name.substr(12, name.length() - 12);
            std::replace(name.begin(), name.end(), '_', ' ');
            
            });
        }
        else
        {
            std::string n = std::string(magic_enum::enum_name(*value));
            n = n.substr(type_name.length(), n.length() - type_name.length());
            std::replace(n.begin(), n.end(), '_', ' ');
            name = n;
        }

        if (ImGui::BeginCombo(label, name.c_str()))
        {
            magic_enum::enum_for_each<T>([&](T t) {
                std::string name = std::string(magic_enum::enum_name(t));
                name = name.substr(type_name.length(), name.length() - type_name.length());
                // name replace _ to space
                std::replace(name.begin(), name.end(), '_', ' ');
                if (ImGui::Selectable(name.c_str(), bit_flag?static_cast<int>(t) & static_cast<int>(*value) : t == *value))
                {
                    if (bit_flag && ImGui::GetIO().KeyCtrl)
                    {
                        *value = static_cast<T>(static_cast<int>(*value) | static_cast<int>(t));
                    }
                    else
                    {
                        *value = t;
                    }
                    result = true;
                } 
                });
            ImGui::EndCombo();
        }
        return result;
    }
}

#endif