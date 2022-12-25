#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "editor/widget/enum_type.h"

namespace imgui_editor
{
	struct style_color
	{
		ImGuiCol_ idx; 
		ImColor col;
	};

	struct style_var_float
	{
		ImGuiStyleVar_ idx = ImGuiStyleVar_Alpha;
		float val;
	};

	struct style_var_vec2
	{
		ImGuiStyleVar_ idx = ImGuiStyleVar_WindowPadding;
		ImVec2 val;
	};
	
	struct widget
	{
		widget_type type = widget_type::widget_type_none;
		void* args = nullptr;

		std::string label = "empty";
		
		std::vector<widget*> children;

		std::vector<style_color> style_colors;
		std::vector<style_var_float> style_var_floats;
		std::vector<style_var_vec2> style_var_vec2s;

		size_t id = 0;
		widget* parent = nullptr;

		void(*draw)(widget*) = nullptr;
		void(*draw_inspector)(widget*) = nullptr;
	};	

	widget* find(size_t id);
	const char* get_pretty_name(widget_type type);

	int32_t to_fixed_type(widget_type type);
	widget_type to_widget_type(int32_t fixed_type);

	void draw_widget(widget* context);
	void draw_inspector_widget(widget* context);

    IMGUI_EDITOR_EXPORT widget* new_widget(widget_type type);
    IMGUI_EDITOR_EXPORT widget* new_widget_by_id(widget_type type, size_t id);
	IMGUI_EDITOR_EXPORT void* new_widget_arg(widget_type type);
	IMGUI_EDITOR_EXPORT void delete_widget(widget* target);
	IMGUI_EDITOR_EXPORT void delete_widget_args(widget_type type, void* target);

	void parse_args_data(widget_type type, void* data, std::string& inout, std::string& version, bool in);

	inline std::string widget_data_serialize(widget_type type, void* data, std::string& version)
	{
        std::string result;
		assert(nullptr != data);
        parse_args_data(type, data, result, version, false);
        return result;
	}
	
	inline void widget_data_deserialize(widget_type type, void* target, const char* data, std::string& version)
	{
        std::string str2 = data;
        parse_args_data(type, target, str2, version, true);
	}

	std::string widget_serialize(widget* target);
	IMGUI_EDITOR_EXPORT void widget_deserialize(widget* target, const char* data);

	enum class generate_code
	{
		cpp,
	};

	void widget_generate(generate_code code, widget* target, bool root, std::string& result);

	// TODO
	// struct widget_args_required
	// {
	// 	size_t unique_id = 0;
	// 	widget_type type = widget_type::widget_type_none;
	// 	const char* pretty_name = nullptr;
	// 	void*(* new_args)() = nullptr;
	// 	void(* delete_args)(void*) = nullptr;
	// 	void(* on_gui)(void*) = nullptr;
	// 	void(* on_inspector)(void*) = nullptr;
	// 	std::string(*serialize)(const char*&);
	// 	void(*deserialize)(void*, const char*, const std::string&);
	// 	std::string(*gen)(const generate_code&, void*);
	// };

	// widget_args_required& get_widget_args_required(widget_type type);
}

#endif
