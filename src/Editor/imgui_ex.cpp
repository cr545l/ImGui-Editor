#include "Precompiled.h"

#include "editor/imgui_ex.h"

namespace ImGui
{
    bool InputTexts(const char* baseLabel, std::vector<std::string>& value, ImGuiInputTextFlags flags , ImGuiInputTextCallback callback , void* user_data )
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
} 