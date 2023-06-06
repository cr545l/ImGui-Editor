#include "Precompiled.h"

#include <magic_enum/magic_enum.hpp>

#include "editor/imgui_editor.h"
#include "editor/selection.h"
#include "editor/command.h"

namespace imgui_editor
{
    extern ImVec2 g_unitSize;

    void draw_tool(imgui_editor_context* ctx)
    {
        if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unitSize.y * 25), true))
        {
            if (ImGui::BeginChild("Types", ImVec2(0.f, g_unitSize.y * 20)))
            {  
				magic_enum::enum_for_each<widget_type>([&](widget_type t)
					{
                        if(t == widget_type::widget_type_none) return;

                        std::string name = get_pretty_name(t);
						if (ImGui::Selectable(name.c_str(), t == ctx->create_widget_type))
						{
							ctx->create_widget_type = t;
						}
					});
            }
            ImGui::EndChild();

            ImGui::Separator();
            const bool disable = nullptr == ctx->root;
            ImGui::BeginDisabled(disable);
			
            auto selects = selection::get_targets();
            const bool selected = 0 < selects.size();
            const bool disabled= !selected || selected&& nullptr==selects[0]->parent;

            ImGui::BeginDisabled(disabled);
            if (ImGui::Button("Insert front"))
            {
                auto target = selects[0];
                auto parent = target->parent;
                auto it = std::find(parent->children.begin(), parent->children.end(), target);
                if (it != parent->children.end())
                {
                    auto index = std::distance(parent->children.begin(), it);
                    command::create_widget(parent, ctx->create_widget_type, index);
                }
            }
            ImGui::SameLine();
            if(ImGui::Button("Insert back"))
            {
                auto target = selects[0];
                auto parent = target->parent;
                auto it = std::find(parent->children.begin(), parent->children.end(), target);
                if (it != parent->children.end())
                {
                    auto index = std::distance(parent->children.begin(), it);
                    command::create_widget(parent, ctx->create_widget_type, index+1);
                }
            }
            ImGui::EndDisabled();

            ImGui::SameLine();
            if (ImGui::Button("Add Child"))
            {
                if (selected)
                {
                    for (auto i : selects)
                    {
                        command::create_widget(i, ctx->create_widget_type);
                    }
                }
                else
                {
                    command::create_widget(ctx->root, ctx->create_widget_type);
                }
            }
            ImGui::EndDisabled();
        }
        ImGui::EndChild();
    }
}