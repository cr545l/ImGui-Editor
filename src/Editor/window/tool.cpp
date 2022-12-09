#include "Precompiled.h"

#include <magic_enum/magic_enum.hpp>

#include "editor/widget_editor.h"
#include "editor/selection.h"
#include "editor/command.h"

extern ImVec2 g_unitSize;

namespace imgui_editor
{
    void draw_widget_tool(widget_tool *ctx)
    {
        if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unitSize.y * 25), true))
        {
            if (ImGui::BeginChild("Types", ImVec2(0.f, g_unitSize.y * 20)))
            {  
				magic_enum::enum_for_each<widget_type>([&](widget_type t)
					{
                        if(t == widget_type::widget_type_none) return;

                        std::string name = get_pretty_name(t);
						if (ImGui::Selectable(name.c_str(), t == ctx->type))
						{
							ctx->type = t;
						}
					});
            }
            ImGui::EndChild();

            ImGui::Separator();
            const bool disable = nullptr == ctx->root;
            ImGui::BeginDisabled(disable);
            if (ImGui::Button("Add Widget"))
            {
                auto selected = selection::get_targets();
                if (selected.size())
                {
                    for (auto i : selected)
                    {
                        command::create_widget(i, ctx->type);
                    }
                }
                else
                {
                    command::create_widget(ctx->root, ctx->type);
                }
            }
            ImGui::EndDisabled();
        }
        ImGui::EndChild();
    }
}