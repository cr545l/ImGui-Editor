#include "Precompiled.h"
#include "Editor/CrWindow.h"

ImVec2 CR_STATE g_windowSize;
ImVec2 CR_STATE g_unitSize;

CrWindow::CrWindow(HostData* hostData) :_hostData(hostData)
{
}

void CrWindow::OnGUI()
{
	g_windowSize = ImGui::GetIO().DisplaySize;
	g_unitSize = ImGui::CalcTextSize(" ");

	_editor.OnGUI();
}
