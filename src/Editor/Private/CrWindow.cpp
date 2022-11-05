#include <Precompiled.h>
#include "Editor/CrWindow.h"

void CrWindow::OnGUI()
{
    auto size = ImGui::GetIO().DisplaySize;
    const static ImGuiWindowFlags flag =
    ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar;
    
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize(size);
    if(ImGui::Begin("window", nullptr, flag))
    {
        static bool demo = false;
        ImGui::Checkbox("Demo", &demo);
        if(demo)
        {
            ImGui::ShowDemoWindow(&demo);
        }
        
        
        ImGui::Button("tes2t2");
        
        if(ImGui::BeginChild("Preview"))
        {
            ImGui::Button("tes2t2");
            
        }
        ImGui::EndChild();
    }
    ImGui::End();
}
