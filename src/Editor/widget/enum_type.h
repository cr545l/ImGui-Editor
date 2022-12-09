#ifndef __ENUM_TYPE_H__
#define __ENUM_TYPE_H__

namespace imgui_editor
{
	enum class widget_type : uint32_t
	{
		widget_type_none 						= 0,

#pragma region // Windows
		widget_type_begin_end_window 			,
		widget_type_begin_end_child				,
#pragma endregion // Windows

#pragma region // Parameters stacks (current window)
		widget_type_push_pop_item_width			,
		widget_type_push_pop_text_wrap_pos		,
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
		widget_type_separator					,
		widget_type_same_line					,
		widget_type_spacing						,
		widget_type_dummy						,
		widget_type_indent						,
		widget_type_unindent					,
		widget_type_begin_end_group				,
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
		widget_type_text						,
		widget_type_text_colored				,
		widget_type_label_text					,
		widget_type_bullet_text					,
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
		widget_type_button						,
		widget_type_small_button				,
		widget_type_checkbox					,
		widget_type_checkbox_flags				,
		widget_type_radio_button				,
		widget_type_bullet						,
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
		widget_type_begin_end_combo				,
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
		widget_type_drag_float					,
		widget_type_drag_float2					,
		widget_type_drag_float3					,
		widget_type_drag_float4					,
		widget_type_drag_int					,
		widget_type_drag_int2					,
		widget_type_drag_int3					,
		widget_type_drag_int4					,
#pragma endregion // Widgets: Drag Sliders
		
#pragma region // Widgets: Regular Sliders
		widget_type_slider_float				,
		widget_type_slider_float2				,
		widget_type_slider_float3				,
		widget_type_slider_float4				,
		widget_type_slider_angle				,
		widget_type_slider_int					,
		widget_type_slider_int2					,
		widget_type_slider_int3					,
		widget_type_slider_int4					,
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
		widget_type_input_text					,
		widget_type_input_text_multiline		,
		widget_type_input_text_with_hint		,
		widget_type_input_float					,
		widget_type_input_float2				,
		widget_type_input_float3				,
		widget_type_input_float4				,
		widget_type_input_int					,
		widget_type_input_int2					,
		widget_type_input_int3					,
		widget_type_input_int4					,
		widget_type_input_double				,
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
		widget_type_color_edit3					,
		widget_type_color_edit4					,
		widget_type_color_picker3				,
		widget_type_color_picker4				,
		widget_type_color_button				,
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
		widget_type_push_pop_tree_node			,
		widget_type_collapsing_header			,
#pragma endregion // Widgets: Trees

#pragma region // Widgets: Selectables
		widget_type_selectable					,
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
		widget_type_begin_end_list_box			,
#pragma endregion // Widgets: List Boxes
		
#pragma region // Widgets: Menus
		widget_type_begin_end_menu				,
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
		widget_type_begin_end_popup				,
#pragma endregion // Popups, Modals
		
#pragma region // Tables
		widget_type_begin_end_table				,
#pragma endregion // Tables
	};
}

#endif
