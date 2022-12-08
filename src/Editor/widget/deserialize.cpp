#include "Precompiled.h"

#include "editor/imgui_ex.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"

namespace imgui_editor
{
	void widget_data_deserialize(widget_type type, void* data, const char* str, const std::string& version)
	{
		std::istringstream stream(str);
		char comma;
		switch (type)
		{
		case widget_type::widget_type_none: return;
		case widget_type::widget_type_button: return;
		case widget_type::widget_type_small_button: return;
		case widget_type::widget_type_checkbox:
        {            
            widget_checkbox* wd = (widget_checkbox*)data;
            stream >> wd->check;
        }
        break;
        case widget_type::widget_type_checkbox_flags:
        {
            widget_checkbox_flags* wd = (widget_checkbox_flags*)data;
            stream >> wd->flags;
            stream >> comma;
            stream >> wd->flags_value;
        }
        break;
		case widget_type::widget_type_radio_button:
		{
			widget_radio_button* wd = (widget_radio_button*)data;
			stream >> wd->active;
		}
		break;
		case widget_type::widget_type_text: return;
		case widget_type::widget_type_text_colored:
		{
			widget_text_colored* wd = (widget_text_colored*)data;
			stream >> wd->color.Value.x;
			stream >> comma;
			stream >> wd->color.Value.y;
			stream >> comma;
			stream >> wd->color.Value.z;
			stream >> comma;
			stream >> wd->color.Value.w;
		}
		break;
		case widget_type::widget_type_bullet_text: return;
		case widget_type::widget_type_bullet: return;
		case widget_type::widget_type_selectable:
		{
			widget_selectable* wd = (widget_selectable*)data;
			stream >> wd->selected;
			stream >> comma;
			stream >> wd->flags;
		}
		break;
		case widget_type::widget_type_label_text:
		{
			widget_label_text* wd = (widget_label_text*)data;
            stream >> wd->text;
		}
        case widget_type::widget_type_input_text:
        {
            widget_input_text* wd = (widget_input_text*)data;
            stream >> wd->text;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_text_multiline:
        {
            widget_input_text_multiline* wd = (widget_input_text_multiline*)data;
            stream >> wd->text;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_text_with_hint:
        {
            widget_input_text_with_hint* wd = (widget_input_text_with_hint*)data;
            stream >> wd->text;
            stream >> comma;
            stream >> wd->hint;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_int:
        {
            widget_input_int* wd = (widget_input_int*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->step;
            stream >> comma;
            stream >> wd->step_fast;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_int2:
        {
            widget_input_int2* wd = (widget_input_int2*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_int3:
        {
            widget_input_int3* wd = (widget_input_int3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_int4:
        {
            widget_input_int4* wd = (widget_input_int4*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->value[3];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_float:
        {
            widget_input_float* wd = (widget_input_float*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->step;
            stream >> comma;
            stream >> wd->step_fast;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_float2:
        {
            widget_input_float2* wd = (widget_input_float2*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_float3:
        {
            widget_input_float3* wd = (widget_input_float3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_input_double:
        {
            widget_input_double* wd = (widget_input_double*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->step;
            stream >> comma;
            stream >> wd->step_fast;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_int:
        {
            widget_drag_int* wd = (widget_drag_int*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->speed;
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_int2:
        {
            widget_drag_int2* wd = (widget_drag_int2*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_int3:
        {
            widget_drag_int3* wd = (widget_drag_int3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_int4:
        {
            widget_drag_int4* wd = (widget_drag_int4*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->value[3];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_float:
        {
            widget_drag_float* wd = (widget_drag_float*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->speed;
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_float2:
        {
            widget_drag_float2* wd = (widget_drag_float2*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_float3:
        {
            widget_drag_float3* wd = (widget_drag_float3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_drag_float4:
        {
            widget_drag_float4* wd = (widget_drag_float4*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->value[3];
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_int:
        {
            widget_slider_int* wd = (widget_slider_int*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_int2:
        {
            widget_slider_int2* wd = (widget_slider_int2*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_int3:
        {
            widget_slider_int3* wd = (widget_slider_int3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_int4:
        {
            widget_slider_int4* wd = (widget_slider_int4*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->value[3];
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_float:
        {
            widget_slider_float* wd = (widget_slider_float*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }  
        break;
        case widget_type::widget_type_slider_float2:
        {
            widget_slider_float2* wd = (widget_slider_float2*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_float3:
        {
            widget_slider_float3* wd = (widget_slider_float3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_float4:
        {
            widget_slider_float4* wd = (widget_slider_float4*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->value[3];
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_slider_angle:
        {
            widget_slider_angle* wd = (widget_slider_angle*)data;
            stream >> wd->value;
            stream >> comma;
            stream >> wd->min;
            stream >> comma;
            stream >> wd->max;
            stream >> comma;
            stream >> wd->format;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_color_edit3:
        {
            widget_color_edit3* wd = (widget_color_edit3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_color_edit4:
        {
            widget_color_edit4* wd = (widget_color_edit4*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->value[3];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_color_picker3:
        {
            widget_color_picker3* wd = (widget_color_picker3*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_color_picker4:
        {
            widget_color_picker4* wd = (widget_color_picker4*)data;
            stream >> wd->value[0];
            stream >> comma;
            stream >> wd->value[1];
            stream >> comma;
            stream >> wd->value[2];
            stream >> comma;
            stream >> wd->value[3];
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_color_button:
        {
            widget_color_button* wd = (widget_color_button*)data;
            stream >> wd->col.x;
            stream >> comma;
            stream >> wd->col.y;
            stream >> comma;
            stream >> wd->col.z;
            stream >> comma;
            stream >> wd->col.w;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_collapsing_header:
        {
            widget_collapsing_header* wd = (widget_collapsing_header*)data;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_separator: return;
        case widget_type::widget_type_same_line:
        {
            widget_same_line* wd = (widget_same_line*)data;
            stream >> wd->offset_from_start_x;
            stream >> comma;
            stream >> wd->spacing;
        }
        break;
        case widget_type::widget_type_spacing: return;
        case widget_type::widget_type_dummy: return;
        case widget_type::widget_type_indent:
        {
            widget_indent* wd = (widget_indent*)data;
            stream >> wd->indent_w;
        }
        break;
        case widget_type::widget_type_unindent:
        {
            widget_unindent* wd = (widget_unindent*)data;
            stream >> wd->indent_w;
        }
        break;
        case widget_type::widget_type_begin_end_window:
        {
            widget_begin_end_window* wd = (widget_begin_end_window*)data;
            stream >> wd->open;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_begin_end_child:
        {
            widget_begin_end_child* wd = (widget_begin_end_child*)data;
            stream >> wd->border;
            stream >> comma;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_begin_end_popup:
        {
            widget_begin_end_popup* wd = (widget_begin_end_popup*)data;
            stream >> wd->flags;
        }
        break;
        case widget_type::widget_type_begin_end_list_box:
        {
            widget_begin_end_list_box* wd = (widget_begin_end_list_box*)data;
            stream >> wd->items_count;
            stream >> comma;
            stream >> wd->items_height;
        }
        break;
        case widget_type::widget_type_begin_end_table:
        {
            widget_begin_end_table* wd = (widget_begin_end_table*)data;
            stream >> wd->columns;
            stream >> comma;
            stream >> wd->flags;
            stream >> comma;
            stream >> wd->outer_size.x;
            stream >> comma;
            stream >> wd->outer_size.y;
            stream >> comma;
            stream >> wd->inner_width;
        }
        break;
        case widget_type::widget_type_begin_end_group: return;
        case widget_type::widget_type_begin_end_combo:
        {
            widget_begin_end_combo* wd = (widget_begin_end_combo*)data;
            stream >> wd->preview_value;
            stream >> comma;
            stream >> wd->flags;
        } 
        break;
        case widget_type::widget_type_begin_end_menu:
        {
            widget_begin_end_menu* wd = (widget_begin_end_menu*)data;
            stream >> wd->enabled;
        }
        break;
        case widget_type::widget_type_push_pop_tree_node:
        {
            widget_push_pop_tree_node* wd = (widget_push_pop_tree_node*)data;
			stream >> wd->flags;
		}
		break;
		case widget_type::widget_type_push_pop_item_width:
		{
			widget_push_pop_item_width* wd = (widget_push_pop_item_width*)data;
			stream >> wd->item_width;
		}
		break;
		case widget_type::widget_type_push_pop_text_wrap_pos:
		{
			widget_push_pop_text_wrap_pos* wd = (widget_push_pop_text_wrap_pos*)data;
			stream >> wd->item_width;
		}
		break;
		}
	}
}