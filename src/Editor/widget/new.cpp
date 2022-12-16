#include "Precompiled.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"

namespace imgui_editor
{
	void* new_widget_arg(widget_type type)
	{
		switch (type)
		{
		case widget_type::widget_type_none:						return new widget_none();

		// Windows
		case widget_type::widget_type_begin_end_window:			return new widget_begin_end_window();
		case widget_type::widget_type_begin_end_child:			return new widget_begin_end_child();

		// Window manipulation
		case widget_type::widget_type_set_next_window_pos:			return new widget_set_next_window_pos();
		case widget_type::widget_type_set_next_window_size:			return new widget_set_next_window_size();
		case widget_type::widget_type_set_next_window_content_size: return new widget_set_next_window_content_size();
		case widget_type::widget_type_set_next_window_collapsed:	return new widget_set_next_window_collapsed();
		case widget_type::widget_type_set_next_window_focus:		return new widget_set_next_window_focus();
		case widget_type::widget_type_set_next_window_bg_alpha:		return new widget_set_next_window_bg_alpha();

		// Parameters stacks (current window)
		case widget_type::widget_type_push_pop_item_width:		return new widget_push_pop_item_width();
		case widget_type::widget_type_push_pop_text_wrap_pos:	return new widget_push_pop_text_wrap_pos();

		// Cursor / Layout
		case widget_type::widget_type_separator:				return new widget_separator();
		case widget_type::widget_type_same_line:				return new widget_same_line();
		case widget_type::widget_type_spacing:					return new widget_spacing();
		case widget_type::widget_type_dummy:					return new widget_dummy();
		case widget_type::widget_type_indent:					return new widget_indent();
		case widget_type::widget_type_unindent:					return new widget_unindent();
		case widget_type::widget_type_begin_end_group:			return new widget_begin_end_group();
		case widget_type::widget_type_set_cursor_pos:			return new widget_set_cursor_pos();

		// Widgets: Text
		case widget_type::widget_type_text:						return new widget_text();
		case widget_type::widget_type_text_colored:				return new widget_text_colored();
		case widget_type::widget_type_label_text:				return new widget_label_text();
		case widget_type::widget_type_bullet_text:				return new widget_bullet_text();

		// Widgets: Main
		case widget_type::widget_type_button:					return new widget_button();
		case widget_type::widget_type_checkbox:					return new widget_checkbox();
		case widget_type::widget_type_radio_button:				return new widget_radio_button();
		case widget_type::widget_type_small_button:				return new widget_small_button();
		case widget_type::widget_type_checkbox_flags:			return new widget_checkbox_flags();
		case widget_type::widget_type_bullet:					return new widget_bullet();

		// Widgets: Combo Box
		case widget_type::widget_type_begin_end_combo:			return new widget_begin_end_combo();

		// Widgets: Drag Sliders
		case widget_type::widget_type_drag_float:				return new widget_drag_float();
		case widget_type::widget_type_drag_float2:				return new widget_drag_float2();
		case widget_type::widget_type_drag_float3:				return new widget_drag_float3();
		case widget_type::widget_type_drag_float4:				return new widget_drag_float4();
		case widget_type::widget_type_drag_int:					return new widget_drag_int();
		case widget_type::widget_type_drag_int2:				return new widget_drag_int2();
		case widget_type::widget_type_drag_int3:				return new widget_drag_int3();
		case widget_type::widget_type_drag_int4:				return new widget_drag_int4();

		// Widgets: Regular Sliders
		case widget_type::widget_type_slider_float:				return new widget_slider_float();
		case widget_type::widget_type_slider_float2:			return new widget_slider_float2();
		case widget_type::widget_type_slider_float3:			return new widget_slider_float3();
		case widget_type::widget_type_slider_float4:			return new widget_slider_float4();
		case widget_type::widget_type_slider_angle:				return new widget_slider_angle();
		case widget_type::widget_type_slider_int:				return new widget_slider_int();
		case widget_type::widget_type_slider_int2:				return new widget_slider_int2();
		case widget_type::widget_type_slider_int3:				return new widget_slider_int3();
		case widget_type::widget_type_slider_int4:				return new widget_slider_int4();

		// Widgets: Input with Keyboard
		case widget_type::widget_type_input_text:				return new widget_input_text();
		case widget_type::widget_type_input_text_multiline:		return new widget_input_text_multiline();
		case widget_type::widget_type_input_text_with_hint:		return new widget_input_text_with_hint();
		case widget_type::widget_type_input_float:				return new widget_input_float();
		case widget_type::widget_type_input_float2:				return new widget_input_float2();
		case widget_type::widget_type_input_float3:				return new widget_input_float3();
		case widget_type::widget_type_input_float4:				return new widget_input_float4();
		case widget_type::widget_type_input_int:				return new widget_input_int();
		case widget_type::widget_type_input_int2:				return new widget_input_int2();
		case widget_type::widget_type_input_int3:				return new widget_input_int3();
		case widget_type::widget_type_input_int4:				return new widget_input_int4();
		case widget_type::widget_type_input_double:				return new widget_input_double();

		// Widgets: Color Editor/Picker 
		case widget_type::widget_type_color_edit3:				return new widget_color_edit3();
		case widget_type::widget_type_color_edit4:				return new widget_color_edit4();
		case widget_type::widget_type_color_picker3:			return new widget_color_picker3();
		case widget_type::widget_type_color_picker4:			return new widget_color_picker4();
		case widget_type::widget_type_color_button:				return new widget_color_button();

		// Widgets: Trees
		case widget_type::widget_type_push_pop_tree_node:		return new widget_push_pop_tree_node();
		case widget_type::widget_type_collapsing_header:		return new widget_collapsing_header();

		// Widgets: Selectables
		case widget_type::widget_type_selectable:				return new widget_selectable();

		// Widgets: List Boxes
		case widget_type::widget_type_begin_end_list_box:		return new widget_begin_end_list_box();

		// Widgets: Menus
		case widget_type::widget_type_begin_end_menu_bar:		return new widget_begin_end_menu_bar();
		case widget_type::widget_type_begin_end_menu:			return new widget_begin_end_menu();
		case widget_type::widget_type_menu_item:				return new widget_menu_item();

		// Popups, Modals
		case widget_type::widget_type_begin_end_popup:			return new widget_begin_end_popup();

		// Tables
		case widget_type::widget_type_begin_end_table:			return new widget_begin_end_table();
		case widget_type::widget_type_table_next_row:			return new widget_table_next_row();
		case widget_type::widget_type_table_next_column:		return new widget_table_next_column();
		case widget_type::widget_type_table_set_column_index:	return new widget_table_set_column_index();
		}
		return nullptr;
	}
}