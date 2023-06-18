#include "Precompiled.h"
#include "editor/widget.h"
#include "editor/widget/args_data.h"

namespace imgui_editor
{
	void delete_widget_args(const widget_type type, void* target)
	{
		// LOG("DeleArg %s %x", get_widget_name(type), target);
		switch (type)
		{
		default:
		case widget_type::widget_type_none: return;

		// Windows
		case widget_type::widget_type_begin_end_window: delete static_cast<widget_begin_end_window*>(target); return;
		case widget_type::widget_type_begin_end_child: delete static_cast<widget_begin_end_child*>(target); return;

		// Window manipulation
		case widget_type::widget_type_set_next_window_pos: delete static_cast<widget_set_next_window_pos*>(target); return;
		case widget_type::widget_type_set_next_window_size: delete static_cast<widget_set_next_window_size*>(target); return;
		case widget_type::widget_type_set_next_window_content_size: delete static_cast<widget_set_next_window_content_size*>(target); return;
		case widget_type::widget_type_set_next_window_collapsed: delete static_cast<widget_set_next_window_collapsed*>(target); return;
		case widget_type::widget_type_set_next_window_focus: delete static_cast<widget_set_next_window_focus*>(target); return;
		case widget_type::widget_type_set_next_window_bg_alpha: delete static_cast<widget_set_next_window_bg_alpha*>(target); return;

		// Parameters stacks (current window)
		case widget_type::widget_type_push_pop_item_width: delete static_cast<widget_push_pop_item_width*>(target); return;
		case widget_type::widget_type_push_pop_text_wrap_pos: delete static_cast<widget_push_pop_text_wrap_pos*>(target); return;

		// Cursor / Layout
		case widget_type::widget_type_separator: delete static_cast<widget_separator*>(target); return;
		case widget_type::widget_type_same_line: delete static_cast<widget_same_line*>(target); return;
		case widget_type::widget_type_spacing: delete static_cast<widget_spacing*>(target); return;
		case widget_type::widget_type_dummy: delete static_cast<widget_dummy*>(target); return;
		case widget_type::widget_type_indent: delete static_cast<widget_indent*>(target); return;
		case widget_type::widget_type_unindent: delete static_cast<widget_unindent*>(target); return;
		case widget_type::widget_type_begin_end_group: delete static_cast<widget_begin_end_group*>(target); return;
		case widget_type::widget_type_set_cursor_pos: delete static_cast<widget_set_cursor_pos*>(target); return;

		// Widgets: Text
		case widget_type::widget_type_text: delete static_cast<widget_text*>(target); return;
		case widget_type::widget_type_text_colored: delete static_cast<widget_text_colored*>(target); return;
		case widget_type::widget_type_label_text: delete static_cast<widget_label_text*>(target); return;
		case widget_type::widget_type_bullet_text: delete static_cast<widget_bullet_text*>(target); return;

		// Widgets: Main
		case widget_type::widget_type_button: delete static_cast<widget_button*>(target); return;
		case widget_type::widget_type_small_button: delete static_cast<widget_small_button*>(target); return;
		case widget_type::widget_type_checkbox: delete static_cast<widget_checkbox*>(target); return;
		case widget_type::widget_type_checkbox_flags: delete static_cast<widget_checkbox_flags*>(target); return;
		case widget_type::widget_type_radio_button: delete static_cast<widget_radio_button*>(target); return;
		case widget_type::widget_type_bullet: delete static_cast<widget_bullet*>(target); return;

		// Widgets: Combo Box
		case widget_type::widget_type_begin_end_combo: delete static_cast<widget_begin_end_combo*>(target); return;

		// Widgets: Drag Sliders
		case widget_type::widget_type_drag_float: delete static_cast<widget_drag_float*>(target); return;
		case widget_type::widget_type_drag_float2: delete static_cast<widget_drag_float2*>(target); return;
		case widget_type::widget_type_drag_float3: delete static_cast<widget_drag_float3*>(target); return;
		case widget_type::widget_type_drag_float4: delete static_cast<widget_drag_float4*>(target); return;
		case widget_type::widget_type_drag_int: delete static_cast<widget_drag_int*>(target); return;
		case widget_type::widget_type_drag_int2: delete static_cast<widget_drag_int2*>(target); return;
		case widget_type::widget_type_drag_int3: delete static_cast<widget_drag_int3*>(target); return;
		case widget_type::widget_type_drag_int4: delete static_cast<widget_drag_int4*>(target); return;

		// Widgets: Regular Sliders
		case widget_type::widget_type_slider_float: delete static_cast<widget_slider_float*>(target); return;
		case widget_type::widget_type_slider_float2: delete static_cast<widget_slider_float2*>(target); return;
		case widget_type::widget_type_slider_float3: delete static_cast<widget_slider_float3*>(target); return;
		case widget_type::widget_type_slider_float4: delete static_cast<widget_slider_float4*>(target); return;
		case widget_type::widget_type_slider_angle: delete static_cast<widget_slider_angle*>(target); return;
		case widget_type::widget_type_slider_int: delete static_cast<widget_slider_int*>(target); return;
		case widget_type::widget_type_slider_int2: delete static_cast<widget_slider_int2*>(target); return;
		case widget_type::widget_type_slider_int3: delete static_cast<widget_slider_int3*>(target); return;
		case widget_type::widget_type_slider_int4: delete static_cast<widget_slider_int4*>(target); return;

		// Widgets: Input with Keyboard
		case widget_type::widget_type_input_text: delete static_cast<widget_input_text*>(target); return;
		case widget_type::widget_type_input_text_multiline: delete static_cast<widget_input_text_multiline*>(target); return;
		case widget_type::widget_type_input_text_with_hint: delete static_cast<widget_input_text_with_hint*>(target); return;
		case widget_type::widget_type_input_float: delete static_cast<widget_input_float*>(target); return;
		case widget_type::widget_type_input_float2: delete static_cast<widget_input_float2*>(target); return;
		case widget_type::widget_type_input_float3: delete static_cast<widget_input_float3*>(target); return;
		case widget_type::widget_type_input_float4: delete static_cast<widget_input_float4*>(target); return;
		case widget_type::widget_type_input_int: delete static_cast<widget_input_int*>(target); return;
		case widget_type::widget_type_input_int2: delete static_cast<widget_input_int2*>(target); return;
		case widget_type::widget_type_input_int3: delete static_cast<widget_input_int3*>(target); return;
		case widget_type::widget_type_input_int4: delete static_cast<widget_input_int4*>(target); return;
		case widget_type::widget_type_input_double: delete static_cast<widget_input_double*>(target); return;

		// Widgets: Color Editor/Picker 
		case widget_type::widget_type_color_edit3: delete static_cast<widget_color_edit3*>(target); return;
		case widget_type::widget_type_color_edit4: delete static_cast<widget_color_edit4*>(target); return;
		case widget_type::widget_type_color_picker3: delete static_cast<widget_color_picker3*>(target); return;
		case widget_type::widget_type_color_picker4: delete static_cast<widget_color_picker4*>(target); return;
		case widget_type::widget_type_color_button: delete static_cast<widget_color_button*>(target); return;

		// Widgets: Trees
		case widget_type::widget_type_push_pop_tree_node: delete static_cast<widget_push_pop_tree_node*>(target); return;
		case widget_type::widget_type_collapsing_header: delete static_cast<widget_collapsing_header*>(target); return;

		// Widgets: Selectables
		case widget_type::widget_type_selectable: delete static_cast<widget_selectable*>(target); return;

		// Widgets: List Boxes
		case widget_type::widget_type_begin_end_list_box: delete static_cast<widget_begin_end_list_box*>(target); return;

		// Widgets: Menus
		case widget_type::widget_type_begin_end_menu_bar: delete static_cast<widget_begin_end_menu_bar*>(target); return;
		case widget_type::widget_type_begin_end_menu: delete static_cast<widget_begin_end_menu*>(target); return;
		case widget_type::widget_type_menu_item: delete static_cast<widget_menu_item*>(target); return;

		// Popups, Modals
		case widget_type::widget_type_begin_end_popup: delete static_cast<widget_begin_end_popup*>(target); return;

		// Tables
		case widget_type::widget_type_begin_end_table: delete static_cast<widget_begin_end_table*>(target); return;
		case widget_type::widget_type_table_next_row: delete static_cast<widget_table_next_row*>(target); return;
		case widget_type::widget_type_table_next_column: delete static_cast<widget_table_next_column*>(target); return;
		case widget_type::widget_type_table_set_column_index: delete static_cast<widget_table_set_column_index*>(target); return;

		// ImGui-Editor
		case widget_type::widget_type_caller: delete static_cast<widget_caller*>(target); return;
		}
	}
}