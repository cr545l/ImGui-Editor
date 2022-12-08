#include "Precompiled.h"

#include "editor/widget.h"


extern size_t g_widget_id;

namespace imgui_editor
{
	// TODO
	// widget_args_required w[(size_t)widget_type::count];
	// widget_args_required& get_widget_args_required(widget_type type)
	// {
	// 	return w[(size_t)type];
	// }

	widget* new_widget(widget_type type)
	{
		auto w = new widget();
		w->type = type;
		w->args = new_widget_arg(type);
		w->id = g_widget_id++;
		return w;
	}

	void delete_widget(widget* target)
	{
		delete_widget_args(target->type, target->args);
		target->args = nullptr;

		for(size_t i = 0, max = target->children.size(); i < max; ++i)
		{
			delete_widget(target->children[i]);
		}
		target->children.clear();
	}

}
