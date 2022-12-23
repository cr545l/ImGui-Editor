#ifndef __IMGUI_EX_H__
#define __IMGUI_EX_H__

#include <algorithm>
#include <magic_enum/magic_enum.hpp>
#include <sstream>

namespace imgui_editor
{
	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiSelectableFlags_& flags)
	{
		int i = 0;
		stream >> i;
		flags = (ImGuiSelectableFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiCol_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiCol_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiStyleVar_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiStyleVar_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiInputTextFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiInputTextFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiColorEditFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiColorEditFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiSliderFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiSliderFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiTreeNodeFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiTreeNodeFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiWindowFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiWindowFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiTableFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiTableFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiComboFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiComboFlags_)i;
		return stream;
	}

	inline std::istringstream& operator>> (std::istringstream& stream, ImGuiTableRowFlags_& col)
	{
		int i = 0;
		stream >> i;
		// col = (ImGuiTableRowFlags_)i;
		return stream;
	}    

	template<typename ... Args>
	std::string safe_string_format(const std::string& format, Args ... args)
	{
		std::string safe_format = format;

		static const std::string search = "%s";
		static const std::string replace = "\"%s\"";

		size_t pos = 0;
		while ((pos = safe_format.find(search, pos)) != std::string::npos)
		{
			safe_format.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		
		int size = snprintf(nullptr, 0, safe_format.c_str(), args ...) + 1; // Extra space for '\0'
		assert( 0< size );
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, safe_format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}

	CR_EXPORT void sscanf2(const char* format, const char* data, void* value);

	inline std::string to_safe_string(const std::string& v) 
	{
		std::string s = v;

		static const std::string search = "\"";
		static const std::string replace = "\\\"";

		size_t pos = 0;
		while ((pos = s.find(search, pos)) != std::string::npos)
		{
			s.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return s;
	}

	inline std::string read_string(std::istringstream& stream)
	{
		std::string result;
		char c;
		bool isStart = false;
		bool isEscape = false;
		while(stream.get(c))
		{
			if(c == '"')
			{
				if(isStart)
				{
					if(isEscape)
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
				if(isEscape)
				{
					result += '\\';
					isEscape = false;
				}
				if(c == '\\')
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
    bool InputTexts(const char* baseLabel, std::vector<std::string>& value, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    
    template <typename T>
	inline std::string ToString(T t)
	{
        std::string name = std::string(magic_enum::enum_name(t));
		return name;
	}

    template <>
	inline std::string ToString(ImGuiWindowFlags_ t)
	{
		switch(t)
		{
			case ImGuiWindowFlags_None: return "ImGuiWindowFlags_None";
			case ImGuiWindowFlags_NoTitleBar: return "ImGuiWindowFlags_NoTitleBar";
			case ImGuiWindowFlags_NoResize: return "ImGuiWindowFlags_NoResize";
			case ImGuiWindowFlags_NoMove: return "ImGuiWindowFlags_NoMove";
			case ImGuiWindowFlags_NoScrollbar: return "ImGuiWindowFlags_NoScrollbar";
			case ImGuiWindowFlags_NoScrollWithMouse: return "ImGuiWindowFlags_NoScrollWithMouse";
			case ImGuiWindowFlags_NoCollapse: return "ImGuiWindowFlags_NoCollapse";
			case ImGuiWindowFlags_AlwaysAutoResize: return "ImGuiWindowFlags_AlwaysAutoResize";
			case ImGuiWindowFlags_NoBackground: return "ImGuiWindowFlags_NoBackground";
			case ImGuiWindowFlags_NoSavedSettings: return "ImGuiWindowFlags_NoSavedSettings";
			case ImGuiWindowFlags_NoMouseInputs: return "ImGuiWindowFlags_NoMouseInputs";
			case ImGuiWindowFlags_MenuBar: return "ImGuiWindowFlags_MenuBar";
			case ImGuiWindowFlags_HorizontalScrollbar: return "ImGuiWindowFlags_HorizontalScrollbar";
			case ImGuiWindowFlags_NoFocusOnAppearing: return "ImGuiWindowFlags_NoFocusOnAppearing";
			case ImGuiWindowFlags_NoBringToFrontOnFocus: return "ImGuiWindowFlags_NoBringToFrontOnFocus";
			case ImGuiWindowFlags_AlwaysVerticalScrollbar: return "ImGuiWindowFlags_AlwaysVerticalScrollbar";
			case ImGuiWindowFlags_AlwaysHorizontalScrollbar: return "ImGuiWindowFlags_AlwaysHorizontalScrollbar";
			case ImGuiWindowFlags_AlwaysUseWindowPadding: return "ImGuiWindowFlags_AlwaysUseWindowPadding";
			case ImGuiWindowFlags_NoNavInputs: return "ImGuiWindowFlags_NoNavInputs";
			case ImGuiWindowFlags_NoNavFocus: return "ImGuiWindowFlags_NoNavFocus";
			case ImGuiWindowFlags_UnsavedDocument: return "ImGuiWindowFlags_UnsavedDocument";
			case ImGuiWindowFlags_NoNav: return "ImGuiWindowFlags_NoNav";
			case ImGuiWindowFlags_NoDecoration: return "ImGuiWindowFlags_NoDecoration";
			case ImGuiWindowFlags_NoInputs: return "ImGuiWindowFlags_NoInputs";
			case ImGuiWindowFlags_NavFlattened: return "ImGuiWindowFlags_NavFlattened";
			case ImGuiWindowFlags_ChildWindow: return "ImGuiWindowFlags_ChildWindow";
			case ImGuiWindowFlags_Tooltip: return "ImGuiWindowFlags_Tooltip";
			case ImGuiWindowFlags_Popup: return "ImGuiWindowFlags_Popup";
			case ImGuiWindowFlags_Modal: return "ImGuiWindowFlags_Modal";
			case ImGuiWindowFlags_ChildMenu: return "ImGuiWindowFlags_ChildMenu";
		}
	}

    template <typename T>
    std::string GetEnumName(const T& value, bool bit_flag = true)
    {
        constexpr std::string_view type_name =  magic_enum::enum_type_name<T>();

        std::string name = "";
        if(bit_flag)
        {
            magic_enum::enum_for_each<T>([&](T t) {
                if (static_cast<int>(t) & static_cast<int>(value))
                {
                    if (name.length())
                    {
                        name += "|";
                    }
                    std::string n = ToString(t);
                    n = n.substr(type_name.length(), n.length() - type_name.length());
                    std::replace(n.begin(), n.end(), '_', ' ');
                    name += n;
                }

            std::string name = ToString(t);
            // name = name.substr(12, name.length() - 12);
            std::replace(name.begin(), name.end(), '_', ' ');
            
            });
        }
        else
        {
            std::string n = ToString(value);
            n = n.substr(type_name.length(), n.length() - type_name.length());
            std::replace(n.begin(), n.end(), '_', ' ');
            name = n;
        }
        return name;
    }

    template <typename T>
    bool Combo(const char* label, T* value, bool bit_flag = true)
    {
        constexpr std::string_view type_name =  magic_enum::enum_type_name<T>();
        bool result = false;

        if (ImGui::BeginCombo(label, GetEnumName(*value, bit_flag).c_str()))
        {
            magic_enum::enum_for_each<T>([&](T t) {
                std::string name = GetEnumName(t, false);
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

    template <>
    inline bool Combo(const char* label, ImGuiWindowFlags_* value, bool bit_flag)
    {
        constexpr std::string_view type_name =  magic_enum::enum_type_name<ImGuiWindowFlags_>();
        bool result = false;

        if (ImGui::BeginCombo(label, GetEnumName(*value, bit_flag).c_str()))
        {
			constexpr ImGuiWindowFlags_ enums [] = {
				ImGuiWindowFlags_None,
				ImGuiWindowFlags_NoTitleBar,
				ImGuiWindowFlags_NoResize,
				ImGuiWindowFlags_NoMove,
				ImGuiWindowFlags_NoScrollbar,
				ImGuiWindowFlags_NoScrollWithMouse,
				ImGuiWindowFlags_NoCollapse,
				ImGuiWindowFlags_AlwaysAutoResize,
				ImGuiWindowFlags_NoBackground,
				ImGuiWindowFlags_NoSavedSettings,
				ImGuiWindowFlags_NoMouseInputs,
				ImGuiWindowFlags_MenuBar,
				ImGuiWindowFlags_HorizontalScrollbar,
				ImGuiWindowFlags_NoFocusOnAppearing,
				ImGuiWindowFlags_NoBringToFrontOnFocus,
				ImGuiWindowFlags_AlwaysVerticalScrollbar,
				ImGuiWindowFlags_AlwaysHorizontalScrollbar,
				ImGuiWindowFlags_AlwaysUseWindowPadding,
				ImGuiWindowFlags_NoNavInputs,
				ImGuiWindowFlags_NoNavFocus,
				ImGuiWindowFlags_UnsavedDocument,
				ImGuiWindowFlags_NoNav,
				ImGuiWindowFlags_NoDecoration,
				ImGuiWindowFlags_NoInputs,
				ImGuiWindowFlags_NavFlattened,
				ImGuiWindowFlags_ChildWindow,
				ImGuiWindowFlags_Tooltip,
				ImGuiWindowFlags_Popup,
				ImGuiWindowFlags_Modal,
				ImGuiWindowFlags_ChildMenu
			};

			for(size_t i = 0, max = sizeof(enums) / sizeof(enums[0]); i < max; ++i)
			{
				ImGuiWindowFlags_ t = enums[i];
				std::string name = GetEnumName(t, false);
				if (ImGui::Selectable(name.c_str(), bit_flag?static_cast<int>(t) & static_cast<int>(*value) : t == *value))
				{
					if (bit_flag && ImGui::GetIO().KeyCtrl)
					{
						*value = static_cast<ImGuiWindowFlags_>(static_cast<int>(*value) | static_cast<int>(t));
					}
					else
					{
						*value = t;
					}
					result = true;
				}
			}
            ImGui::EndCombo();
        }
        return result;
    }
}

#endif