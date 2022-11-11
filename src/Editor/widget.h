#ifndef __IE_WIDGET_H__
#define __IE_WIDGET_H__

#include "Editor/widget_type.h"

namespace ie
{
struct widget
{
    std::string label = "empty";
    std::vector<widget*> children;
    
    widget_type type = widget_type::widget_type_none;
    void* context = nullptr;
    void(*draw)(widget*);
};

void draw_widget(widget* context);

widget* new_widget(widget_type type);

void attach_child(widget* parent, widget* child);
}

#endif
