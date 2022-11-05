#include <Precompiled.h>
#include "Editor/CrWindow.h"

void CrWindow::OnGUI()
{
	const ImVec2 size = ImGui::GetIO().DisplaySize;
	constexpr static ImGuiWindowFlags flag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;

	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize(size);
	if (ImGui::Begin("window", nullptr, flag))
	{
		static CR_STATE bool demo = false;
		ImGui::Checkbox("Demo", &demo);
		if (demo)
		{
			ImGui::ShowDemoWindow(&demo);
		}
	}
	ImGui::End();
}
