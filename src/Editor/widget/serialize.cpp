#include "Precompiled.h"

#include "editor/imgui_ex.h"
#include "editor/widget.h"
#include "editor/widget/args_data.h" 

namespace imgui_editor
{
	std::string widget_data_serialize(widget_type type, void* data, const char*& version)
    {
        switch (type)
        {
        case widget_type::widget_type_none: return "";

#pragma region // Windows
        case widget_type::widget_type_begin_end_window:
        {
            version = "0";
            widget_begin_end_window* wd = (widget_begin_end_window*)data;
            return string_format("%d,%d", wd->open,  wd->flags);
        }
        case widget_type::widget_type_begin_end_child:
        {
            version = "0";
            widget_begin_end_child* wd = (widget_begin_end_child*)data;
            return string_format("%d,%d", wd->border, wd->flags);
        }
#pragma endregion // Windows

#pragma region // Parameters stacks (current window)
        case widget_type::widget_type_push_pop_item_width:
        {
            version = "0";
            widget_push_pop_item_width* wd = (widget_push_pop_item_width*)data;
            return string_format("%f", wd->item_width);
        }
        case widget_type::widget_type_push_pop_text_wrap_pos:
        {
            version = "0";
            widget_push_pop_text_wrap_pos* wd = (widget_push_pop_text_wrap_pos*)data;
            return string_format("%f", wd->item_width);
        }
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
        case widget_type::widget_type_separator: return "";
        case widget_type::widget_type_same_line:
        {
            version = "0";
            widget_same_line* wd = (widget_same_line*)data;
            return string_format("%f,%f", wd->offset_from_start_x, wd->spacing);
        }
        case widget_type::widget_type_spacing: return "";
        case widget_type::widget_type_dummy: return "";
        case widget_type::widget_type_indent: 
        {
            version = "0";
            widget_indent* wd = (widget_indent*)data;
            return string_format("%f", wd->indent_w);
        }
        case widget_type::widget_type_unindent: 
        {
            version = "0";
            widget_unindent* wd = (widget_unindent*)data;
            return string_format("%f", wd->indent_w);
        }
        case widget_type::widget_type_begin_end_group: return "";
        case widget_type::widget_type_set_cursor_pos:
        {
            version = "0";
            widget_set_cursor_pos* wd = (widget_set_cursor_pos*)data;
            return string_format("%f,%f", wd->local_pos.x, wd->local_pos.y);
        }
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
        case widget_type::widget_type_text: return "";
        case widget_type::widget_type_text_colored:
        {
            version = "0";
            widget_text_colored* wd = (widget_text_colored*)data;
            return string_format("%f,%f,%f,%f,", wd->color.Value.x, wd->color.Value.y, wd->color.Value.z, wd->color.Value.w);
        }
        case widget_type::widget_type_label_text:
        {
            version = "0";
            widget_label_text* wd = (widget_label_text*)data;
            return string_format("%s,", wd->text.c_str());
        }
        case widget_type::widget_type_bullet_text: return "";
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
        case widget_type::widget_type_button: return "";
        case widget_type::widget_type_small_button: return "";
        case widget_type::widget_type_checkbox:
        {
            version = "0";
            widget_checkbox* wd = (widget_checkbox*)data;            
            return string_format("%d,", wd->check);
        }
        case widget_type::widget_type_checkbox_flags:
        {
            version = "0";
            widget_checkbox_flags* wd = (widget_checkbox_flags*)data;
            return string_format("%d,%d,", wd->flags, wd->flags_value);
        }
        case widget_type::widget_type_radio_button:
        {
            version = "0";
            widget_radio_button* wd = (widget_radio_button*)data;
            return string_format("%d,", wd->active);
        }
        case widget_type::widget_type_bullet: return "";
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
        case widget_type::widget_type_begin_end_combo:
        {
            version = "0";
            widget_begin_end_combo* wd = (widget_begin_end_combo*)data;
            return string_format("%s,%d", wd->preview_value.c_str(), wd->flags);
        }
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
        case widget_type::widget_type_drag_float:
        {
            version = "0";
            widget_drag_float* wd = (widget_drag_float*)data;
            return string_format("%f,%f,%f,%f,%s,%d", wd->value, wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float2:
        {
            version = "0";
            widget_drag_float2* wd = (widget_drag_float2*)data;
            return string_format("%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float3:
        {
            version = "0";
            widget_drag_float3* wd = (widget_drag_float3*)data;
            return string_format("%f,%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float4:
        {
            version = "0";
            widget_drag_float4* wd = (widget_drag_float4*)data;
            return string_format("%f,%f,%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int:
        {
            version = "0";
            widget_drag_int* wd = (widget_drag_int*)data;
            return string_format("%d,%f,%d,%d,%s,%d", wd->value, wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int2:
        {
            version = "0";
            widget_drag_int2* wd = (widget_drag_int2*)data;
            return string_format("%d,%d,%f,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int3:
        {
            version = "0";
            widget_drag_int3* wd = (widget_drag_int3*)data;
            return string_format("%d,%d,%d,%f,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int4:
        {
            version = "0";
            widget_drag_int4* wd = (widget_drag_int4*)data;
            return string_format("%d,%d,%d,%d,%f,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
        case widget_type::widget_type_slider_float:
        {
            version = "0";
            widget_slider_float* wd = (widget_slider_float*)data;
            return string_format("%f,%f,%f,%s,%d", wd->value, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float2:
        {
            version = "0";
            widget_slider_float2* wd = (widget_slider_float2*)data;
            return string_format("%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float3:
        {
            version = "0";
            widget_slider_float3* wd = (widget_slider_float3*)data;
            return string_format("%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float4:
        {
            version = "0";
            widget_slider_float4* wd = (widget_slider_float4*)data;
            return string_format("%f,%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_angle:
        {
            version = "0";
            widget_slider_angle* wd = (widget_slider_angle*)data;
            return string_format("%f,%f,%f,%s,%d", wd->value, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int:
        {
            version = "0";
            widget_slider_int* wd = (widget_slider_int*)data;
            return string_format("%d,%d,%d,%s,%d", wd->value, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int2:
        {
            version = "0";
            widget_slider_int2* wd = (widget_slider_int2*)data;
            return string_format("%d,%d,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int3:
        {
            version = "0";
            widget_slider_int3* wd = (widget_slider_int3*)data;
            return string_format("%d,%d,%d,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int4:
        {
            version = "0";
            widget_slider_int4* wd = (widget_slider_int4*)data;
            return string_format("%d,%d,%d,%d,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
        case widget_type::widget_type_input_text:
        {
            version = "0";
            widget_input_text* wd = (widget_input_text*)data;
            return string_format("%s,%d,", wd->text.c_str(), wd->flags);
        }
        case widget_type::widget_type_input_text_multiline:
        {
            version = "0";
            widget_input_text_multiline* wd = (widget_input_text_multiline*)data;
            return string_format("%s,%d,", wd->text.c_str(), wd->flags);
        }
        case widget_type::widget_type_input_text_with_hint:
        {
            version = "0";
            widget_input_text_with_hint* wd = (widget_input_text_with_hint*)data;
            return string_format("%s,%s,%d,", wd->text.c_str(), wd->hint.c_str(), wd->flags);
        }
        case widget_type::widget_type_input_float:
        {
            version = "0";
            widget_input_float* wd = (widget_input_float*)data;
            return string_format("%f,%f,%f,%d", wd->value, wd->step, wd->step_fast, wd->flags);
        }
        case widget_type::widget_type_input_float2:
        {
            version = "0";
            widget_input_float2* wd = (widget_input_float2*)data;
            return string_format("%f,%f,%d", wd->value[0], wd->value[1], wd->flags);
        }
        case widget_type::widget_type_input_float3:
        {
            version = "0";
            widget_input_float3* wd = (widget_input_float3*)data;
            return string_format("%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_input_float4:
        {
            version = "0";
            widget_input_float4* wd = (widget_input_float4*)data;
            return string_format("%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_input_int:
        {
            version = "0";
            widget_input_int* wd = (widget_input_int*)data;
            return string_format("%d,%d,%d,%d", wd->value, wd->step, wd->step_fast, wd->flags);
        }
        case widget_type::widget_type_input_int2:
        {
            version = "0";
            widget_input_int2* wd = (widget_input_int2*)data;
            return string_format("%d,%d,%d", wd->value[0], wd->value[1], wd->flags);
        }
        case widget_type::widget_type_input_int3:
        {
            version = "0";
            widget_input_int3* wd = (widget_input_int3*)data;
            return string_format("%d,%d,%d,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_input_int4:
        {
            version = "0";
            widget_input_int4* wd = (widget_input_int4*)data;
            return string_format("%d,%d,%d,%d,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_input_double:
        {
            version = "0";
            widget_input_double* wd = (widget_input_double*)data;
            return string_format("%f,%f,%f,%d", wd->value, wd->step, wd->step_fast, wd->flags);
        }
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
        case widget_type::widget_type_color_edit3:
        {
            version = "0";
            widget_color_edit3* wd = (widget_color_edit3*)data;
            return string_format("%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_color_edit4:
        {
            version = "0";
            widget_color_edit4* wd = (widget_color_edit4*)data;
            return string_format("%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_color_picker3:
        {
            version = "0";
            widget_color_picker3* wd = (widget_color_picker3*)data;
            return string_format("%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_color_picker4:
        {
            version = "0";
            widget_color_picker4* wd = (widget_color_picker4*)data;
            return string_format("%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_color_button:
        {
            version = "0";
            widget_color_button* wd = (widget_color_button*)data;
            return string_format("%f,%f,%f,%f,%d,%f,%f", wd->col.x, wd->col.y, wd->col.z, wd->col.w, wd->flags, wd->size.x, wd->size.y);
        }
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
        case widget_type::widget_type_push_pop_tree_node:
        {
            version = "0";
            widget_push_pop_tree_node* wd = (widget_push_pop_tree_node*)data;
            return string_format("%d", wd->flags);
        }
        case widget_type::widget_type_collapsing_header:
        {
            version = "0";
            widget_collapsing_header* wd = (widget_collapsing_header*)data;
            return string_format("%d",wd->flags);
        }        
#pragma endregion // Widgets: Trees


#pragma region // Widgets: Selectables
        case widget_type::widget_type_selectable:
        {
            version = "0";
            widget_selectable* wd = (widget_selectable*)data;
            return string_format("%d,%d,", wd->selected, wd->flags);
        }
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
        case widget_type::widget_type_begin_end_list_box:
        {
            version = "0";
            widget_begin_end_list_box* wd = (widget_begin_end_list_box*)data;
            return string_format("%d,%d", wd->items_count, wd->items_height);
        }
#pragma endregion // Widgets: List Boxes
		
#pragma region // Widgets: Menus
        case widget_type::widget_type_begin_end_menu:
        {
            version = "0";
            widget_begin_end_menu* wd = (widget_begin_end_menu*)data;
            return string_format("%d", wd->enabled);
        }
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
        case widget_type::widget_type_begin_end_popup:
        {
            version = "0";
            widget_begin_end_popup* wd = (widget_begin_end_popup*)data;
            return string_format("%f", wd->flags);
        }
#pragma endregion // Popups, Modals
		
#pragma region // Tables
        case widget_type::widget_type_begin_end_table:
        {
            version = "0";
            widget_begin_end_table* wd = (widget_begin_end_table*)data;
            return string_format("%d,%d,%f,%f,%f",wd->columns,wd->flags,wd->outer_size.x,wd->outer_size.y,wd->inner_width);
        }
        case widget_type::widget_type_table_next_row:
        {
            version = "0";
            widget_table_next_row* wd = (widget_table_next_row*)data;
            return string_format("%d,%f", wd->flags, wd->min_row_height);
        }
        case widget_type::widget_type_table_next_column: return "";
        case widget_type::widget_type_table_set_column_index:
        {
            version = "0";
            widget_table_set_column_index* wd = (widget_table_set_column_index*)data;
            return string_format("%d", wd->column_n);
        }
#pragma endregion // Tables

        default:
            debug_break();
            return "";
        }
    }
}