#include "Precompiled.h"

#include <algorithm>

#include "editor/selection.h"
#include "editor/imgui_editor.h"
#include "editor/widget.h"
#include "editor/command.h"

namespace imgui_editor
{
	static bool draw_node(std::vector<widget*>& selected, widget* ctx, std::vector<widget*>& outRemove)
	{
		bool remove = false;
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;

		if (std::ranges::any_of(selected, [&](const widget* w)
		                        { return w == ctx; }))
		{
			flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (ctx)
		{			
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
					widget* source = static_cast<widget*>(payload->Data);
					if(source != ctx)
					{
						command::attach_child(ctx, source);
					}
				}

				if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("create_widget"))
				{
					const widget_type* type = static_cast<widget_type*>(payload->Data);
					command::create_widget(ctx, *type);
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
					outRemove.emplace_back(ctx);
				}
				ImGui::EndPopup();
			}
			if (showChildren)
			{
				const auto& children = ctx->children;
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


	void draw_hierarchy(imgui_editor_context* context)
	{
		std::vector<widget*> selected = selection::get_targets();

		std::vector<widget*> remove;

		if (draw_node(selected, context->root, remove))
		{
			for (size_t i = 0, max = remove.size(); i < max; ++i)
			{
				command::remove_widget(remove[i]);
			}
		}
	}
}