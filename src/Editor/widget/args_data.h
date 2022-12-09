#ifndef __ARGS_DATA_H__
#define __ARGS_DATA_H__

namespace imgui_editor
{	
	struct widget_none {};
	
#pragma region // Windows
	struct widget_begin_end_window
	{
		bool open = true;
		ImGuiWindowFlags_ flags;
	};

	struct widget_begin_end_child
	{
		bool border = 1;
		ImGuiWindowFlags_ flags;
	};
#pragma endregion // Windows

#pragma region // Parameters stacks (current window)	
	struct widget_push_pop_item_width
	{
		float item_width;
	};

	struct widget_push_pop_text_wrap_pos
	{
		float item_width;
	};
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
	struct widget_separator { };

	struct widget_same_line
	{
		float offset_from_start_x = 0.0f;
		float spacing = -1.0f;
	};

	struct widget_spacing { };

	struct widget_dummy
	{
	};

	struct widget_indent
	{
		float indent_w = 0.0f;
	};

	struct widget_unindent
	{
		float indent_w = 0.0f;
	};

	struct widget_begin_end_group { };
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text	
	struct widget_text {};

	struct widget_text_colored
	{
		ImColor color;
	};

	struct widget_label_text
	{
		std::string text;
	};

	struct widget_bullet_text { };
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
	struct widget_button { };

	struct widget_small_button { };

	struct widget_checkbox
	{
		bool check = false;
	};

	struct widget_checkbox_flags
	{
		int flags = 0;
		int flags_value = 0;
	};

	struct widget_radio_button
	{
		bool active = false;
	};

	struct widget_bullet { };
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
	struct widget_begin_end_combo
	{
		std::string preview_value;
		ImGuiComboFlags_ flags;
	};
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
	struct widget_drag_float
	{
		float value;
		float speed;
		float min;
		float max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_drag_float2
	{
		float value[2];
		float speed;
		float min;
		float max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_drag_float3
	{
		float value[3];
		float speed;
		float min;
		float max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_drag_float4
	{
		float value[4];
		float speed;
		float min;
		float max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_drag_int
	{
		int value;
		float speed;
		int min;
		int max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_drag_int2
	{
		int value[2];
		float speed;
		int min;
		int max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_drag_int3
	{
		int value[3];
		float speed;
		int min;
		int max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_drag_int4
	{
		int value[4];
		float speed;
		int min;
		int max;
		std::string format;
		ImGuiSliderFlags_ flags;
	};
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
	struct widget_slider_float
	{
		float value = 0.0f;
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_float2
	{
		float value[2] = {0.0f,};
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_float3
	{
		float value[3] = {0.0f,};
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_float4
	{
		float value[4] = {0.0f,};
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_angle
	{
		float value = 0.0f;
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_int
	{
		int value = 0;
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_int2
	{
		int value[2] = {0,};
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_int3
	{
		int value[3] = {0,};
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags_ flags;
	};

	struct widget_slider_int4
	{
		int value[4] = {0,};
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags_ flags;
	};
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
	struct widget_input_text
	{
		std::string text;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_text_multiline
	{
		std::string text;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_text_with_hint
	{
		std::string text;
		std::string hint;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_float
	{
		float value;
		float step;
		float step_fast;
		std::string format;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_float2
	{
		float value[2];
		std::string format;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_float3
	{
		float value[3];
		std::string format;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_float4
	{
		float value[4];
		std::string format;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_int
	{
		int value;
		int step;
		int step_fast;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_int2
	{
		int value[2];
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_int3
	{
		int value[3];
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_int4
	{
		int value[4];
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_double
	{
		double value;
		double step;
		double step_fast;
		std::string format;
		ImGuiInputTextFlags_ flags;
	};
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
	struct widget_color_edit3
	{
		float value[3] = {0.0f,};
		ImGuiColorEditFlags_ flags;
	};

	struct widget_color_edit4
	{
		float value[4] = {0.0f,};
		ImGuiColorEditFlags_ flags;
	};

	struct widget_color_picker3
	{
		float value[3] = {0.0f,};
		ImGuiColorEditFlags_ flags;
	};

	struct widget_color_picker4
	{
		float value[4] = {0.0f,};
		ImGuiColorEditFlags_ flags;
	};

	struct widget_color_button
	{
		ImVec4 col;
		ImGuiColorEditFlags_ flags;
		ImVec2 size;
	};
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
	struct widget_push_pop_tree_node
	{
		ImGuiTreeNodeFlags_ flags;
	};

	struct widget_collapsing_header
	{
		ImGuiTreeNodeFlags_ flags;
	};
#pragma endregion // Widgets: Trees

#pragma region // Widgets: Selectables
	struct widget_selectable
	{
		bool selected = false;
		ImGuiSelectableFlags_ flags;
	};
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
	struct widget_begin_end_list_box
	{
		int items_count;
		int items_height;
	};
#pragma endregion // Widgets: List Boxes
		
#pragma region // Widgets: Menus
	struct widget_begin_end_menu
	{
		bool enabled = true;
	};
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
	struct widget_begin_end_popup
	{
		ImGuiWindowFlags_ flags;
	};	
#pragma endregion // Popups, Modals
		
#pragma region // Tables
	struct widget_begin_end_table
	{
		int columns = 1;
		ImGuiTableFlags_ flags;
		ImVec2 outer_size;
		float inner_width = 0;
	};
#pragma endregion // Tables
}

#endif