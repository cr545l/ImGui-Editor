#include "Precompiled.h"
#include "editor/widget.h"

namespace imgui_editor
{
	int32_t to_fixed_type(widget_type type)
	{
		switch (type)
		{		
			// Windows
			case  widget_type::widget_type_begin_end_window 			: return 1001;
			case  widget_type::widget_type_begin_end_child				: return 1002;

			// Parameters stacks (current window)
			case  widget_type::widget_type_push_pop_item_width			: return 2001;
			case  widget_type::widget_type_push_pop_text_wrap_pos		: return 2002;

			// Cursor / Layout
			case  widget_type::widget_type_separator					: return 3001;
			case  widget_type::widget_type_same_line					: return 3002;
			case  widget_type::widget_type_spacing						: return 3003;
			case  widget_type::widget_type_dummy						: return 3004;
			case  widget_type::widget_type_indent						: return 3005;
			case  widget_type::widget_type_unindent						: return 3006;
			case  widget_type::widget_type_begin_end_group				: return 3007;

			// Widgets: Text
			case  widget_type::widget_type_text							: return 4001;
			case  widget_type::widget_type_text_colored					: return 4002;
			case  widget_type::widget_type_label_text					: return 4003;
			case  widget_type::widget_type_bullet_text					: return 4004;

			// Widgets: Main
			case  widget_type::widget_type_button						: return 5001;
			case  widget_type::widget_type_small_button					: return 5002;

			case  widget_type::widget_type_checkbox						: return 5003;
			case  widget_type::widget_type_checkbox_flags				: return 5004;
			case  widget_type::widget_type_radio_button					: return 5005;
			case  widget_type::widget_type_bullet						: return 5006;

			// Widgets: Combo Box
			case  widget_type::widget_type_begin_end_combo				: return 6001;

			// Widgets: Drag Sliders
			case  widget_type::widget_type_drag_float					: return 7001;
			case  widget_type::widget_type_drag_float2					: return 7002;
			case  widget_type::widget_type_drag_float3					: return 7003;
			case  widget_type::widget_type_drag_float4					: return 7004;
			case  widget_type::widget_type_drag_int						: return 7005;
			case  widget_type::widget_type_drag_int2					: return 7006;
			case  widget_type::widget_type_drag_int3					: return 7007;
			case  widget_type::widget_type_drag_int4					: return 7008;

			// Widgets: Regular Sliders
			case  widget_type::widget_type_slider_float					: return 8001;
			case  widget_type::widget_type_slider_float2				: return 8002;
			case  widget_type::widget_type_slider_float3				: return 8003;
			case  widget_type::widget_type_slider_float4				: return 8004;
			case  widget_type::widget_type_slider_angle					: return 8005;
			case  widget_type::widget_type_slider_int					: return 8006;
			case  widget_type::widget_type_slider_int2					: return 8007;
			case  widget_type::widget_type_slider_int3					: return 8008;
			case  widget_type::widget_type_slider_int4					: return 8009;

			// Widgets: Input with Keyboard
			case  widget_type::widget_type_input_text					: return 9001;
			case  widget_type::widget_type_input_text_multiline			: return 9002;
			case  widget_type::widget_type_input_text_with_hint			: return 9003;
			case  widget_type::widget_type_input_float					: return 9008;
			case  widget_type::widget_type_input_float2					: return 9009;
			case  widget_type::widget_type_input_float3					: return 9010;
			case  widget_type::widget_type_input_float4					: return 9011;
			case  widget_type::widget_type_input_int					: return 9004;
			case  widget_type::widget_type_input_int2					: return 9005;
			case  widget_type::widget_type_input_int3					: return 9006;
			case  widget_type::widget_type_input_int4					: return 9007;
			case  widget_type::widget_type_input_double					: return 9012;

			// Widgets: Color Editor/Picker 
			case  widget_type::widget_type_color_edit3					: return 10001;
			case  widget_type::widget_type_color_edit4					: return 10002;
			case  widget_type::widget_type_color_picker3				: return 10003;
			case  widget_type::widget_type_color_picker4				: return 10004;
			case  widget_type::widget_type_color_button					: return 10005;

			// Widgets: Trees
			case  widget_type::widget_type_push_pop_tree_node			: return 11001;
			case  widget_type::widget_type_collapsing_header			: return 11002;

			// Widgets: Selectables
			case  widget_type::widget_type_selectable					: return 12001;

			// Widgets: List Boxes
			case  widget_type::widget_type_begin_end_list_box			: return 13001;

			// Widgets: Menus
			case  widget_type::widget_type_begin_end_menu				: return 14001;

			// Popups; Modals
			case  widget_type::widget_type_begin_end_popup				: return 15001;

			// Tables
			case  widget_type::widget_type_begin_end_table				: return 16001;
			
			case widget_type::widget_type_none:	
		default:
			return 0;
		}
	}
}