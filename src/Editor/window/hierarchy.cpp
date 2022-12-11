#include "Precompiled.h"

#include <algorithm>

#include "editor/selection.h"
#include "editor/imgui_editor.h"
#include "editor/widget.h"
#include "editor/command.h"

namespace imgui_editor
{
	static void draw_node(std::vector<widget*>& selected, widget* ctx)
	{
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;

		if (std::any_of(selected.begin(), selected.end(), [&](widget* w)
			{ return w == ctx; }))
		{
			flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (ctx)
		{
			bool remove = false;
			
			ImGui::PushID(ctx->id);
			bool showChildren = ImGui::TreeNodeEx(ctx->label.c_str(), flag, "%s (%s)", ctx->label.c_str(), get_pretty_name(ctx->type));

			if(ImGui::BeginDragDropSource( ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("widget", &ctx, sizeof(widget*));
				ImGui::Text(ctx->label.c_str());
				ImGui::EndDragDropSource();
			}

			if(ImGui::BeginDragDropTarget())
			{
				if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("widget"))
				{
					widget* source = *(widget**)payload->Data;
					if(source != ctx)
					{
						command::attach_child(ctx, source);
					}
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::PopID();
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				command::select(ctx);
			}
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::Text(ctx->label.c_str());
				ImGui::Separator();
				if (ImGui::MenuItem("Delete"))
				{
					remove = true;
				}
				ImGui::EndPopup();
			}

			if (remove)
			{
				command::remove_widget(ctx);
				
				if (showChildren)
				{
					ImGui::TreePop();
				}
			}
			else
			{
				if (showChildren)
				{
					const auto& children = ctx->children;
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