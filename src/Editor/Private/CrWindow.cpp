#include <Precompiled.h>
#include "Editor/CrWindow.h"

void CrWindow::OnGUI()
{
    if(ImGui::Begin("window"))
    {
        ImGui::Button("test");
    }
    ImGui::End();
}
