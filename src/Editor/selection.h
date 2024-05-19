#ifndef __SELECTION_H__
#define __SELECTION_H__

BEGIN_NS_IMGUI_EDITOR

struct widget;
struct selection_context
{
    widget* target;
    std::vector<widget*> targets;
};

void init_selection(selection_context* ctx);

namespace selection
{
    widget* get_target();
    const std::vector<widget*>& get_targets();
    void reset();
    void clear();
}

END_NS_IMGUI_EDITOR

#endif
