#include "Precompiled.h"

#include "editor/extension.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"

#define _default_parse(type, format, ...)                        \
type* wd = (type*)data;                                         \
if (in)                                                         \
{                                                               \
    sscanf2(format, inout.c_str(), wd);                         \
}                                                               \
else                                                            \
{                                                               \
    version = "0";                                              \
    inout = safe_string_format(format, ##__VA_ARGS__);          \
}                                                               \
return

namespace imgui_editor
{
    void parse_args_data(const widget_type type, void* data, std::string& inout, std::string& version, const bool in)
    {        
        switch (type)
        {
        case widget_type::widget_type_none: return;

#pragma region // Windows
        case widget_type::widget_type_begin_end_window:
        {
            _default_parse(widget_begin_end_window, "%d,%d", wd->open,  wd->flags);
        }
        case widget_type::widget_type_begin_end_child:
        {
            _default_parse(widget_begin_end_child, "%f,%f,%d,%d", wd->size.x, wd->size.y, wd->border, wd->flags);
        }
#pragma endregion // Windows

#pragma region // Parameters stacks (current window)
        case widget_type::widget_type_push_pop_item_width:
        {
            _default_parse(widget_push_pop_item_width, "%f", wd->item_width);
        }
        case widget_type::widget_type_push_pop_text_wrap_pos:
        {
            _default_parse(widget_push_pop_text_wrap_pos, "%f", wd->item_width);
        }
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
        case widget_type::widget_type_separator: return;
        case widget_type::widget_type_same_line:
        {
            _default_parse(widget_same_line, "%f,%f", wd->offset_from_start_x, wd->spacing);
        }
        case widget_type::widget_type_spacing: return;
        case widget_type::widget_type_dummy: 
        {
            _default_parse(widget_dummy, "%f,%f", wd->size.x, wd->size.y);
        }
        case widget_type::widget_type_indent: 
        {
            _default_parse(widget_indent, "%f", wd->indent_w);
        }
        case widget_type::widget_type_unindent: 
        {
            _default_parse(widget_unindent,"%f", wd->indent_w);
        }
        case widget_type::widget_type_begin_end_group: return;
        case widget_type::widget_type_set_cursor_pos:
        {
            _default_parse(widget_set_cursor_pos, "%f,%f", wd->local_pos.x, wd->local_pos.y);
        }
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
        case widget_type::widget_type_text: return;
        case widget_type::widget_type_text_colored:
        {
            _default_parse(widget_text_colored, "%f,%f,%f,%f,", wd->color.Value.x, wd->color.Value.y, wd->color.Value.z, wd->color.Value.w);
        }
        case widget_type::widget_type_label_text:
        {
            _default_parse(widget_label_text, "%s,", to_safe_string(wd->text).c_str());
        }
        case widget_type::widget_type_bullet_text: return;
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
        case widget_type::widget_type_button: 
        {
            _default_parse(widget_button, "%f,%f,", wd->size.x, wd->size.y);
        }
        case widget_type::widget_type_small_button: return;
        case widget_type::widget_type_checkbox:
        {    
            _default_parse(widget_checkbox, "%d,", wd->check);
        }
        case widget_type::widget_type_checkbox_flags:
        {
            _default_parse(widget_checkbox_flags, "%d,%d,", wd->flags, wd->flags_value);
        }
        case widget_type::widget_type_radio_button:
        {
            _default_parse(widget_radio_button, "%d,", wd->active);
        }
        case widget_type::widget_type_bullet: return;
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
        case widget_type::widget_type_begin_end_combo:
        {
            _default_parse(widget_begin_end_combo, "%s,%d", to_safe_string(wd->preview_value).c_str(), wd->flags);
        }
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
        case widget_type::widget_type_drag_float:
        {
            _default_parse(widget_drag_float, "%f,%f,%f,%f,%s,%d", 
                wd->value, 
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float2:
        {
            _default_parse(widget_drag_float2, "%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float3:
        {
            _default_parse(widget_drag_float3, "%f,%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2],
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float4:
        {
            _default_parse(widget_drag_float4, "%f,%f,%f,%f,%f,%f,%f,%s,%d",
                wd->value[0], wd->value[1], wd->value[2], wd->value[3],
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int:
        {
            _default_parse(widget_drag_int, "%d,%f,%d,%d,%s,%d", 
                wd->value, 
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int2:
        {
            _default_parse(widget_drag_int2, "%d,%d,%f,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int3:
        {
            _default_parse(widget_drag_int3, "%d,%d,%d,%f,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], 
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int4:
        {
            _default_parse(widget_drag_int4, "%d,%d,%d,%d,%f,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], 
                wd->speed, wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
        case widget_type::widget_type_slider_float:
        {
            _default_parse(widget_slider_float, "%f,%f,%f,%s,%d", 
                wd->value, 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float2:
        {
            _default_parse(widget_slider_float2, "%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float3:
        {
            _default_parse(widget_slider_float3, "%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float4:
        {
            _default_parse(widget_slider_float4, "%f,%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_angle:
        {
            _default_parse(widget_slider_angle, "%f,%f,%f,%s,%d", 
                wd->value, 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int:
        {
            _default_parse(widget_slider_int, "%d,%d,%d,%s,%d", 
                wd->value, 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int2:
        {
            _default_parse(widget_slider_int2, "%d,%d,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int3:
        {
            _default_parse(widget_slider_int3, "%d,%d,%d,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int4:
        {
            _default_parse(widget_slider_int4, "%d,%d,%d,%d,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], 
                wd->min, wd->max, to_safe_string(wd->format).c_str(), wd->flags);
        }
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
        case widget_type::widget_type_input_text:
        {
            _default_parse(widget_input_text, "%s,%d,",
                to_safe_string(wd->text).c_str(), wd->flags);
        }
        case widget_type::widget_type_input_text_multiline:
        {
            _default_parse(widget_input_text_multiline, "%s,%f,%f,%d,", 
                to_safe_string(wd->text).c_str(), wd->size.x, wd->size.y, wd->flags);
        }
        case widget_type::widget_type_input_text_with_hint:
        {
            _default_parse(widget_input_text_with_hint, "%s,%s,%d,", 
                to_safe_string(wd->text).c_str(), to_safe_string(wd->hint).c_str(), wd->flags);
        }
        case widget_type::widget_type_input_float:
        {
            _default_parse(widget_input_float, "%f,%f,%f,%d",
                wd->value, wd->step, wd->step_fast, wd->flags);
        }
        case widget_type::widget_type_input_float2:
        {
            _default_parse(widget_input_float2, "%f,%f,%d", 
                wd->value[0], wd->value[1], wd->flags);
        }
        case widget_type::widget_type_input_float3:
        {
            _default_parse(widget_input_float3, "%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_input_float4:
        {
            _default_parse(widget_input_float4, "%f,%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_input_int:
        {
            _default_parse(widget_input_int, "%d,%d,%d,%d", 
                wd->value, wd->step, wd->step_fast, wd->flags);
        }
        case widget_type::widget_type_input_int2:
        {
            _default_parse(widget_input_int2, "%d,%d,%d",
                wd->value[0], wd->value[1], wd->flags);
        }
        case widget_type::widget_type_input_int3:
        {
            _default_parse(widget_input_int3, "%d,%d,%d,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_input_int4:
        {
            _default_parse(widget_input_int4, "%d,%d,%d,%d,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_input_double:
        {
            _default_parse(widget_input_double, "%f,%f,%f,%d", 
                wd->value, wd->step, wd->step_fast, wd->flags);
        }
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
        case widget_type::widget_type_color_edit3:
        {
            _default_parse(widget_color_edit3, "%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_color_edit4:
        {
            _default_parse(widget_color_edit4, "%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_color_picker3:
        {
            _default_parse(widget_color_picker3, "%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_color_picker4:
        {
            _default_parse(widget_color_picker4, "%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_color_button:
        {
            _default_parse(widget_color_button, "%f,%f,%f,%f,%d,%f,%f", wd->col.x, wd->col.y, wd->col.z, wd->col.w, wd->flags, wd->size.x, wd->size.y);
        }
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
        case widget_type::widget_type_push_pop_tree_node:
        {
            _default_parse(widget_push_pop_tree_node, "%d", wd->flags);
        }
        case widget_type::widget_type_collapsing_header:
        {
            _default_parse(widget_collapsing_header, "%d",wd->flags);
        }        
#pragma endregion // Widgets: Trees

#pragma region // Widgets: Selectables
        case widget_type::widget_type_selectable:
        {
            _default_parse(widget_selectable, "%d,%d,%f,%f,", wd->selected, wd->flags, wd->size.x, wd->size.y);
        }
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
        case widget_type::widget_type_begin_end_list_box:
        {
            _default_parse(widget_begin_end_list_box, "%d,%d,%f,%f,", wd->items_count, wd->items_height, wd->size.x, wd->size.y);
        }
#pragma endregion // Widgets: List Boxes
		
#pragma region // Widgets: Menus2
        case widget_type::widget_type_begin_end_menu_bar: return;
        case widget_type::widget_type_begin_end_menu:
        {
            _default_parse(widget_begin_end_menu, "%d", wd->enabled);
        }
        case widget_type::widget_type_menu_item:
        {
            _default_parse(widget_menu_item, "%s,%d,%d",
                to_safe_string(wd->shortcut).c_str(),
                wd->selected, 
                wd->enabled);
        }
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
        case widget_type::widget_type_begin_end_popup:
        {
            _default_parse(widget_begin_end_popup, "%f", wd->flags);
        }
#pragma endregion // Popups, Modals
		
#pragma region // Tables
        case widget_type::widget_type_begin_end_table:
        {
            _default_parse(widget_begin_end_table, "%d,%d,%f,%f,%f",
                wd->columns,wd->flags,wd->outer_size.x,wd->outer_size.y,wd->inner_width);
        }
        case widget_type::widget_type_table_next_row:
        {
            _default_parse(widget_table_next_row, "%d,%f", wd->flags, wd->min_row_height);
        }
        case widget_type::widget_type_table_next_column: return;
        case widget_type::widget_type_table_set_column_index:
        {
            _default_parse(widget_table_set_column_index, "%d", wd->column_n);
        }
#pragma endregion // Tables

        default:
            debug_break();
            return;
        }
    }

    #undef _default_parse
}