#ifndef __IE_WIDGET_EDITOR_H__
#define __IE_WIDGET_EDITOR_H__

#include "Editor/widget.h"

namespace ie
{
struct widget;
struct widget_editor;

struct widget_tool
{
    widget_editor* editor = nullptr;
    widget* root = nullptr;
    widget_type type = widget_type::widget_type_none;
};

struct widget_hierarchy
{
    widget_editor* editor = nullptr;
    widget* target = nullptr;
};

struct widget_inspector
{
    widget_editor* editor = nullptr;
};

struct widget_editor
{
    widget root;
    
    widget_tool tool;
    widget_hierarchy hirarchy;
    widget_inspector inspector;
};

void init_widget_editor(widget_editor* context);

void draw_widget_tool(widget_tool* context);
void draw_widget_hierarchy(widget_hierarchy* context);
void draw_widget_inspector(widget_inspector* context);

void draw_widget_editor(widget_editor* context);
}

#endif
