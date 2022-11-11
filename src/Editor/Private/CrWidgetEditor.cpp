#include "Precompiled.h"
#include "Editor/CrWidgetEditor.h"
#include <algorithm>
#include "Editor/CrSelection.h"

extern ImVec2 g_windowSize;
extern ImVec2 g_unitSize;

void CrWidgetTool::OnGUI()
{
	if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unitSize.y * 10), true))
	{
		if (ImGui::BeginChild("Types", ImVec2(0.f, g_unitSize.y * 7)))
		{
//			magic_enum::enum_for_each<CrWidget::Type>([&](CrWidget::Type t)
//				{
//					const auto name = std::string(magic_enum::enum_name(t));
//					if (ImGui::Selectable(name.c_str(), t == _type))
//					{
//						_type = t;
//					}
//				});
			ImGui::EndChild();
		}

		const bool disable = nullptr == _root;
		ImGui::BeginDisabled(disable);
		if (ImGui::Button("Add Widget"))
		{
			auto selected = CrSelection::GetTargets();
			if (selected.size())
			{
				for(auto i : selected)
				{
					CrHistroy::Commit(new CrWidget::AttachChild(i, CrWidget::New(_type)));
				}
			}
			else
			{
				CrHistroy::Commit(new CrWidget::AttachChild(_root, CrWidget::New(_type)));
			}
		}
		ImGui::EndDisabled();
	}
	ImGui::EndChild();
}

void CrWidgetHirarchy::OnGUI()
{
	auto selected = CrSelection::GetTargets();
	std::function<void(CrWidget*)> drawNode = [&](CrWidget* widget) {

		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_None;

		if (std::any_of(selected.begin(), selected.end(), [&](CrWidget* w) { return w == widget;}))
		{
			flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (widget && ImGui::TreeNodeEx(widget->label.c_str(), flag))
		{
			const auto& children = widget->GetChildren();
			for(size_t i =0 , max = children.size(); i < max; ++i)
			{
				ImGui::PushID(i);
				drawNode(children[i]);
				ImGui::PopID();
			}
			ImGui::TreePop();
		}

		if(ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		{
			CrHistroy::Commit(new CrSelection::Select(widget));
		}
	};

	drawNode(_target);
}

void CrWidgetInspector::OnGUI()
{
	auto selected = CrSelection::GetTargets();
	ImGui::Text("Selected %d", selected.size());

	for(auto i : selected)
	{
		i->OnInspectorGUI();
	}
}

void CrWidgetEditor::Initialize()
{
	_tool.SetRoot(&_root);
	_hirarchy.SetTarget(&_root);
}

void CrWidgetEditor::Finalize()
{
}

void CrWidgetEditor::OnGUI()
{
	constexpr static ImGuiWindowFlags flag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar ;

	const ImVec2 toolSize{ g_unitSize.x * 50, g_windowSize.y };
	ImGui::SetNextWindowSize(toolSize);
	ImGui::SetNextWindowPos({ 0,0 });
	if (ImGui::Begin("tool", nullptr, flag))
	{
		static CR_STATE bool demo = false;
		ImGui::Checkbox("Demo", &demo);
		if (demo)
		{
			ImGui::ShowDemoWindow(&demo);
		}

		ImGui::BeginDisabled(!CrHistroy::CanUndo());
		if(ImGui::Button("Undo"))
		{
			CrHistroy::Undo();
		}
		ImGui::EndDisabled();

		ImGui::SameLine();

		ImGui::BeginDisabled(!CrHistroy::CanRedo());
		if(ImGui::Button("Redo"))
		{
			CrHistroy::Redo();
		}
		ImGui::EndDisabled();


		_tool.OnGUI();

		_hirarchy.OnGUI();
	}
	ImGui::End();

	const ImVec2 viewSize{ g_windowSize.x - toolSize.x * 2, g_windowSize.y };
	ImGui::SetNextWindowSize(viewSize);
	ImGui::SetNextWindowPos({ toolSize.x, 0 });
	if (ImGui::Begin("view", nullptr, flag))
	{
		_root.OnGUI();
		const ImVec2 pos = ImGui::GetCurrentWindow()->Pos;
		const ImVec2 cursor = pos + ImGui::GetCursorPos();
		const ImVec2 max = cursor + ImVec2(g_unitSize.x * 0.5f, g_unitSize.y);
		ImGui::GetWindowDrawList()->AddRectFilled(cursor, max, IM_COL32_WHITE);		
	}
	ImGui::End();
	
	ImGui::SetNextWindowSize(toolSize);
	ImGui::SetNextWindowPos({ g_windowSize.x - toolSize.x, 0 });
	if (ImGui::Begin("inspector", nullptr, flag))
	{
		_inspector.OnGUI();
	}
	ImGui::End();
}
