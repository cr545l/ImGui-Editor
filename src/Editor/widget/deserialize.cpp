#include "Precompiled.h"

#include "editor/extension.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"

namespace imgui_editor
{
    template<typename T, typename ... Args>
    void default_parse(std::string& inout, std::string& version, const bool in, T* data, const char* format, Args ... args)
    {                        
        if (in)                                               
        {                                          
                       
            sscanf2(format, inout.c_str(), data);               
        }                                                     
        else                                                  
        {                                                     
            version = "0";                                    
            inout = safe_string_format(format, args ...);
        }                                                     
    }
 
    static std::string to_safe_string2(const bool in, const std::string& value)
    {
        // value는 widget의 어떤 필드값이며
        // in이 true인 경우 외부 문자열을 deserialize 하는 동작을 하는 것이므로
        // 할당할 대상인 value를 참조하면 안된다.
        return in ? "" : value;
    }

    void parse_args_data(const widget_type type, void* data, std::string& inout, std::string& version, const bool in)
    {        
        switch (type)
        {
        case widget_type::widget_type_none: return;

#pragma region // Windows
        case widget_type::widget_type_begin_end_window:
        {
            widget_begin_end_window* wd = (widget_begin_end_window*)data;
            default_parse(inout, version, in, wd, 
                "%b,%d", 
                wd->open, wd->flags);
            return;
        }
        case widget_type::widget_type_begin_end_child:
        {
            widget_begin_end_child* wd = (widget_begin_end_child*)data;
            default_parse(inout, version, in, wd,
                "%f,%f,%b,%d", 
                wd->size.x, wd->size.y, wd->border, wd->flags);
            return;
        }
#pragma endregion // Windows

#pragma region // Window manipulation
        case widget_type::widget_type_set_next_window_pos:
        {
            widget_set_next_window_pos* wd = (widget_set_next_window_pos*)data;
            default_parse(inout, version, in, wd,
                "%f,%f,%d,%f,%f", 
                wd->pos.x, wd->pos.y, wd->cond, wd->pivot.x, wd->pivot.y);
            return;
        }
        case widget_type::widget_type_set_next_window_size:
        {
            widget_set_next_window_size* wd = (widget_set_next_window_size*)data;
            default_parse(inout, version, in, wd,
                "%f,%f,%d", 
                wd->size.x, wd->size.y, wd->cond);
            return;
        }
        case widget_type::widget_type_set_next_window_content_size:
        {
            widget_set_next_window_content_size* wd = (widget_set_next_window_content_size*)data;
            default_parse(inout, version, in, wd,
                "%f,%f", 
                wd->size.x, wd->size.y);
            return;
        }
        case widget_type::widget_type_set_next_window_collapsed:
        {
            widget_set_next_window_collapsed* wd = (widget_set_next_window_collapsed*)data;
            default_parse(inout, version, in, wd,
                "%b,%d", 
                wd->collapsed, wd->cond);
            return;
        }
        case widget_type::widget_type_set_next_window_focus: return;
        case widget_type::widget_type_set_next_window_bg_alpha:
        {
            widget_set_next_window_bg_alpha* wd = (widget_set_next_window_bg_alpha*)data;
            default_parse(inout, version, in, wd,
                "%f", 
                wd->alpha);
            return;
        }

#pragma region // Parameters stacks (current window)
        case widget_type::widget_type_push_pop_item_width:
        {
            widget_push_pop_item_width* wd = (widget_push_pop_item_width*)data;
            default_parse(inout, version, in, wd, "%f", wd->item_width);
            return;
        }
        case widget_type::widget_type_push_pop_text_wrap_pos:
        {
            widget_push_pop_text_wrap_pos* wd = (widget_push_pop_text_wrap_pos*)data;
            default_parse(inout, version, in, wd, "%f", wd->item_width);
            return;
        }
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
        case widget_type::widget_type_separator: return;
        case widget_type::widget_type_same_line:
        {
            widget_same_line* wd = (widget_same_line*)data;
            default_parse(inout, version, in, wd, "%f,%f", wd->offset_from_start_x, wd->spacing);
            return;
        }
        case widget_type::widget_type_spacing: return;
        case widget_type::widget_type_dummy: 
        {
            widget_dummy* wd = (widget_dummy*)data;
            default_parse(inout, version, in, wd, "%f,%f", wd->size.x, wd->size.y);
            return;
        }
        case widget_type::widget_type_indent: 
        {
            widget_indent* wd = (widget_indent*)data;
            default_parse(inout, version, in, wd, "%f", wd->indent_w);
            return;
        }
        case widget_type::widget_type_unindent: 
        {
            widget_unindent* wd = (widget_unindent*)data;
            default_parse(inout, version, in, wd, "%f", wd->indent_w);
            return;
        }
        case widget_type::widget_type_begin_end_group: return;
        case widget_type::widget_type_set_cursor_pos:
        {
            widget_set_cursor_pos* wd = (widget_set_cursor_pos*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f", 
                wd->local_pos.x, wd->local_pos.y);
            return;
        }
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
        case widget_type::widget_type_text: return;
        case widget_type::widget_type_text_colored:
        { 
            widget_text_colored* wd = (widget_text_colored*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,", 
                wd->color.Value.x, wd->color.Value.y, wd->color.Value.z, wd->color.Value.w);
            return;
        }
        case widget_type::widget_type_label_text:
        {
            widget_label_text* wd = (widget_label_text*)data;
            default_parse(inout, version, in, wd, 
                "%s,", 
                to_safe_string2(in, wd->text).c_str());
            return;
        }
        case widget_type::widget_type_bullet_text: return;
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
        case widget_type::widget_type_button: 
        {
            widget_button* wd = (widget_button*)data;
            default_parse(inout, version, in, wd, "%f,%f,", wd->size.x, wd->size.y);
            return;
        }
        case widget_type::widget_type_small_button: return;
        case widget_type::widget_type_checkbox:
        {    
            widget_checkbox* wd = (widget_checkbox*)data;
            default_parse(inout, version, in, wd, "%b,", wd->check);
            return;
        }
        case widget_type::widget_type_checkbox_flags:
        {
            widget_checkbox_flags* wd = (widget_checkbox_flags*)data;
            default_parse(inout, version, in, wd, "%d,%d,", wd->flags, wd->flags_value);
            return;
        }
        case widget_type::widget_type_radio_button:
        {
            widget_radio_button* wd = (widget_radio_button*)data;
            default_parse(inout, version, in, wd, "%b,", wd->active);
            return;
        }
        case widget_type::widget_type_bullet: return;
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
        case widget_type::widget_type_begin_end_combo:
        {
            widget_begin_end_combo* wd = (widget_begin_end_combo*)data;
            default_parse(inout, version, in, wd, 
                "%s,%d", 
                to_safe_string2(in, wd->preview_value).c_str(), wd->flags);
            return;
        }
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
        case widget_type::widget_type_drag_float:
        {
            widget_drag_float* wd = (widget_drag_float*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%s,%d", 
                wd->value, 
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_drag_float2:
        {
            widget_drag_float2* wd = (widget_drag_float2*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float3:
        {
            widget_drag_float3* wd = (widget_drag_float3*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2],
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_drag_float4:
        {
            widget_drag_float4* wd = (widget_drag_float4*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%f,%f,%f,%s,%d",
                wd->value[0], wd->value[1], wd->value[2], wd->value[3],
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_drag_int:
        {
            widget_drag_int* wd = (widget_drag_int*)data;
            default_parse(inout, version, in, wd, 
                "%d,%f,%d,%d,%s,%d", 
                wd->value, 
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_drag_int2:
        {
            widget_drag_int2* wd = (widget_drag_int2*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%f,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_drag_int3:
        {
            widget_drag_int3* wd = (widget_drag_int3*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%f,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], 
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_drag_int4:
        {
            widget_drag_int4* wd = (widget_drag_int4*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%d,%f,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], 
                wd->speed, wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
        case widget_type::widget_type_slider_float:
        {
            widget_slider_float* wd = (widget_slider_float*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%s,%d", 
                wd->value, 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_float2:
        {
            widget_slider_float2* wd = (widget_slider_float2*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_float3:
        {
            widget_slider_float3* wd = (widget_slider_float3*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_float4:
        {
            widget_slider_float4* wd = (widget_slider_float4*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%f,%f,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_angle:
        {
            widget_slider_angle* wd = (widget_slider_angle*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%s,%d", 
                wd->value, 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_int:
        {
            widget_slider_int* wd = (widget_slider_int*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%s,%d", 
                wd->value, 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_int2:
        {
            widget_slider_int2* wd = (widget_slider_int2*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_int3:
        {
            widget_slider_int3* wd = (widget_slider_int3*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_slider_int4:
        {
            widget_slider_int4* wd = (widget_slider_int4*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%d,%d,%d,%s,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], 
                wd->min, wd->max, to_safe_string2(in, wd->format).c_str(), wd->flags);
            return;
        }
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
        case widget_type::widget_type_input_text:
        {
            widget_input_text* wd = (widget_input_text*)data;
            default_parse(inout, version, in, wd, 
                "%s,%d,",
                to_safe_string2(in, wd->text).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_input_text_multiline:
        {
            widget_input_text_multiline* wd = (widget_input_text_multiline*)data;
            default_parse(inout, version, in, wd, 
                "%s,%f,%f,%d,", 
                to_safe_string2(in, wd->text).c_str(), wd->size.x, wd->size.y, wd->flags);
            return;
        }
        case widget_type::widget_type_input_text_with_hint:
        {
            widget_input_text_with_hint* wd = (widget_input_text_with_hint*)data;
            default_parse(inout, version, in, wd, 
                "%s,%s,%d,", 
                to_safe_string2(in, wd->text).c_str(), to_safe_string2(in, wd->hint).c_str(), wd->flags);
            return;
        }
        case widget_type::widget_type_input_float:
        {
            widget_input_float* wd = (widget_input_float*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%d",
                wd->value, wd->step, wd->step_fast, wd->flags);
            return;
        }
        case widget_type::widget_type_input_float2:
        {
            widget_input_float2* wd = (widget_input_float2*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%d", 
                wd->value[0], wd->value[1], wd->flags);
            return;
        }
        case widget_type::widget_type_input_float3:
        {
            widget_input_float3* wd = (widget_input_float3*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->flags);
            return;
        }
        case widget_type::widget_type_input_float4:
        {
            widget_input_float4* wd = (widget_input_float4*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
            return;
        }
        case widget_type::widget_type_input_int:
        {
            widget_input_int* wd = (widget_input_int*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%d", 
                wd->value, wd->step, wd->step_fast, wd->flags);
            return;
        }
        case widget_type::widget_type_input_int2:
        {
            widget_input_int2* wd = (widget_input_int2*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d",
                wd->value[0], wd->value[1], wd->flags);
            return;
        }
        case widget_type::widget_type_input_int3:
        {
            widget_input_int3* wd = (widget_input_int3*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->flags);
            return;
        }
        case widget_type::widget_type_input_int4:
        {
            widget_input_int4* wd = (widget_input_int4*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%d,%d,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
            return;
        }
        case widget_type::widget_type_input_double:
        {
            widget_input_double* wd = (widget_input_double*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%d", 
                wd->value, wd->step, wd->step_fast, wd->flags);
            return;
        }
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
        case widget_type::widget_type_color_edit3:
        {
            widget_color_edit3* wd = (widget_color_edit3*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->flags);
            return;
        }
        case widget_type::widget_type_color_edit4:
        {
            widget_color_edit4* wd = (widget_color_edit4*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
            return;
        }
        case widget_type::widget_type_color_picker3:
        {
            widget_color_picker3* wd = (widget_color_picker3*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->flags);
            return;
        }
        case widget_type::widget_type_color_picker4:
        {
            widget_color_picker4* wd = (widget_color_picker4*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%d", 
                wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
            return;
        }
        case widget_type::widget_type_color_button:
        {
            widget_color_button* wd = (widget_color_button*)data;
            default_parse(inout, version, in, wd, 
                "%f,%f,%f,%f,%d,%f,%f", 
                wd->col.x, wd->col.y, wd->col.z, wd->col.w, wd->flags, wd->size.x, wd->size.y);
            return;
        }
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
        case widget_type::widget_type_push_pop_tree_node:
        {
            widget_push_pop_tree_node* wd = (widget_push_pop_tree_node*)data;
            default_parse(inout, version, in, wd, "%d", wd->flags);
            return;
        }
        case widget_type::widget_type_collapsing_header:
        {
            widget_collapsing_header* wd = (widget_collapsing_header*)data;
            default_parse(inout, version, in, wd, "%d",wd->flags);
            return;
        }        
#pragma endregion // Widgets: Trees

#pragma region // Widgets: Selectables
        case widget_type::widget_type_selectable:
        {
            widget_selectable* wd = (widget_selectable*)data;
            default_parse(inout, version, in, wd, 
                "%b,%d,%f,%f,", 
                wd->selected, wd->flags, wd->size.x, wd->size.y);
            return;
        }
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
        case widget_type::widget_type_begin_end_list_box:
        {
            widget_begin_end_list_box* wd = (widget_begin_end_list_box*)data;
            default_parse(inout, version, in, wd, 
                "%d,%d,%f,%f,", 
                wd->items_count, wd->items_height, wd->size.x, wd->size.y);
            return;
        }
#pragma endregion // Widgets: List Boxes
		
#pragma region // Widgets: Menus2
        case widget_type::widget_type_begin_end_menu_bar: return;
        case widget_type::widget_type_begin_end_menu:
        {
            widget_begin_end_menu* wd = (widget_begin_end_menu*)data;
            default_parse(inout, version, in, wd, "%d", wd->enabled);
            return;
        }
        case widget_type::widget_type_menu_item:
        {
            widget_menu_item* wd = (widget_menu_item*)data;
            default_parse(inout, version, in, wd, "%s,%b,%b",
                to_safe_string2(in, wd->shortcut).c_str(),
                wd->selected, 
                wd->enabled);
            return;
        }
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
        case widget_type::widget_type_begin_end_popup:
        {
            widget_begin_end_popup* wd = (widget_begin_end_popup*)data;
            default_parse(inout, version, in, wd, "%f", wd->flags);
            return;
        }
#pragma endregion // Popups, Modals
		
#pragma region // Tables
        case widget_type::widget_type_begin_end_table:
        {
            widget_begin_end_table* wd = (widget_begin_end_table*)data;
            default_parse(inout, version, in, wd, "%d,%d,%f,%f,%f",
                wd->columns,wd->flags,wd->outer_size.x,wd->outer_size.y,wd->inner_width);
            return;
        }
        case widget_type::widget_type_table_next_row:
        {
            widget_table_next_row* wd = (widget_table_next_row*)data;
            default_parse(inout, version, in, wd, "%d,%f", wd->flags, wd->min_row_height);
            return;
        }
        case widget_type::widget_type_table_next_column: return;
        case widget_type::widget_type_table_set_column_index:
        {
            widget_table_set_column_index* wd = (widget_table_set_column_index*)data;
            default_parse(inout, version, in, wd, "%d", wd->column_n);
            return;
        }
#pragma endregion // Tables

        default:
            debug_break();
            return;
        }
    }
}