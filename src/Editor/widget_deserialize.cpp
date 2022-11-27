#include "Precompiled.h"

#include <sstream>
#include "editor/imgui_ex.h"

#include "editor/widget.h"
#include "editor/widget_data.h"

namespace imgui_editor
{
	std::istringstream& operator>> (std::istringstream& stream, ImGuiSelectableFlags_& flags)
	{
		int i = 0;
		stream >> i;
		flags = (ImGuiSelectableFlags_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiCol_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiCol_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiStyleVar_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiStyleVar_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiInputTextFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiInputTextFlags_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiColorEditFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiColorEditFlags_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiSliderFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiSliderFlags_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiTreeNodeFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiTreeNodeFlags_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiWindowFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiWindowFlags_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiTableFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiTableFlags_)i;
		return stream;
	}

	std::istringstream& operator>> (std::istringstream& stream, ImGuiComboFlags_& col)
	{
		int i = 0;
		stream >> i;
		col = (ImGuiComboFlags_)i;
		return stream;
	}

	void widget_data_deserialize(widget_type type, void* data, const char* str)
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
            stream >> wd->size.x;
            stream >> comma;
            stream >> wd->size.y;
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
            stream >> comma;
            stream >> wd->size.x;
            stream >> comma;
            stream >> wd->size.y;
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
        case widget_type::widget_type_dummy:
        {
            widget_dummy* wd = (widget_dummy*)data;
            stream >> wd->size.x;
            stream >> comma;
            stream >> wd->size.y;
        }
        break;
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
            stream >> wd->size.x;
            stream >> comma;
            stream >> wd->size.y;
            stream >> comma;
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
            stream >> wd->size.x;
            stream >> comma;
            stream >> wd->size.y;
            stream >> comma;
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
		}
	}

	static size_t parse(const std::string& source, const size_t begin, std::vector<std::string>& result)
	{
		std::string::size_type end = source.size();
		size_t count = 0;

		// 1 2123 21 23 212121 0
		// [ [][[n]] [[a]][][] ]

		// 121210
		// [[][]]

		// 10
		// []
		for (size_t i = begin; i < source.size(); ++i)
		{
			if ('[' == source[i])
			{
				++count;
			}
			else if (']' == source[i])
			{
				end = i;
				--count;
			}
			if (0 == count)break;
		}

		if (0 != end && begin < end && 0 < end - begin - 1)
		{
			std::string body = source.substr(begin + 1, end - begin - 1); // remove []

			//   1232 32 3210  10  12343 43 4321 210  
			// [ {[{},{},{}]}, {}, {{[{},{},{}]},[]}, {} ]
			//               ^   ^                  ^

			count = 0;
			size_t cursor = 0;
			for (size_t i = 0; i < body.size(); ++i)
			{
				if ('[' == body[i] || '{' == body[i])
				{
					++count;
				}
				else if (']' == body[i] || '}' == body[i])
				{
					--count;
				}
				else if (0 == count && ',' == body[i])
				{
					// empty pass
					if (0 < i - cursor)
					{
						result.push_back(body.substr(cursor, i - cursor)); // include {}
					}
					cursor = i + 1;
				}
			}
		}

		return end + 1; // remove ,
	}

	void widget_deserialize(widget* target_widget, const char* data)
	{
		std::string read;
		std::istringstream widget_stream(data);
		char* pos = NULL;

        std::getline(widget_stream, read, '{');
        std::getline(widget_stream, read, ',');
        target_widget->type = (widget_type)strtoul(read.c_str(), &pos, 0);

        std::getline(widget_stream, read, '{');
        std::getline(widget_stream, read, '}');

        if (nullptr != target_widget->args) delete_widget_args(target_widget->type, target_widget->args);
        target_widget->args = new_widget_arg(target_widget->type);

        widget_data_deserialize(target_widget->type, target_widget->args, read.c_str());

        std::getline(widget_stream, read, ',');

        std::getline(widget_stream, read, ',');
        target_widget->label = read;

        std::getline(widget_stream, read, ',');
        target_widget->size.x = strtof(read.c_str(), &pos);
        std::getline(widget_stream, read, ',');
        target_widget->size.y = strtof(read.c_str(), &pos);

        std::getline(widget_stream, read);

		for(size_t i= 0, max = target_widget->children.size(); i < max; ++i)
		{
			delete_widget(target_widget->children[i]);
		}
		target_widget->children.clear();

		std::vector<std::string> children;
		size_t next = parse(read, 0, children);
		for (size_t i = 0; i < children.size(); ++i)
		{
			widget* child_widget = new_widget(widget_type::widget_type_none);
			widget_deserialize(child_widget, children[i].c_str());

            target_widget->children.push_back(child_widget);
            child_widget->parent = target_widget;
		}

		char dummy;

		std::vector<std::string> style_colors;
		next = parse(read, next+1, style_colors);
		target_widget->style_colors.resize(style_colors.size());

		for (size_t i = 0; i < style_colors.size(); ++i)
		{
			std::istringstream stream(style_colors[i]);
			stream >> dummy; // {
			stream >> target_widget->style_colors[i].idx;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.x;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.y;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.z;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.w;
		}

		std::vector<std::string> style_var_floats;
		next = parse(read, next+1, style_var_floats);
		target_widget->style_var_floats.resize(style_var_floats.size());

		for (size_t i = 0; i < style_var_floats.size(); ++i)
		{
			std::istringstream stream(style_var_floats[i]);
			stream >> dummy; // {
			stream >> target_widget->style_var_floats[i].idx;
			stream >> dummy; // ,
			stream >> target_widget->style_var_floats[i].val;
		}

		std::vector<std::string> style_var_vec2s;
		next = parse(read, next+1, style_var_vec2s);
		target_widget->style_var_vec2s.resize(style_var_vec2s.size());

		for (size_t i = 0; i < style_var_vec2s.size(); ++i)
		{
			std::istringstream stream(style_var_vec2s[i]);
			stream >> dummy; // {
			stream >> target_widget->style_var_vec2s[i].idx;
			stream >> dummy; // ,
			stream >> target_widget->style_var_vec2s[i].val.x;
			stream >> dummy; // ,
			stream >> target_widget->style_var_vec2s[i].val.y;
		}
    }
}