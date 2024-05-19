#ifndef __ENUM_TYPE_H__
#define __ENUM_TYPE_H__

BEGIN_NS_IMGUI_EDITOR

// 주석으로 삽입하면 enum에 주석이 달리므로 region으로 묶어서 표시
enum class widget_type : uint32_t
{
    widget_type_none = 0,

#pragma region // Windows
    widget_type_begin_end_window,
    widget_type_begin_end_child,
#pragma endregion // Windows

#pragma region // Window manipulation
    widget_type_set_next_window_pos,
    widget_type_set_next_window_size,
    widget_type_set_next_window_content_size,
    widget_type_set_next_window_collapsed,
    widget_type_set_next_window_focus,
    widget_type_set_next_window_bg_alpha,
#pragma endregion // Window manipulation

#pragma region // Parameters stacks (current window)
    widget_type_push_pop_item_width,
    widget_type_push_pop_text_wrap_pos,
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
    widget_type_separator,
    widget_type_same_line,
    widget_type_spacing,
    widget_type_dummy,
    widget_type_indent,
    widget_type_unindent,
    widget_type_begin_end_group,
    widget_type_set_cursor_pos,
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
    widget_type_text,
    widget_type_text_colored,
    widget_type_label_text,
    widget_type_bullet_text,
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
    widget_type_button,
    widget_type_small_button,
    widget_type_checkbox,
    widget_type_checkbox_flags,
    widget_type_radio_button,
    widget_type_bullet,
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
    widget_type_begin_end_combo,
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
    widget_type_drag_float,
    widget_type_drag_float2,
    widget_type_drag_float3,
    widget_type_drag_float4,
    widget_type_drag_int,
    widget_type_drag_int2,
    widget_type_drag_int3,
    widget_type_drag_int4,
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
    widget_type_slider_float,
    widget_type_slider_float2,
    widget_type_slider_float3,
    widget_type_slider_float4,
    widget_type_slider_angle,
    widget_type_slider_int,
    widget_type_slider_int2,
    widget_type_slider_int3,
    widget_type_slider_int4,
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
    widget_type_input_text,
    widget_type_input_text_multiline,
    widget_type_input_text_with_hint,
    widget_type_input_float,
    widget_type_input_float2,
    widget_type_input_float3,
    widget_type_input_float4,
    widget_type_input_int,
    widget_type_input_int2,
    widget_type_input_int3,
    widget_type_input_int4,
    widget_type_input_double,
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
    widget_type_color_edit3,
    widget_type_color_edit4,
    widget_type_color_picker3,
    widget_type_color_picker4,
    widget_type_color_button,
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
    widget_type_push_pop_tree_node,
    widget_type_collapsing_header,
#pragma endregion // Widgets: Trees

#pragma region // Widgets: Selectables
    widget_type_selectable,
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
    widget_type_begin_end_list_box,
#pragma endregion // Widgets: List Boxes

#pragma region // Widgets: Menus
    widget_type_begin_end_menu_bar,
    widget_type_begin_end_menu,
    widget_type_menu_item,
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
    widget_type_begin_end_popup,
#pragma endregion // Popups, Modals

#pragma region // Tables
    widget_type_begin_end_table,
    widget_type_table_next_row,
    widget_type_table_next_column,
    widget_type_table_set_column_index,
#pragma endregion // Tables

#pragma region // ImGui-Editor
    widget_type_caller,
#pragma endregion // ImGui-Editor
};
#endif

END_NS_IMGUI_EDITOR