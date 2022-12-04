#include "Precompiled.h"

#include <algorithm>

#include "editor/selection.h"
#include "editor/widget_editor.h"
#include "editor/widget.h"

namespace imgui_editor
{

	void drawNode(std::vector<widget*>& selected, widget* current_widget)
	{
		ImGui::PushID(current_widget->label.c_str());
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick;

		if (std::any_of(selected.begin(), selected.end(), [&](widget* w)
			{ return w == current_widget; }))
		{
			flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (current_widget)
		{
			bool remove = false;
			bool showChildren = ImGui::TreeNodeEx(current_widget->label.c_str(), flag, "%s (%s)", current_widget->label.c_str(), get_pretty_name(current_widget->type));
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				selection::select(current_widget);
			}
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::Text(current_widget->label.c_str());
				ImGui::Separator();
				if (ImGui::MenuItem("Delete"))
				{
					remove = true;
				}
				ImGui::EndPopup();
			}

			if (remove)
			{
				remove_widget(current_widget);
			}
			else
			{
				if (showChildren)
				{
					const auto& children = current_widget->children;
					for (size_t i = 0, max = children.size(); i < max; ++i)
					{
						ImGui::PushID(i);
						drawNode(selected, children[i]);
						ImGui::PopID();
					}
					ImGui::TreePop();
				}
			}
		}
		ImGui::PopID();
	};


	void draw_widget_hierarchy(widget_hierarchy *context)
	{
		std::vector<widget*> selected = selection::get_targets();
		drawNode(selected, context->root);
	}
}