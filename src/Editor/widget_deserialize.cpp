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

    void widget_deserialize(widget* result, const char* d)
    {
        std::string data = d;

        std::string read;
        std::istringstream stream(d);
        char *pos = NULL;

        std::getline(stream, read, ',');
        result->type = (widget_type)strtoul(read.c_str(), &pos, 0);

        std::getline(stream, read, '{');
        std::getline(stream, read, '}');
        widget_data_deserialize(result->type, result->args, read.c_str());
        std::getline(stream, read, ',');
        
        std::getline(stream, read, ',');
        result->label = read;
        
        std::getline(stream, read, ',');
        result->size.x = strtof(read.c_str(), &pos);
        std::getline(stream, read, ',');
        result->size.y = strtof(read.c_str(), &pos);


        std::getline(stream, read, '[');
        std::getline(stream, read, ']');
    }
}