#ifndef __WIDGET_TYPE_H__
#define __WIDGET_TYPE_H__

namespace imgui_editor
{
	// 추후 추가될 위젯들을 위해 공백으로 확보
	enum class widget_type : uint32_t
	{
		widget_type_none 						= 0,

		// Windows
		widget_type_begin_end_window 			,
		widget_type_begin_end_child				,

		// Parameters stacks (current window)
		widget_type_push_pop_item_width			,
		widget_type_push_pop_text_wrap_pos		,

		// Cursor / Layout
		widget_type_separator					,
		widget_type_same_line					,
		widget_type_spacing						,
		widget_type_dummy						,
		widget_type_indent						,
		widget_type_unindent					,
		widget_type_begin_end_group				,

		// Widgets: Text
		widget_type_text						,
		widget_type_text_colored				,
		widget_type_label_text					,
		widget_type_bullet_text					,

		// Widgets: Main
		widget_type_button						,
		widget_type_small_button				,
		widget_type_checkbox					,
		widget_type_checkbox_flags				,
		widget_type_radio_button				,
		widget_type_bullet						,

		 // Widgets: Combo Box
		widget_type_begin_end_combo				,

		// Widgets: Drag Sliders
		widget_type_drag_float					,
		widget_type_drag_float2					,
		widget_type_drag_float3					,
		widget_type_drag_float4					,
		widget_type_drag_int					,
		widget_type_drag_int2					,
		widget_type_drag_int3					,
		widget_type_drag_int4					,
		
		// Widgets: Regular Sliders
		widget_type_slider_float				,
		widget_type_slider_float2				,
		widget_type_slider_float3				,
		widget_type_slider_float4				,
		widget_type_slider_angle				,
		widget_type_slider_int					,
		widget_type_slider_int2					,
		widget_type_slider_int3					,
		widget_type_slider_int4					,

   		// Widgets: Input with Keyboard
		widget_type_input_text					,
		widget_type_input_text_multiline		,
		widget_type_input_text_with_hint		,
		widget_type_input_int					,
		widget_type_input_int2					,
		widget_type_input_int3					,
		widget_type_input_int4					,
		widget_type_input_float					,
		widget_type_input_float2				,
		widget_type_input_float3				,
		widget_type_input_float4				,
		widget_type_input_double				,

		// Widgets: Color Editor/Picker 
		widget_type_color_edit3					,
		widget_type_color_edit4					,
		widget_type_color_picker3				,
		widget_type_color_picker4				,
		widget_type_color_button				,

    	// Widgets: Trees
		widget_type_push_pop_tree_node			,
		widget_type_collapsing_header			,

		// Widgets: Selectables
		widget_type_selectable					,

		// Widgets: List Boxes
		widget_type_begin_end_list_box			,
		
		// Widgets: Menus
		widget_type_begin_end_menu				,

    	// Popups, Modals
		widget_type_begin_end_popup				,
		
		// Tables
		widget_type_begin_end_table				,
	};
}

#endif
