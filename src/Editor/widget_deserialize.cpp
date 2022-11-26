#include "Precompiled.h"

#include <sstream>
#include "Editor/imgui_ex.h"

#include "Editor/widget.h"
#include "Editor/widget_data.h"

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
			attach_child(target_widget, child_widget);
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