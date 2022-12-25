#include "Precompiled.h"
#include "editor/widget.h"

namespace imgui_editor
{
	widget_type to_widget_type(int32_t fixed_type)
	{
		switch (fixed_type)
		{
		default: return widget_type::widget_type_none;

		// Windows
		case 1001: return widget_type::widget_type_begin_end_window			;
		case 1002: return widget_type::widget_type_begin_end_child			;

		// Window manipulation
		case 17001: return widget_type::widget_type_set_next_window_pos			;
		case 17002: return widget_type::widget_type_set_next_window_size		;
		case 17003: return widget_type::widget_type_set_next_window_content_size;
		case 17004: return widget_type::widget_type_set_next_window_collapsed	;
		case 17005: return widget_type::widget_type_set_next_window_focus		;
		case 17006: return widget_type::widget_type_set_next_window_bg_alpha	;

		// Parameters stacks (current window)
		case 2001: return widget_type::widget_type_push_pop_item_width		;
		case 2002: return widget_type::widget_type_push_pop_text_wrap_pos	;

		// Cursor / Layout
		case 3001: return widget_type::widget_type_separator				;
		case 3002: return widget_type::widget_type_same_line				;
		case 3003: return widget_type::widget_type_spacing					;
		case 3004: return widget_type::widget_type_dummy					;
		case 3005: return widget_type::widget_type_indent					;
		case 3006: return widget_type::widget_type_unindent					;
		case 3007: return widget_type::widget_type_begin_end_group			;
		case 3008: return widget_type::widget_type_set_cursor_pos			;

		// Widgets: Text
		case 4001: return widget_type::widget_type_text						;
		case 4002: return widget_type::widget_type_text_colored				;
		case 4003: return widget_type::widget_type_label_text				;
		case 4004: return widget_type::widget_type_bullet_text				;

		// Widgets: Main
		case 5001: return widget_type::widget_type_button					;
		case 5002: return widget_type::widget_type_small_button				;
		case 5003: return widget_type::widget_type_checkbox					;
		case 5004: return widget_type::widget_type_checkbox_flags			;
		case 5005: return widget_type::widget_type_radio_button				;
		case 5006: return widget_type::widget_type_bullet					;
		
		// Widgets: Combo Box
		case 6001: return widget_type::widget_type_begin_end_combo			;

		// Widgets: Drag Sliders
		case 7001: return widget_type::widget_type_drag_float				;
		case 7002: return widget_type::widget_type_drag_float2				;
		case 7003: return widget_type::widget_type_drag_float3				;
		case 7004: return widget_type::widget_type_drag_float4				;
		case 7005: return widget_type::widget_type_drag_int					;
		case 7006: return widget_type::widget_type_drag_int2				;
		case 7007: return widget_type::widget_type_drag_int3				;
		case 7008: return widget_type::widget_type_drag_int4				;

		// Widgets: Regular Sliders
		case 8001: return widget_type::widget_type_slider_float				;
		case 8002: return widget_type::widget_type_slider_float2			;
		case 8003: return widget_type::widget_type_slider_float3			;
		case 8004: return widget_type::widget_type_slider_float4			;
		case 8005: return widget_type::widget_type_slider_angle				;
		case 8006: return widget_type::widget_type_slider_int				;
		case 8007: return widget_type::widget_type_slider_int2				;
		case 8008: return widget_type::widget_type_slider_int3				;
		case 8009: return widget_type::widget_type_slider_int4				;

		// Widgets: Input with Keyboard
		case 9001: return widget_type::widget_type_input_text				;
		case 9002: return widget_type::widget_type_input_text_multiline		;
		case 9003: return widget_type::widget_type_input_text_with_hint		;
		case 9008: return widget_type::widget_type_input_float				;
		case 9009: return widget_type::widget_type_input_float2				;
		case 9010: return widget_type::widget_type_input_float3				;
		case 9011: return widget_type::widget_type_input_float4				;
		case 9004: return widget_type::widget_type_input_int				;
		case 9005: return widget_type::widget_type_input_int2				;
		case 9006: return widget_type::widget_type_input_int3				;
		case 9007: return widget_type::widget_type_input_int4				;
		case 9012: return widget_type::widget_type_input_double				;

		// Widgets: Color Editor/Picker 
		case 10001: return widget_type::widget_type_color_edit3				;
		case 10002: return widget_type::widget_type_color_edit4				;
		case 10003: return widget_type::widget_type_color_picker3			;
		case 10004: return widget_type::widget_type_color_picker4			;
		case 10005: return widget_type::widget_type_color_button			;

		// Widgets: Trees
		case 11001: return widget_type::widget_type_push_pop_tree_node		;
		case 11002: return widget_type::widget_type_collapsing_header		;
		
		// Widgets: Selectables
		case 12001: return widget_type::widget_type_selectable				;

		// Widgets: List Boxes
		case 13001: return widget_type::widget_type_begin_end_list_box		;

		// Widgets: Menus
		case 14002: return widget_type::widget_type_begin_end_menu_bar	;
		case 14001: return widget_type::widget_type_begin_end_menu			;
		case 14003: return widget_type::widget_type_menu_item				;
		
		// Popups, Modals
		case 15001: return widget_type::widget_type_begin_end_popup			;
		
		// Tables
		case 16001: return widget_type::widget_type_begin_end_table			;
		case 16002: return widget_type::widget_type_table_next_row			;
		case 16003: return widget_type::widget_type_table_next_column		;
		case 16004: return widget_type::widget_type_table_set_column_index	;

		// ImGui-Editor
		case 18001: return widget_type::widget_type_caller;
		}
	}
}