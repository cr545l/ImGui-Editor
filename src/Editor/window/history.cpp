#include "Precompiled.h"
#include "editor/imgui_editor.h"
#include "editor/history.h"

BEGIN_NS_IMGUI_EDITOR

extern ImVec2 g_unit_size;

static size_t last_index = 0;
void draw_history(history* ctx)
{
    static bool auto_scroll = true;

    const bool changed = last_index != ctx->index;
    last_index = ctx->index;
    ImGui::Checkbox("Auto-scroll", &auto_scroll);
    if (ImGui::BeginListBox("History"))
    {
        for (size_t i = 0; i < ctx->commands.size(); ++i)
        {
            const bool is_selected = i == ctx->index;

            if (ImGui::Selectable(ctx->commands[i]->label.c_str(), is_selected, ImGuiSelectableFlags_SelectOnNav))
            {
                ctx->index = i;
            }
            if (auto_scroll && is_selected && changed && 0 < ImGui::GetScrollMaxY())
            {
                ImGui::SetScrollHereY(ImGui::GetScrollY() / ImGui::GetScrollMaxY());
            }
        }
        ImGui::EndListBox();
    }
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.f, g_unit_size.y));
}

END_NS_IMGUI_EDITOR