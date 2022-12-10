#include "Precompiled.h"
#include "editor/widget.h"
#include "editor/imgui_editor.h"
#include "editor/selection.h"

namespace imgui_editor
{
	extern ImVec2 g_unitSize;

	void draw_inspector(widget_inspector* context)
	{
		auto selected = selection::get_targets();
		ImGui::Text("Selected %lu", selected.size());

		if(selected.size())
		{
			widget* ctx = selection::get_targets()[0];

			ImGui::Separator();
			
			if(ImGui::TreeNode("Gen c++"))
			{
				std::string s =  widget_generate(generate_code::cpp, ctx);
				ImGui::InputTextMultiline("##data", &s, ImVec2(0, g_unitSize.y*50), ImGuiInputTextFlags_ReadOnly);
				ImGui::TreePop();

                if(ImGui::Button("Copy"))
                {
                    ImGui::SetClipboardText(s.c_str());
                }
			}
			
			if(ImGui::TreeNode("Output"))
			{
				std::string s =  widget_serialize(ctx);
				ImGui::InputTextMultiline("##data", &s, ImVec2(0, g_unitSize.y*2), ImGuiInputTextFlags_ReadOnly);
				ImGui::TreePop();
			}

			if(ImGui::TreeNode("Input"))
			{
				ImGui::InputTextMultiline("##data", &context->input, ImVec2(0, g_unitSize.y*2));
				if(ImGui::Button("Apply"))
				{
					widget_deserialize(ctx, context->input.c_str());
				}

				ImGui::TreePop();
			}

			ImGui::Separator();
			
			for (auto i : selected)
			{
				draw_inspector_widget(i);
			}
		}
	}
}