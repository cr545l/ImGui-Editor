#ifndef __SELECTION_H__
#define __SELECTION_H__

namespace imgui_editor
{
	struct widget;
	struct selection_context
	{
		widget* target;
		std::vector<widget*> targets;
	};

	void init_selection(selection_context* ctx);

	namespace selection
	{
		void select(widget* target);
		void select(std::initializer_list<widget*> targets);

		widget* get_target();
		const std::vector<widget*> get_targets();
	}
}

#endif