#ifndef __WIDGET_DATA_H__
#define __WIDGET_DATA_H__

namespace imgui_editor
{	
	struct widget_none {};

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

	struct widget_text {};

	struct widget_text_colored
	{
		ImColor color;
	};

	struct widget_bullet_text { };

	struct widget_bullet { };

	struct widget_selectable
	{
		bool selected = false;
		ImGuiSelectableFlags_ flags;
	};

	struct widget_label_text
	{
		std::string text;
	};

	struct widget_input_text
	{
		std::string text;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_text_multiline
	{
		std::string text;
		ImVec2 size;
		ImGuiInputTextFlags_ flags;
	};

	struct widget_input_text_with_hint
	{
		std::string text;
		std::string hint;
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

	struct widget_input_double
	{
		double value;
		double step;
		double step_fast;
		std::string format;
		ImGuiInputTextFlags_ flags;
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

	struct widget_list_box
	{
		int current_item = 0;
		std::vector<std::string> items;
		int height_in_items = -1;
	};

	struct widget_same_line
	{
		float offset_from_start_x = 0.0f;
		float spacing = -1.0f;
	};

	struct widget_separator { };

	struct widget_spacing { };

	struct widget_dummy
	{
		ImVec2 size;
	};

	struct widget_indent
	{
		float indent_w = 0.0f;
	};

	struct widget_unindent
	{
		float indent_w = 0.0f;
	};

	struct widget_collapsing_header
	{
		ImGuiTreeNodeFlags_ flags;
	};

	

	struct widget_begin_end_window
	{
		bool open = true;
		ImGuiWindowFlags_ flags;
	};

	struct widget_begin_end_child
	{
		ImVec2 size;
		bool border = 1;
		ImGuiWindowFlags_ flags;
	};

	struct widget_begin_end_popup
	{
		std::string name;
		ImGuiWindowFlags_ flags;
	};
	
	struct widget_begin_end_table
	{
		int columns = 1;
		ImGuiTableFlags_ flags;
		ImVec2 outer_size;
		float inner_width = 0;
	};

	struct widget_begin_end_list_box
	{
		ImVec2 size;
		int items_count;
		int items_height;
	};

	struct widget_begin_end_group { };
	
	struct widget_begin_end_combo
	{
		std::string preview_value;
		ImGuiComboFlags_ flags;
	};

	struct widget_begin_end_menu
	{
		bool enabled = true;
	};

	struct widget_push_pop_tree_node
	{
		ImGuiTreeNodeFlags_ flags;
	};

}

#endif
