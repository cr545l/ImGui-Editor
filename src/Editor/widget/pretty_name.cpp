#include <magic_enum/magic_enum.hpp>

#include "Precompiled.h"
#include "editor/imgui_editor.h"
#include "editor/widget.h"

namespace imgui_editor
{
	const char* get_widget_name(widget_type type)
	{
		std::string name(magic_enum::enum_name(type));
		name.insert(0, "widget_name.");
		return get_language_text(name.c_str());
	}

	const char* get_widget_description(widget_type type)
	{
		std::string name(magic_enum::enum_name(type));
		name.insert(0, "widget_description.");
		return get_language_text(name.c_str());
	}
	
	const char* get_col_name(ImGuiCol_ type)
	{
		std::string name(magic_enum::enum_name(type));
		name.insert(0, "ImGuiCol_name.");
		return get_language_text(name.c_str());	    
	}
	const char* get_col_description(ImGuiCol_ type)
	{
		std::string name(magic_enum::enum_name(type));
		name.insert(0, "ImGuiCol_description.");
		return get_language_text(name.c_str());
	}

	const char* get_style_var_name(ImGuiStyleVar_ type)
	{
		std::string name(magic_enum::enum_name(type));
		name.insert(0, "ImGuiStyleVar_name.");
		return get_language_text(name.c_str());
	}
	const char* get_style_var_description(ImGuiStyleVar_ type)
	{
		std::string name(magic_enum::enum_name(type));
		name.insert(0, "ImGuiStyleVar_description.");
		return get_language_text(name.c_str());	    
	}
}
