#ifndef __WIDGET_EDITOR_H__
#define __WIDGET_EDITOR_H__

#include "editor/widget.h"

namespace imgui_editor
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
		widget* root = nullptr;
	};

	struct widget_inspector
	{
		widget_editor* editor = nullptr;
		std::string input;
	};

	struct widget_editor
	{
		widget* root;

		widget_tool tool;
		widget_hierarchy hirarchy;
		widget_inspector inspector;
	};

	void init_widget_editor(widget_editor* context, const char* init);

	void draw_widget_tool(widget_tool* context);
	void draw_widget_hierarchy(widget_hierarchy* context);
	void draw_widget_inspector(widget_inspector* context);

	void draw_widget_editor(widget_editor* context);
}

#endif
