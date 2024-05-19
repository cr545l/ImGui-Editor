#ifndef __COMMAND_H__
#define __COMMAND_H__

BEGIN_NS_IMGUI_EDITOR

struct widget;
enum class widget_type : uint32_t;

// Support Undo / Redo
namespace command
{
    void create_widget(widget* parent, const widget_type& type, size_t index = -1);

    void attach_child(widget* parent, widget* child);

    void remove_widget(widget* target);

    void select(const widget* target);

    void select(std::initializer_list<widget*> targets);

    void select(const std::vector<widget*>& targets);
}

END_NS_IMGUI_EDITOR

#endif