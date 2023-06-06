#include "Precompiled.h"
#include "editor/widget.h"
#include "editor/imgui_editor.h"
#include "editor/selection.h"

#include "editor/extension.h"

namespace imgui_editor
{
	extern ImVec2 g_unitSize;

	// ReSharper disable All
	struct ImGuiStyleVarInfo
	{
		ImGuiDataType   Type;
		ImU32           Count;
		ImU32           Offset;
		void* GetVarPtr(ImGuiStyle* style) const { return (void*)((unsigned char*)style + Offset); }
	};
	static const ImGuiStyleVarInfo GStyleVarInfo[] =
	{
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, Alpha) },               // ImGuiStyleVar_Alpha
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, DisabledAlpha) },       // ImGuiStyleVar_DisabledAlpha
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowPadding) },       // ImGuiStyleVar_WindowPadding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowRounding) },      // ImGuiStyleVar_WindowRounding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowBorderSize) },    // ImGuiStyleVar_WindowBorderSize
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowMinSize) },       // ImGuiStyleVar_WindowMinSize
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowTitleAlign) },    // ImGuiStyleVar_WindowTitleAlign
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ChildRounding) },       // ImGuiStyleVar_ChildRounding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ChildBorderSize) },     // ImGuiStyleVar_ChildBorderSize
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, PopupRounding) },       // ImGuiStyleVar_PopupRounding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, PopupBorderSize) },     // ImGuiStyleVar_PopupBorderSize
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, FramePadding) },        // ImGuiStyleVar_FramePadding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, FrameRounding) },       // ImGuiStyleVar_FrameRounding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, FrameBorderSize) },     // ImGuiStyleVar_FrameBorderSize
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, ItemSpacing) },         // ImGuiStyleVar_ItemSpacing
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, ItemInnerSpacing) },    // ImGuiStyleVar_ItemInnerSpacing
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, IndentSpacing) },       // ImGuiStyleVar_IndentSpacing
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, CellPadding) },         // ImGuiStyleVar_CellPadding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ScrollbarSize) },       // ImGuiStyleVar_ScrollbarSize
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ScrollbarRounding) },   // ImGuiStyleVar_ScrollbarRounding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, GrabMinSize) },         // ImGuiStyleVar_GrabMinSize
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, GrabRounding) },        // ImGuiStyleVar_GrabRounding
		{ ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, TabRounding) },         // ImGuiStyleVar_TabRounding
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, ButtonTextAlign) },     // ImGuiStyleVar_ButtonTextAlign
		{ ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, SelectableTextAlign) }, // ImGuiStyleVar_SelectableTextAlign
	};
	// ReSharper restore All

	void draw_inspector(widget_inspector* context)
	{
		auto selected = selection::get_targets();
		ImGui::Text("Selected %zu", selected.size());

		if (selected.empty()) return;

		ImGui::Separator();

		ImGui::Separator();

		for (size_t i = 0, max = selected.size(); i < max; ++i)
		{
			widget* ctx = selected[i];
			bool changed = false;

			if (ImGui::TreeNode("Gen c++"))
			{
				std::string s;
				widget_generate(generate_code::cpp, ctx, true, s);
				ImGui::InputTextMultiline("##data", &s, ImVec2(0, g_unitSize.y * 50), ImGuiInputTextFlags_ReadOnly);
				ImGui::TreePop();

				if (ImGui::Button("Copy"))
				{
					ImGui::SetClipboardText(s.c_str());
				}
			}

			if (ImGui::TreeNode("Output"))
			{
				std::string s = widget_serialize(ctx);
				ImGui::InputTextMultiline("##data", &s, ImVec2(0, g_unitSize.y * 2), ImGuiInputTextFlags_ReadOnly);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Input"))
			{
				ImGui::InputTextMultiline("##data", &context->input, ImVec2(0, g_unitSize.y * 2));
				if (ImGui::Button("Apply"))
				{
					widget_deserialize(ctx, context->input.c_str());
					changed = true;
				}
			
				ImGui::TreePop();
			}

			ImGui::BeginGroup();
			ImGui::Text("%s", get_pretty_name(ctx->type));

			ImGui::InputText("ID", &ctx->string_id);
			ImGui::SameLine();

			const std::string default_id = std::to_string(ctx->id);
			ImGui::BeginDisabled(default_id == ctx->string_id);
			if (ImGui::Button("Reset"))
			{
				ctx->string_id = default_id;
				changed = true;
			}
			ImGui::EndDisabled();			

			ImGui::InputText("label", &ctx->label);			

			draw_inspector_widget(ctx);

			ImGui::Separator();

			if (ImGui::TreeNodeEx("style_colors", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::Button("Add Default"))
				{
					for (size_t i = 0, max = static_cast<size_t>(ImGuiCol_COUNT); i < max; ++i)
					{
						ctx->style_colors.push_back({ static_cast<ImGuiCol_>(i), ImGui::GetStyle().Colors[i] });
					}
				}
				ImGui::SameLine();

				if (ImGui::Button("Light"))
				{
					ImGuiStyle style;
					ImGui::StyleColorsLight(&style);
					for (size_t i = 0, max = static_cast<size_t>(ImGuiCol_COUNT); i < max; ++i)
					{
						ctx->style_colors.push_back({ static_cast<ImGuiCol_>(i), style.Colors[i] });
					}
				}

				ImGui::SameLine();
				if (ImGui::Button("Dark"))
				{
					ImGuiStyle style;
					ImGui::StyleColorsDark(&style);
					for (size_t i = 0, max = static_cast<size_t>(ImGuiCol_COUNT); i < max; ++i)
					{
						ctx->style_colors.push_back({ static_cast<ImGuiCol_>(i), style.Colors[i] });
					}
				}

				ImGui::SameLine();
				if (ImGui::Button("Classic"))
				{
					ImGuiStyle style;
					ImGui::StyleColorsClassic(&style);
					for (size_t i = 0, max = static_cast<size_t>(ImGuiCol_COUNT); i < max; ++i)
					{
						ctx->style_colors.push_back({ static_cast<ImGuiCol_>(i), style.Colors[i] });
					}
				}

				int size = ctx->style_colors.size();
				if (ImGui::InputInt("size", (int*)&size))
				{
					if (size < 0)
					{
						size = 0;
					}

					if (static_cast<int>(ctx->style_colors.size()) < size)
					{
						ctx->style_colors.push_back({});
					}
					else
					{
						ctx->style_colors.resize(size);
					}
				}
				for (size_t i = 0, max = ctx->style_colors.size(); i < max; ++i)
				{
					ImGui::PushID(i);
					ImGui::Combo(string_format("%s[%u]", "idx", i).c_str(), &ctx->style_colors[i].idx, false);
					ImGui::ColorEdit4(string_format("%s[%u]", "col", i).c_str(), &ctx->style_colors[i].col.Value.x);
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("style_var_floats", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::Button("Add Default"))
				{
					for (size_t i = 0, max = static_cast<size_t>(ImGuiStyleVar_COUNT); i < max; ++i)
					{
						if (GStyleVarInfo[i].Count == 1)
						{
							float* value = static_cast<float*>(GStyleVarInfo[i].GetVarPtr(&ImGui::GetStyle()));
							ctx->style_var_floats.push_back({ static_cast<ImGuiStyleVar_>(i), *value });
						}
					}
				}
				int size = static_cast<int>(ctx->style_var_floats.size());
				if (ImGui::InputInt("size", (int*)&size))
				{
					if (size < 0)
					{
						size = 0;
					}

					if (static_cast<int>(ctx->style_var_floats.size()) < size)
					{
						ctx->style_var_floats.push_back({});
					}
					else
					{
						ctx->style_var_floats.resize(size);
					}
				}

				for (size_t i = 0, max = ctx->style_var_floats.size(); i < max; ++i)
				{
					ImGui::PushID(static_cast<int>(i));
					std::string preview = ImGui::GetEnumName(ctx->style_var_floats[i].idx, false);
					if (ImGui::BeginCombo(string_format("%s[%u]", "idx", i).c_str(), preview.c_str()))
					{
						for (int j = 0; j < ImGuiStyleVar_COUNT; ++j)
						{
							if (GStyleVarInfo[j].Count == 1)
							{
								if (ImGui::Selectable(ImGui::GetEnumName(static_cast<ImGuiStyleVar_>(j), false).c_str(), ctx->style_var_floats[i].idx == j))
								{
									ctx->style_var_floats[i].idx = static_cast<ImGuiStyleVar_>(j);
								}
							}
						}
						ImGui::EndCombo();
					}

					ImGui::DragFloat(string_format("%s[%u]", "val", i).c_str(), &ctx->style_var_floats[i].val);
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("style_var_vec2s", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::Button("Add Default"))
				{
					for (size_t i = 0, max = static_cast<size_t>(ImGuiStyleVar_COUNT); i < max; ++i)
					{
						if (GStyleVarInfo[i].Count == 2)
						{
							ImVec2* value = static_cast<ImVec2*>(GStyleVarInfo[i].GetVarPtr(&ImGui::GetStyle()));
							ctx->style_var_vec2s.push_back({ static_cast<ImGuiStyleVar_>(i), *value });
						}
					}
				}
				int size = ctx->style_var_vec2s.size();
				if (ImGui::InputInt("size", &size))
				{
					if (size < 0)
					{
						size = 0;
					}

					if (static_cast<int>(ctx->style_var_vec2s.size()) < size)
					{
						ctx->style_var_vec2s.push_back({});
					}
					else
					{
						ctx->style_var_vec2s.resize(size);
					}
				}
				for (size_t i = 0, max = ctx->style_var_vec2s.size(); i < max; ++i)
				{
					ImGui::PushID(i);
					std::string preview = ImGui::GetEnumName(ctx->style_var_vec2s[i].idx, false);
					if (ImGui::BeginCombo(string_format("%s[%u]", "idx", i).c_str(), preview.c_str()))
					{
						for (int j = 0; j < ImGuiStyleVar_COUNT; ++j)
						{
							if (GStyleVarInfo[j].Count == 2)
							{
								if (ImGui::Selectable(ImGui::GetEnumName(static_cast<ImGuiStyleVar_>(j), false).c_str(), ctx->style_var_vec2s[i].idx == j))
								{
									ctx->style_var_vec2s[i].idx = static_cast<ImGuiStyleVar_>(j);
								}
							}
						}
						ImGui::EndCombo();
					}
					ImGui::DragFloat2(string_format("%s[%u]", "val", i).c_str(), &ctx->style_var_vec2s[i].val.x);
					ImGui::PopID();
				}
				ImGui::TreePop();
			}
			
			ImGui::EndGroup();

			if (ImGui::IsItemActivated())
			{

			}

			if (ImGui::IsItemEdited() || changed)
			{

			}

			if (ImGui::IsItemDeactivatedAfterEdit())
			{

			}
		}

	}
}