#include "Precompiled.h"

#include <sstream>
#include "Editor/imgui_ex.h"

#include "Editor/widget.h"
#include "Editor/widget_data.h"

namespace imgui_editor
{
	void widget_data_deserialize(widget_type type, void* data, const char* str)
    {
        std::istringstream stream(str);
        char comma ;
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
        }
    }

    void widget_deserialize(widget* target_widget, const char* d)
    {
        std::string data = d;

        std::string read;
        std::istringstream stream(d);
        char* pos = NULL;

        std::getline(stream, read, '{');
        std::getline(stream, read, ',');
        target_widget->type = (widget_type)strtoul(read.c_str(), &pos, 0);

        std::getline(stream, read, '{');
        std::getline(stream, read, '}');

        if (nullptr != target_widget->args) delete_widget_args(target_widget->type, target_widget->args);
        target_widget->args = new_widget_arg(target_widget->type);

        widget_data_deserialize(target_widget->type, target_widget->args, read.c_str());

        std::getline(stream, read, ',');

        std::getline(stream, read, ',');
        target_widget->label = read;

        std::getline(stream, read, ',');
        target_widget->size.x = strtof(read.c_str(), &pos);
        std::getline(stream, read, ',');
        target_widget->size.y = strtof(read.c_str(), &pos);

        std::getline(stream, read);

        // 1 2123 21 23 212121 0
        // [ [][[n]] [[a]][][] ]

        // 121210
        // [[][]]

        // 10
        // []
        const std::string::size_type begin = read.find('[');
        std::string::size_type end = read.size();
        size_t count = 0;
        for (size_t i = begin; i < read.size(); ++i)
        {
            if ('[' == read[i])
            {
                ++count;
            }
            else if (']' == read[i])
            {
                end = i;
                --count;
            }
            if (0 == count)break;
        }
        std::string body = read.substr(begin + 1, end - begin - 1); // remove []

        //   1232 32 3210  10  12343 43 4321 210  
        // [ {[{},{},{}]}, {}, {{[{},{},{}]},[]}, {} ]
        //               ^   ^                  ^

        count = 0;
        std::vector<std::string> children;
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
                children.push_back(body.substr(cursor, i - cursor - 1));
                cursor = i + 1;
            }
        }

        for (size_t i = 0; i < children.size(); ++i)
        {
            widget* child_widget = new_widget(widget_type::widget_type_none);
            widget_deserialize(child_widget, children[i].c_str());
            attach_child(target_widget, child_widget);
        }

		std::getline(stream, read, ']');
		//
		std::getline(stream, read, ',');

		std::getline(stream, read, '[');
		std::getline(stream, read, ']');
		//
		std::getline(stream, read, ',');

		std::getline(stream, read, '[');
		std::getline(stream, read, ']');
		//
		std::getline(stream, read, ',');

		std::getline(stream, read, '[');
		std::getline(stream, read, ']');
		//
		std::getline(stream, read, ',');
		std::getline(stream, read, '}');
    }
}