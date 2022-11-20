#ifndef __WIDGET_TYPE_H__
#define __WIDGET_TYPE_H__

namespace imgui_editor
{
	enum class widget_type : uint8_t
	{
		widget_type_none,

		widget_type_button,
		widget_type_small_button,
		widget_type_checkbox,
		widget_type_checkbox_flags,
		widget_type_radio_button,

		widget_type_text,
		widget_type_text_colored,
		widget_type_bullet_text,
		widget_type_bullet,

		widget_type_selectable,

		widget_type_label_text,
		widget_type_input_text,
		widget_type_input_text_multiline,
		widget_type_input_text_with_hint,
		widget_type_input_int,
		widget_type_input_int2,
		widget_type_input_int3,
		widget_type_input_int4,
		widget_type_input_float,
		widget_type_input_float2,
		widget_type_input_float3,
		widget_type_input_float4,
		widget_type_input_double,

		widget_type_drag_int,
		widget_type_drag_float,

		widget_type_slider_int,
		widget_type_slider_int2,
		widget_type_slider_int3,
		widget_type_slider_int4,
		widget_type_slider_float,
		widget_type_slider_float2,
		widget_type_slider_float3,
		widget_type_slider_float4,
		widget_type_slider_angle,

		widget_type_color_edit3,
		widget_type_color_edit4,
		widget_type_color_picker3,
		widget_type_color_picker4,
		widget_type_color_button,

		widget_type_list_box,

		widget_type_collapsing_header,
		
		widget_type_separator,
		widget_type_same_line,
		widget_type_spacing,
		widget_type_dummy,
		widget_type_indent,
		widget_type_unindent,

		widget_type_begin_end_window,
		widget_type_begin_end_child,
		widget_type_begin_end_popup,
		widget_type_begin_end_list_box,
		widget_type_begin_end_table,
		widget_type_begin_end_group,
		widget_type_begin_end_combo,
		widget_type_begin_end_menu,

		widget_type_push_pop_tree_node,

	};
}

#endif
