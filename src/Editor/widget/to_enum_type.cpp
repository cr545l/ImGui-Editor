#include "Precompiled.h"
#include "editor/widget.h"

namespace imgui_editor
{
	widget_type to_widget_type(int32_t fixed_type)
	{
		switch (fixed_type)
		{
		case 1001: return widget_type::widget_type_begin_end_window			;
		case 1002: return widget_type::widget_type_begin_end_child			;

		case 2001: return widget_type::widget_type_push_pop_item_width		;
		case 2002: return widget_type::widget_type_push_pop_text_wrap_pos	;

		case 3001: return widget_type::widget_type_separator				;
		case 3002: return widget_type::widget_type_same_line				;
		case 3003: return widget_type::widget_type_spacing					;
		case 3004: return widget_type::widget_type_dummy					;
		case 3005: return widget_type::widget_type_indent					;
		case 3006: return widget_type::widget_type_unindent					;
		case 3007: return widget_type::widget_type_begin_end_group			;

		case 4001: return widget_type::widget_type_text						;
		case 4002: return widget_type::widget_type_text_colored				;
		case 4003: return widget_type::widget_type_label_text				;
		case 4004: return widget_type::widget_type_bullet_text				;

		case 5001: return widget_type::widget_type_button					;
		case 5002: return widget_type::widget_type_small_button				;
		case 5003: return widget_type::widget_type_checkbox					;
		case 5004: return widget_type::widget_type_checkbox_flags			;
		case 5005: return widget_type::widget_type_radio_button				;
		case 5006: return widget_type::widget_type_bullet					;
		
		case 6001: return widget_type::widget_type_begin_end_combo			;

		case 7001: return widget_type::widget_type_drag_float				;
		case 7002: return widget_type::widget_type_drag_float2				;
		case 7003: return widget_type::widget_type_drag_float3				;
		case 7004: return widget_type::widget_type_drag_float4				;
		case 7005: return widget_type::widget_type_drag_int					;
		case 7006: return widget_type::widget_type_drag_int2				;
		case 7007: return widget_type::widget_type_drag_int3				;
		case 7008: return widget_type::widget_type_drag_int4				;

		case 8001: return widget_type::widget_type_slider_float				;
		case 8002: return widget_type::widget_type_slider_float2			;
		case 8003: return widget_type::widget_type_slider_float3			;
		case 8004: return widget_type::widget_type_slider_float4			;
		case 8005: return widget_type::widget_type_slider_angle				;
		case 8006: return widget_type::widget_type_slider_int				;
		case 8007: return widget_type::widget_type_slider_int2				;
		case 8008: return widget_type::widget_type_slider_int3				;
		case 8009: return widget_type::widget_type_slider_int4				;

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

		case 10001: return widget_type::widget_type_color_edit3				;
		case 10002: return widget_type::widget_type_color_edit4				;
		case 10003: return widget_type::widget_type_color_picker3			;
		case 10004: return widget_type::widget_type_color_picker4			;
		case 10005: return widget_type::widget_type_color_button			;

		case 11001: return widget_type::widget_type_push_pop_tree_node		;
		case 11002: return widget_type::widget_type_collapsing_header		;

		case 12001: return widget_type::widget_type_selectable				;

		case 13001: return widget_type::widget_type_begin_end_list_box		;
		case 14001: return widget_type::widget_type_begin_end_menu			;
		case 15001: return widget_type::widget_type_begin_end_popup			;
		case 16001: return widget_type::widget_type_begin_end_table			;
		}
	}
}