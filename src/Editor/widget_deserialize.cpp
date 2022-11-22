#include "Precompiled.h"

#include "Editor/imgui_ex.h"

#include "Editor/widget.h"
#include "Editor/widget_data.h"

namespace imgui_editor
{
	void widget_data_deserialize(widget_type type, void* target, const char* data)
    {
        switch (type)
        {
        case widget_type::widget_type_none: return;
        case widget_type::widget_type_button: return;
        case widget_type::widget_type_small_button: return;
        case widget_type::widget_type_checkbox:
        {            
            widget_checkbox* wd = (widget_checkbox*)target;

            int check = 0;

            sscanf(data, "%d", &check);
            wd->check = check ? true : false;

        }
        case widget_type::widget_type_checkbox_flags:
        {
            widget_checkbox_flags* wd = (widget_checkbox_flags*)target;

            sscanf(data, "%d %d", &wd->flags, &wd->flags_value);

        }
        }
    }

    widget* widget_deserialize(const char* data)
    {
        widget* result = nullptr;
        return result;
    }
}