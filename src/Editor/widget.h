#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "Editor/widget_type.h"

namespace imgui_editor
{
	struct widget
	{
		std::string label = "empty";
		std::vector<widget*> children;

		ImVec2 size;

		widget_type type = widget_type::widget_type_none;
		void* args = nullptr;
		void(*draw)(widget*) = nullptr;
		void(*draw_inspector)(widget*) = nullptr;
	};

	void draw_widget(widget* context);
	void draw_inspector_widget(widget* context);

	widget* new_widget(widget_type type);
	void delete_widget(widget* target);

	void attach_child(widget* parent, widget* child);
}

#endif
