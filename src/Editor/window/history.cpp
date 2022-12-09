#include "Precompiled.h"
#include "editor/imgui_editor.h"
#include "editor/history.h"

extern ImVec2 g_unitSize;

namespace imgui_editor
{
    void draw_histroy(history* ctx)
    {
        if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unitSize.y * 25), true))
        {
            ImGui::Text("History");

            if(ImGui::BeginListBox("History"))
            {
                for(size_t i = 0; i < ctx->commands.size(); ++i)
                {
                    if(ImGui::Selectable(ctx->commands[i]->label.c_str(), i == ctx->index))
                    {
                        ctx->index = i;
                    }
                }

                ImGui::EndListBox();
            }
        }
        ImGui::EndChild();

        ImGui::Dummy(ImVec2(0.f, g_unitSize.y));
    }
}