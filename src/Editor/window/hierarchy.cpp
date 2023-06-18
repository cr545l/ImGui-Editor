#include "Precompiled.h"

#include <algorithm>

#include "editor/selection.h"
#include "editor/imgui_editor.h"
#include "editor/widget.h"
#include "editor/command.h"
#include "editor/widget/args_data.h"

namespace imgui_editor
{
	struct widget_menu_item;

	static bool draw_node(std::vector<widget*>& selected, widget* widget_context, std::vector<widget*>& outRemove)
	{
		bool remove = false;
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;

		if (std::ranges::any_of(selected, [&](const widget* w)
		                        { return w == widget_context; }))
		{
			flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (widget_context)
		{			
			ImGui::PushID(static_cast<int>(widget_context->id));
			const bool is_show_children = ImGui::TreeNodeEx(widget_context->label.c_str(), flag, "%s (%s)", widget_context->label.c_str(), get_widget_name(widget_context->type));

			if(ImGui::BeginDragDropSource( ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("widget", &widget_context, sizeof(widget*));
				ImGui::TextUnformatted(widget_context->label.c_str());
				ImGui::EndDragDropSource();
			}

			if(ImGui::BeginDragDropTarget())
			{
				if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("widget"))
				{
					widget* source = static_cast<widget*>(payload->Data);
					if(source != widget_context)
					{
						command::attach_child(widget_context, source);
					}
				}

				if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("create_widget"))
				{
					const widget_type* type = static_cast<widget_type*>(payload->Data);
					command::create_widget(widget_context, *type);
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::PopID();
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				command::select(widget_context);
			}
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::TextUnformatted(widget_context->label.c_str());
				ImGui::Separator();


				if (ImGui::MenuItem("Delete"))
				{
					remove = true;
					outRemove.emplace_back(widget_context);
				}
				ImGui::EndPopup();
			}

			if (is_show_children)
			{
				const auto& children = widget_context->children;
				const size_t max = children.size();
				for (size_t i = 0; i < max; ++i)
				{
					remove |= draw_node(selected, children[i], outRemove);
				}
				ImGui::TreePop();
			}
		}
		return remove;
	};


	void draw_hierarchy(const imgui_editor_context* editor_context)
	{
		if (ImGui::BeginChild("hierarchy", ImVec2(0.f, 0.f), true))
		{
			std::vector<widget*> selected = selection::get_targets();
			std::vector<widget*> remove;

			if (draw_node(selected, editor_context->root, remove))
			{
				selected.erase(std::ranges::remove_if(selected, [&](const widget* elem)
					{
						return std::find(remove.begin(), remove.end(), elem) != remove.end();
					}).begin(), selected.end());

				command::select(selected);

				for (size_t i = 0, max = remove.size(); i < max; ++i)
				{
					command::remove_widget(remove[i]);
				}
			}

			if (ImGui::IsKeyPressed(ImGuiKey_Delete))
			{
				selection::clear();
				for (size_t i = 0, max = selected.size(); i < max; ++i)
				{
					command::remove_widget(selected[i]);
				}
			}
		}
		ImGui::EndChild();
	}
}
