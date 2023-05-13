#include "Precompiled.h"

#include "editor/extension.h"

namespace imgui_editor
{
	void sscanf2(const char* format, const char* data, void* value)
	{
		std::istringstream stream(data);

		for (size_t i = 0, max = strlen(format); i < max; ++i)
		{
			if (format[i] == '%')
			{
				switch (format[i + 1])
				{
				case 'b':
				{
					bool read = false;
					stream >> read;
					*(bool*)value = read;
					value = (char*)value + sizeof(bool);
					++i;
				}
				break;
				case 'd':
				{
					int read = 0;
					stream >> read;
					*(int*)value = read;
					value = (char*)value + sizeof(int);
					++i;
				}
				break;
				case 's':
				{
					std::string read = read_string(stream);
					*(std::string*)value = read;
					value = (char*)value + sizeof(std::string);
					++i;
				}
				break;
				case 'f':
				{
					float read = 0;
					stream >> read;
					*(float*)value = read;
					value = (char*)value + sizeof(float);
					++i;
				}
				break;
				default:
					debug_break();
				}
			}
			else
			{
				char c;
				stream >> c;
			}
		}
	}

	std::string read_string(std::istringstream& stream)
	{
		std::string result;
		char c;
		bool isStart = false;
		bool isEscape = false;
		while (stream.get(c))
		{
			if (c == '"')
			{
				if (isStart)
				{
					if (isEscape)
					{
						result += c;
						isEscape = false;
					}
					else
					{
						break;
					}
				}
				else
				{
					isStart = true;
				}
			}
			else
			{
				if (isEscape)
				{
					result += '\\';
					isEscape = false;
				}
				if (c == '\\')
				{
					isEscape = true;
				}
				else
				{
					result += c;
				}
			}
		}
		return result;
	}
}

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