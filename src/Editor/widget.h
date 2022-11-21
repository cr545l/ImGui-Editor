#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "Editor/widget_type.h"

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
		std::string label = "empty";
		std::vector<widget*> children;

		ImVec2 size;
		widget_type type = widget_type::widget_type_none;

		void* args = nullptr;

		std::vector<style_color> style_colors;
		std::vector<style_var_float> style_var_floats;
		std::vector<style_var_vec2> style_var_vec2s;

		void(*draw)(widget*) = nullptr;
		void(*draw_inspector)(widget*) = nullptr;
	};

	void draw_widget(widget* context);
	void draw_inspector_widget(widget* context);

	widget* new_widget(widget_type type);
	void delete_widget(widget* target);

	void attach_child(widget* parent, widget* child);
}

#endif
