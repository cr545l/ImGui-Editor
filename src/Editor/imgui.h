#include "Precompiled.h"

#include <algorithm>
#include <magic_enum.hpp>

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	assert( 0< size );
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

namespace ImGui
{
    bool InputTexts(const char* baseLabel, std::vector<std::string>& value, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL)
    {
        bool result = false;

        int size =value.size();
        if(ImGui::InputInt(baseLabel, (int*)&size))
        {
            if (size < 0)
            {
                size = 0;
            }

            if ((int)value.size() < size)
            {
                value.push_back("new item");
            }
            else
            {
                value.resize(size);
            }
        }
        for(size_t i =0, max = value.size(); i < max; ++i)
        {
            ImGui::PushID(i);
            result = ImGui::InputText(string_format("%s[%u]", baseLabel, i).c_str(), &value[i], flags, callback, user_data);
            ImGui::PopID();
        }
        return result;
    }

    template <typename T>
    bool Combo(const char* label, T* value)
    {
        constexpr std::string_view type_name =  magic_enum::enum_type_name<T>();

        bool result = false;
        std::string name = "";
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

        if (ImGui::BeginCombo(label, name.c_str()))
        {
            magic_enum::enum_for_each<T>([&](T t) {
                std::string name = std::string(magic_enum::enum_name(t));
                name = name.substr(type_name.length(), name.length() - type_name.length());
                // name replace _ to space
                std::replace(name.begin(), name.end(), '_', ' ');
                if (ImGui::Selectable(name.c_str(), static_cast<int>(t) & static_cast<int>(*value)))
                {
                    if (ImGui::GetIO().KeyCtrl)
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