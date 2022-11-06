#include "Precompiled.h"
#include "Editor/CrWidget.h"
#include "Editor/CrSelection.h"

using namespace Widget;

CrWidget* CrWidget::New(const Type type)
{
	switch (type)
	{
	case Type::Window:
		return new Window();
	case Type::Button:
		return new Button();
	case Type::Checkbox:
		return new Checkbox();
	case Type::RadioButton:
		return new RadioButton();
	}
}

CrWidget::CrWidget()
{
}

CrWidget::~CrWidget()
{
}

void CrWidget::OnGUI()
{
	drawChildren();
}

void CrWidget::OnInspectorGUI()
{
	std::string temp;
	temp.reserve(label.capacity() * 2);
	temp = label;
	if (ImGui::InputText("label", const_cast<char*>(temp.c_str()), temp.capacity(), label.capacity()))
	{
		if(label.capacity() < temp.length())
		{
			label.reserve(temp.capacity());
		}
		label = temp.c_str();
	}
}

void CrWidget::drawChildren()
{
	for(size_t i =0, max = _children.size(); i < max;++i)
	{
		ImGui::PushID(i);
		_children[i]->OnGUI();
		ImGui::PopID();
	}
}

void Window::OnGUI()
{
	ImVec2 min = { 0.f,0.f }, max = { 0.f,0.f };
	if (ImGui::Begin(label.c_str()))
	{
		drawChildren();
		ImGui::End();
	}

	min = ImGui::GetItemRectMin();
	max = ImGui::GetItemRectMax();
	ImGui::GetWindowDrawList()->AddRect(min, max, IM_COL32(0, 255, 0, 255));
}

void Button::OnGUI()
{	
	ImGui::Button(label.c_str());
	if(ImGui::IsItemClicked(ImGuiMouseButton_Left))
	{
		CrHistroy::Commit(new CrSelection::Select(this));
	}
	drawChildren();
}

void Checkbox::OnGUI()
{
	ImGui::Checkbox(label.c_str(), value->GetValue<bool>());
	if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
	{
		CrHistroy::Commit(new CrSelection::Select(this));
	}
	drawChildren();
}

void RadioButton::OnGUI()
{
	ImGui::RadioButton(label.c_str(), *value->GetValue<bool>());
	if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
	{
		CrHistroy::Commit(new CrSelection::Select(this));
	}
	drawChildren();
}
