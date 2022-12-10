#include "Precompiled.h"

#include <algorithm>

#include "editor/selection.h"
#include "editor/imgui_editor.h"
#include "editor/widget.h"
#include "editor/command.h"

namespace imgui_editor
{
	static void draw_node(std::vector<widget*>& selected, widget* current_widget)
	{
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;

		if (std::any_of(selected.begin(), selected.end(), [&](widget* w)
			{ return w == current_widget; }))
		{
			flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (current_widget)
		{
			bool remove = false;
			
			ImGui::PushID(current_widget->id);
			bool showChildren = ImGui::TreeNodeEx(current_widget->label.c_str(), flag, "%s (%s)", current_widget->label.c_str(), get_pretty_name(current_widget->type));
			ImGui::PopID();
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				command::select(current_widget);
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
				command::remove_widget(current_widget);
				
				if (showChildren)
				{
					ImGui::TreePop();
				}
			}
			else
			{
				if (showChildren)
				{
					const auto& children = current_widget->children;
					for (size_t i = 0, max = children.size(); i < max; ++i)
					{
						draw_node(selected, children[i]);
					}
					ImGui::TreePop();
				}
			}
		}
	};


	void draw_hierarchy(widget_hierarchy *context)
	{
		std::vector<widget*> selected = selection::get_targets();
		draw_node(selected, context->root);
	}
}