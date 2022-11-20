#ifndef __WIDGET_DATA_
#define __WIDGET_DATA_

namespace imgui_editor
{
	
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

	struct widget_text_colored
	{
		ImColor color;
	};

	struct widget_text_selectable
	{
		std::string text;
		bool selected = false;
		ImGuiSelectableFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_label_text
	{
		std::string text;
	};

	struct widget_input_text
	{
		std::string text;
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_text_multiline
	{
		std::string text;
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_text_with_hint
	{
		std::string text;
		std::string hint;
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_int
	{
		int value;
		int step;
		int step_fast;
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_int2
	{
		int value[2];
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_int3
	{
		int value[3];
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_int4
	{
		int value[4];
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_float
	{
		float value;
		float step;
		float step_fast;
		std::string format;
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	};

	struct widget_input_double
	{
		double value;
	};

	struct widget_input_float3
	{
		float value[3];
	};

	struct widget_drag_int
	{
		int value = 0;
	};

	struct widget_drag_float
	{
		float value = 0.0f;
	};

	struct widget_slider_int
	{
		int value = 0;
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_int2
	{
		int value[2] = {0,};
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_int3
	{
		int value[3] = {0,};
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_int4
	{
		int value[4] = {0,};
		int min = 0;
		int max = 0;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_float
	{
		float value = 0.0f;
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_float2
	{
		float value[2] = {0.0f,};
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_float3
	{
		float value[3] = {0.0f,};
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_float4
	{
		float value[4] = {0.0f,};
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_slider_angle
	{
		float value = 0.0f;
		float min = 0.0f;
		float max = 0.0f;
		std::string format;
		ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	};

	struct widget_color_edit3
	{
		float value[3] = {0.0f,};
		ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
	};

	struct widget_color_edit4
	{
		float value[4] = {0.0f,};
		ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
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
		float unindent_w = 0.0f;
	};

	struct widget_collapsing_header
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	};

	struct widget_begin_end_window
	{
		bool open = true;
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	};

	struct widget_begin_end_child
	{
		ImVec2 size;
		bool border = 1;
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	};
	
	// widget_type_begin_end_table
	struct widget_begin_end_table
	{
		std::string name;
		int columns = 1;
		ImGuiTableFlags flags =	ImGuiTableFlags_None;
		ImVec2 outer_size;
		float inner_width = 0;
	};

	struct widget_begin_end_list_box
	{
		ImVec2 size;
		int items_count;
		int items_height;
	};

	struct widget_begin_end_combo
	{
		std::string preview_value;
		ImGuiComboFlags flags =	ImGuiComboFlags_None;
	};
}

#endif
