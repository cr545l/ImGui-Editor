#ifndef __IE_SELECTION_H__
#define __IE_SELECTION_H__

namespace ie
{
struct widget;

namespace selection
{
void select(widget* target);
void select(std::initializer_list<widget*> targets);

widget* get_target();
const std::vector<widget*> get_targets();
}
}

#endif
