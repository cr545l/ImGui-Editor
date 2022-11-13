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
		ImGuiSelectableFlags flags = 0;
	};

	struct widget_label_text
	{
		std::string text;
	};

	struct widget_input_text
	{
		std::string text;
		ImGuiInputTextFlags flags;
	};

	struct widget_input_text_multiline
	{
		std::string text;
		ImGuiInputTextFlags flags;
	};

	struct widget_input_text_with_hint
	{
		std::string text;
		std::string hint;
		ImGuiInputTextFlags flags;
	};

	struct widget_input_int
	{
		int value;
		int step;
		int step_fast;
		ImGuiInputTextFlags flags;
	};

	struct widget_input_int2
	{
		int value[2];
		ImGuiInputTextFlags flags;
	};

	struct widget_input_int3
	{
		int value[3];
		ImGuiInputTextFlags flags;
	};

	struct widget_input_int4
	{
		int value[4];
		ImGuiInputTextFlags flags;
	};

	struct widget_input_float
	{
		float value;
		float step;
		float step_fast;
		int decimal_precision;
		ImGuiInputTextFlags flags;
	};

	struct widget_slider_float
	{
		float value = 0.0f;
	};

	struct widget_slider_angle
	{
		float value = 0.0f;
	};

	struct widget_slider_int
	{
		int value = 0;
	};

	struct widget_drag_int
	{
		int value = 0;
	};

	struct widget_drag_float
	{
		float value = 0.0f;
	};

	struct widget_begin_end_combo
	{
		std::string preview_value;
	};
}

#endif