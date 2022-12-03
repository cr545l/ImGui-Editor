#include "Precompiled.h"

#include "editor/imgui_ex.h"
#include "editor/widget.h"
#include "editor/widget_data.h" 

namespace imgui_editor
{
	std::string widget_data_serialize(widget_type type, void* data)
    {
        switch (type)
        {
        case widget_type::widget_type_none: return "";
        case widget_type::widget_type_button: return "";
        case widget_type::widget_type_small_button: return "";
        case widget_type::widget_type_checkbox:
        {
            widget_checkbox* wd = (widget_checkbox*)data;            
            return string_format("%d,", wd->check);
        }
        case widget_type::widget_type_checkbox_flags:
        {
            widget_checkbox_flags* wd = (widget_checkbox_flags*)data;
            return string_format("%d,%d,", wd->flags, wd->flags_value);
        }
        case widget_type::widget_type_radio_button:
        {
            widget_radio_button* wd = (widget_radio_button*)data;
            return string_format("%d,", wd->active);
        }
        case widget_type::widget_type_text: return "";
        case widget_type::widget_type_text_colored:
        {
            widget_text_colored* wd = (widget_text_colored*)data;
            return string_format("%f,%f,%f,%f,", wd->color.Value.x, wd->color.Value.y, wd->color.Value.z, wd->color.Value.w);
        }
        case widget_type::widget_type_bullet_text: return "";
        case widget_type::widget_type_bullet: return "";
        case widget_type::widget_type_selectable:
        {
            widget_selectable* wd = (widget_selectable*)data;
            return string_format("%d,%d,", wd->selected, wd->flags);
        }
        case widget_type::widget_type_label_text:
        {
            widget_label_text* wd = (widget_label_text*)data;
            return string_format("%s,", wd->text.c_str());
        }
        case widget_type::widget_type_input_text:
        {
            widget_input_text* wd = (widget_input_text*)data;
            return string_format("%s,%d,", wd->text.c_str(), wd->flags);
        }
        case widget_type::widget_type_input_text_multiline:
        {
            widget_input_text_multiline* wd = (widget_input_text_multiline*)data;
            return string_format("%s,%d,", wd->text.c_str(), wd->flags);
        }
        case widget_type::widget_type_input_text_with_hint:
        {
            widget_input_text_with_hint* wd = (widget_input_text_with_hint*)data;
            return string_format("%s,%s,%d,", wd->text.c_str(), wd->hint.c_str(), wd->flags);
        }
        case widget_type::widget_type_input_int:
        {
            widget_input_int* wd = (widget_input_int*)data;
            return string_format("%d,%d,%d,%d", wd->value, wd->step, wd->step_fast, wd->flags);
        }
        case widget_type::widget_type_input_int2:
        {
            widget_input_int2* wd = (widget_input_int2*)data;
            return string_format("%d,%d,%d", wd->value[0], wd->value[1], wd->flags);
        }
        case widget_type::widget_type_input_int3:
        {
            widget_input_int3* wd = (widget_input_int3*)data;
            return string_format("%d,%d,%d,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_input_int4:
        {
            widget_input_int4* wd = (widget_input_int4*)data;
            return string_format("%d,%d,%d,%d,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_input_float:
        {
            widget_input_float* wd = (widget_input_float*)data;
            return string_format("%f,%f,%f,%d", wd->value, wd->step, wd->step_fast, wd->flags);
        }
        case widget_type::widget_type_input_float2:
        {
            widget_input_float2* wd = (widget_input_float2*)data;
            return string_format("%f,%f,%d", wd->value[0], wd->value[1], wd->flags);
        }
        case widget_type::widget_type_input_float3:
        {
            widget_input_float3* wd = (widget_input_float3*)data;
            return string_format("%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_input_float4:
        {
            widget_input_float4* wd = (widget_input_float4*)data;
            return string_format("%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_input_double:
        {
            widget_input_double* wd = (widget_input_double*)data;
            return string_format("%f,%f,%f,%d", wd->value, wd->step, wd->step_fast, wd->flags);
        }
        case widget_type::widget_type_drag_int:
        {
            widget_drag_int* wd = (widget_drag_int*)data;
            return string_format("%d,%f,%d,%d,%s,%d", wd->value, wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int2:
        {
            widget_drag_int2* wd = (widget_drag_int2*)data;
            return string_format("%d,%d,%f,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int3:
        {
            widget_drag_int3* wd = (widget_drag_int3*)data;
            return string_format("%d,%d,%d,%f,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_int4:
        {
            widget_drag_int4* wd = (widget_drag_int4*)data;
            return string_format("%d,%d,%d,%d,%f,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float:
        {
            widget_drag_float* wd = (widget_drag_float*)data;
            return string_format("%f,%f,%f,%f,%s,%d", wd->value, wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float2:
        {
            widget_drag_float2* wd = (widget_drag_float2*)data;
            return string_format("%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float3:
        {
            widget_drag_float3* wd = (widget_drag_float3*)data;
            return string_format("%f,%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_drag_float4:
        {
            widget_drag_float4* wd = (widget_drag_float4*)data;
            return string_format("%f,%f,%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->speed, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int:
        {
            widget_slider_int* wd = (widget_slider_int*)data;
            return string_format("%d,%d,%d,%s,%d", wd->value, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int2:
        {
            widget_slider_int2* wd = (widget_slider_int2*)data;
            return string_format("%d,%d,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int3:
        {
            widget_slider_int3* wd = (widget_slider_int3*)data;
            return string_format("%d,%d,%d,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_int4:
        {
            widget_slider_int4* wd = (widget_slider_int4*)data;
            return string_format("%d,%d,%d,%d,%d,%d,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float:
        {
            widget_slider_float* wd = (widget_slider_float*)data;
            return string_format("%f,%f,%f,%s,%d", wd->value, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float2:
        {
            widget_slider_float2* wd = (widget_slider_float2*)data;
            return string_format("%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float3:
        {
            widget_slider_float3* wd = (widget_slider_float3*)data;
            return string_format("%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_float4:
        {
            widget_slider_float4* wd = (widget_slider_float4*)data;
            return string_format("%f,%f,%f,%f,%f,%f,%s,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_slider_angle:
        {
            widget_slider_angle* wd = (widget_slider_angle*)data;
            return string_format("%f,%f,%f,%s,%d", wd->value, wd->min, wd->max, wd->format.c_str(), wd->flags);
        }
        case widget_type::widget_type_color_edit3:
        {
            widget_color_edit3* wd = (widget_color_edit3*)data;
            return string_format("%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_color_edit4:
        {
            widget_color_edit4* wd = (widget_color_edit4*)data;
            return string_format("%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_color_picker3:
        {
            widget_color_picker3* wd = (widget_color_picker3*)data;
            return string_format("%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->flags);
        }
        case widget_type::widget_type_color_picker4:
        {
            widget_color_picker4* wd = (widget_color_picker4*)data;
            return string_format("%f,%f,%f,%f,%d", wd->value[0], wd->value[1], wd->value[2], wd->value[3], wd->flags);
        }
        case widget_type::widget_type_color_button:
        {
            widget_color_button* wd = (widget_color_button*)data;
            return string_format("%f,%f,%f,%f,%d", wd->col.x, wd->col.y, wd->col.z, wd->col.w, wd->flags);
        }
        case widget_type::widget_type_collapsing_header:
        {
            widget_collapsing_header* wd = (widget_collapsing_header*)data;
            return string_format("%d",wd->flags);
        }        
        case widget_type::widget_type_separator: return "";
        case widget_type::widget_type_same_line:
        {
            widget_same_line* wd = (widget_same_line*)data;
            return string_format("%f,%f", wd->offset_from_start_x, wd->spacing);
        }
        case widget_type::widget_type_spacing: return "";
        case widget_type::widget_type_dummy: return "";
        case widget_type::widget_type_indent: 
        {
            widget_indent* wd = (widget_indent*)data;
            return string_format("%f", wd->indent_w);
        }
        case widget_type::widget_type_unindent: 
        {
            widget_unindent* wd = (widget_unindent*)data;
            return string_format("%f", wd->indent_w);
        }
        case widget_type::widget_type_begin_end_window:
        {
            widget_begin_end_window* wd = (widget_begin_end_window*)data;
            return string_format("%d,%d", wd->open,  wd->flags);
        }
        case widget_type::widget_type_begin_end_child:
        {
            widget_begin_end_child* wd = (widget_begin_end_child*)data;
            return string_format("%d,%d", wd->border, wd->flags);
        }
        case widget_type::widget_type_begin_end_popup:
        {
            widget_begin_end_popup* wd = (widget_begin_end_popup*)data;
            return string_format("%f", wd->flags);
        }
        case widget_type::widget_type_begin_end_list_box:
        {
            widget_begin_end_list_box* wd = (widget_begin_end_list_box*)data;
            return string_format("%d,%d", wd->items_count, wd->items_height);
        }
        case widget_type::widget_type_begin_end_table:
        {
            widget_begin_end_table* wd = (widget_begin_end_table*)data;
            return string_format("%d,%d,%f,%f,%f",wd->columns,wd->flags,wd->outer_size.x,wd->outer_size.y,wd->inner_width);
        }
        case widget_type::widget_type_begin_end_group: return "";
        case widget_type::widget_type_begin_end_combo:
        {
            widget_begin_end_combo* wd = (widget_begin_end_combo*)data;
            return string_format("%s,%d", wd->preview_value.c_str(), wd->flags);
        }
        case widget_type::widget_type_begin_end_menu:
        {
            widget_begin_end_menu* wd = (widget_begin_end_menu*)data;
            return string_format("%d", wd->enabled);
        }
        case widget_type::widget_type_push_pop_tree_node:
        {
            widget_push_pop_tree_node* wd = (widget_push_pop_tree_node*)data;
            return string_format("%d", wd->flags);
        }
        case widget_type::widget_type_push_pop_item_width:
        {
            widget_push_pop_item_width* wd = (widget_push_pop_item_width*)data;
            return string_format("%f", wd->item_width);
        }
        case widget_type::widget_type_push_pop_text_wrap_pos:
        {
            widget_push_pop_text_wrap_pos* wd = (widget_push_pop_text_wrap_pos*)data;
            return string_format("%f", wd->item_width);
        }
        default:
            debug_break();
            return "";
        }
    }
    
	std::string widget_serialize(widget* target)
    {
        std::string children;
        for(size_t i = 0, max = target->children.size(); i < max; ++i)
        {
            children += string_format("%s,", widget_serialize(target->children[i]).c_str());
        }

        std::string style_colors;
        for (size_t i = 0, max = target->style_colors.size(); i < max; ++i)
        {
            style_colors += string_format("{%d,%f,%f,%f,%f},", (int)target->style_colors[i].idx, target->style_colors[i].col.Value.x, target->style_colors[i].col.Value.y, target->style_colors[i].col.Value.z, target->style_colors[i].col.Value.w);
        }

        std::string style_var_floats;
        for (size_t i = 0, max = target->style_var_floats.size(); i < max; ++i)
        {
            style_var_floats += string_format("{%d,%f},", (int)target->style_var_floats[i].idx, target->style_var_floats[i].val);
        }

		std::string style_var_vec2s;
		for (size_t i = 0, max = target->style_var_vec2s.size(); i < max; ++i)
		{
            style_var_vec2s += string_format("{%d,%f,%f},", (int)target->style_var_vec2s[i].idx, target->style_var_vec2s[i].val.x, target->style_var_vec2s[i].val.y);
		}

        return string_format("{%d,{%s},%s,%f,%f,[%s],[%s],[%s],[%s]}", 
        target->type,
        widget_data_serialize(target->type, target->args).c_str(),
        target->label.c_str(), 
        target->size.x, 
        target->size.y, 
        children.c_str(),
        style_colors.c_str(),
        style_var_floats.c_str(),
        style_var_vec2s.c_str());
    }
}