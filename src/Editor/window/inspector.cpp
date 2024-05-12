#include "Precompiled.h"
#include "editor/widget.h"
#include "editor/imgui_editor.h"
#include "editor/selection.h"

#include "editor/extension.h"

namespace imgui_editor
{
	extern ImVec2 g_unit_size;

	// ReSharper disable All
	struct ImGuiStyleVarInfo
	{
		ImGuiDataType   Type;
		ImU32           Count;
		ImU32           Offset;
		void* GetVarPtr(ImGuiStyle* style) const { return (void*)((unsigned char*)style + Offset); }
	};

	// imgui.cpp:L3045
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

	void draw_inspector(imgui_editor_context* context)
	{
		auto selected = selection::get_targets();
		ImGui::Text(F("inspector.seleceted"), selected.size());

		if (selected.empty()) return;
		
		ImGui::Separator();

		for (size_t i = 0, maxi = selected.size(); i < maxi; ++i)
		{
			widget* ctx = selected[i];
			bool changed = false;

			if (ImGui::TreeNode(F("inspector.gen_cpp")))
			{
				std::string s;
				widget_generate(generate_code::cpp, ctx, true, s);
				ImGui::InputTextMultiline("##data", &s, ImVec2(0, g_unit_size.y * 50), ImGuiInputTextFlags_ReadOnly);
				ImGui::TreePop();

				if (ImGui::Button(F("inspector.copy")))
				{
					ImGui::SetClipboardText(s.c_str());
				}
			}

			if (ImGui::TreeNode(F("inspector.export_text")))
			{
				std::string s = widget_serialize(ctx);
				ImGui::InputTextMultiline("##data", &s, ImVec2(0, g_unit_size.y * 2), ImGuiInputTextFlags_ReadOnly);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode(F("inspector.import_text")))
			{
				ImGui::InputTextMultiline("##data", &context->import_text, ImVec2(0, g_unit_size.y * 2));
				if (ImGui::Button(F("common.apply")))
				{
					widget_deserialize(ctx, context->import_text.c_str());
					changed = true;
				}
			
				ImGui::TreePop();
			}

			ImGui::Separator();

			ImGui::BeginGroup();
			ImGui::Text("%s", get_widget_name(ctx->type));

			ImGui::InputText("ID", &ctx->string_id);
			ImGui::SameLine();

			const std::string default_id = std::to_string(ctx->id);
			ImGui::BeginDisabled(default_id == ctx->string_id);
			if (ImGui::Button(F("common.reset")))
			{
				ctx->string_id = default_id;
				changed = true;
			}
			ImGui::EndDisabled();			

			ImGui::InputText(F("inspector.label"), &ctx->label);			

			ImGui::Separator();

			ImGui::Text(F("inspector.parameters"));

			draw_inspector_widget(ctx);

			ImGui::Separator();

			// 스타일 설정
			ImGui::Text(F("inspector.style"));
			if (ImGui::BeginChild("##style", ImVec2(0, 0), true))
			{
				if (ImGui::TreeNodeEx(F("inspector.style_colors"), ImGuiTreeNodeFlags_DefaultOpen))
				{
					if (ImGui::Button(F("inspector.add_value")))
					{
						ImGui::OpenPopup("add_value_color");
					}
					if (ImGui::BeginPopup("add_value_color"))
					{
						if(ImGui::Selectable(F("inspector.add_defaults")))
						{
						    for (size_t j = 0, max = ImGuiCol_COUNT; j < max; ++j)
						    {
                                ctx->style_colors.push_back({ static_cast<ImGuiCol_>(j), ImGui::GetStyle().Colors[j] });
                            }
                        }
						ImGui::Separator();
                        for (size_t j = 0, max = ImGuiCol_COUNT; j < max; ++j)
                        {
                            if (ImGui::Selectable(ImGui::GetStyleColorName(j), false))
                            {
                                ctx->style_colors.push_back({ static_cast<ImGuiCol_>(j), ImGui::GetStyle().Colors[j] });
                            }
							if (ImGui::IsItemHovered())
							{
								ImGui::SetTooltip(get_col_description(static_cast<ImGuiCol_>(j)));
							}
                        }
                        ImGui::EndPopup();
					}
					ImGui::SameLine();

					ImGui::SameLine();

					ImGui::Text(F("inspector.select_theme"));
					
					ImGui::SameLine();
					if (ImGui::Button(F("inspector.light")))
					{
						ImGuiStyle style;
						ImGui::StyleColorsLight(&style);
						for (size_t i = 0, max = static_cast<size_t>(ImGuiCol_COUNT); i < max; ++i)
						{
							ctx->style_colors.push_back({ static_cast<ImGuiCol_>(i), style.Colors[i] });
						}
					}
					
					ImGui::SameLine();
					if (ImGui::Button(F("inspector.dark")))
					{
						ImGuiStyle style;
						ImGui::StyleColorsDark(&style);
						for (size_t i = 0, max = static_cast<size_t>(ImGuiCol_COUNT); i < max; ++i)
						{
							ctx->style_colors.push_back({ static_cast<ImGuiCol_>(i), style.Colors[i] });
						}
					}

					ImGui::SameLine();
					if (ImGui::Button(F("inspector.classic")))
					{
						ImGuiStyle style;
						ImGui::StyleColorsClassic(&style);
						for (size_t i = 0, max = static_cast<size_t>(ImGuiCol_COUNT); i < max; ++i)
						{
							ctx->style_colors.push_back({ static_cast<ImGuiCol_>(i), style.Colors[i] });
						}
					}

					int size = ctx->style_colors.size();
					if (ImGui::InputInt(F("inspector.size"), (int*)&size))
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
						ImGui::Text(get_col_description(static_cast<ImGuiCol_>(i)));
						ImGui::PopID();
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNodeEx(F("inspector.style_var_floats"), ImGuiTreeNodeFlags_DefaultOpen))
				{
					if (ImGui::Button(F("inspector.add_value")))
					{
						ImGui::OpenPopup("add_value_style");
					}

					if (ImGui::BeginPopup("add_value_style"))
					{
						if (ImGui::Selectable(F("inspector.add_defaults")))
						{
							for (size_t j = 0, max = ImGuiStyleVar_COUNT; j < max; ++j)
							{
								if (GStyleVarInfo[j].Count == 1)
								{
									float* value = static_cast<float*>(GStyleVarInfo[j].GetVarPtr(&ImGui::GetStyle()));
									ctx->style_var_floats.push_back({ static_cast<ImGuiStyleVar_>(j), *value });
								}
							}
						}
						ImGui::Separator();
						for (size_t j = 0, max = ImGuiStyleVar_COUNT; j < max; ++j)
						{
                            if (GStyleVarInfo[j].Count == 1)
                            {
                                std::string name = ImGui::GetEnumName(static_cast<ImGuiStyleVar_>(j), false);
                                if (ImGui::Selectable(name.c_str(), false))
                                {
                                    float* value = static_cast<float*>(GStyleVarInfo[j].GetVarPtr(&ImGui::GetStyle()));
                                    ctx->style_var_floats.push_back({ static_cast<ImGuiStyleVar_>(j), *value });
                                }
								if (ImGui::IsItemHovered())
								{
									ImGui::SetTooltip(get_style_var_description(static_cast<ImGuiStyleVar_>(j)));
								}
                            }
                        }
                        ImGui::EndPopup();
					}
					int size = static_cast<int>(ctx->style_var_floats.size());
					if (ImGui::InputInt(F("inspector.size"), (int*)&size))
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

					for (size_t j = 0, maxj = ctx->style_var_floats.size(); j < maxj; ++j)
					{
						ImGui::PushID(static_cast<int>(j));
						std::string preview = ImGui::GetEnumName(ctx->style_var_floats[j].idx, false);
						if (ImGui::BeginCombo(string_format("%s[%u]", "idx", j).c_str(), preview.c_str()))
						{
							for (int k = 0; k < ImGuiStyleVar_COUNT; ++k)
							{
								if (GStyleVarInfo[k].Count == 1)
								{
									if (ImGui::Selectable(ImGui::GetEnumName(static_cast<ImGuiStyleVar_>(k), false).c_str(), ctx->style_var_floats[j].idx == k))
									{
										ctx->style_var_floats[j].idx = static_cast<ImGuiStyleVar_>(k);
									}
								}
							}
							ImGui::EndCombo();
						}

						ImGui::DragFloat(string_format("%s[%u]", "val", j).c_str(), &ctx->style_var_floats[j].val);
						ImGui::Text(get_style_var_description(ctx->style_var_floats[j].idx));
						ImGui::PopID();
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNodeEx(F("inspector.style_var_vec2s"), ImGuiTreeNodeFlags_DefaultOpen))
				{
					if (ImGui::Button(F("inspector.add_value")))
					{
						ImGui::OpenPopup("add_value_var");
					}
					if (ImGui::BeginPopup("add_value_var"))
					{
						if (ImGui::Selectable(F("inspector.add_defaults")))
						{
							for (size_t j = 0, max = static_cast<size_t>(ImGuiStyleVar_COUNT); j < max; ++j)
							{
								if (GStyleVarInfo[j].Count == 2)
								{
									ImVec2* value = static_cast<ImVec2*>(GStyleVarInfo[j].GetVarPtr(&ImGui::GetStyle()));
									ctx->style_var_vec2s.push_back({ static_cast<ImGuiStyleVar_>(j), *value });
								}
							}
                        }
                        ImGui::Separator();
                        for (size_t j = 0, max = ImGuiStyleVar_COUNT; j < max; ++j)
                        {
                            if (GStyleVarInfo[j].Count == 2)
                            {
                                std::string name = ImGui::GetEnumName(static_cast<ImGuiStyleVar_>(j), false);
                                if (ImGui::Selectable(name.c_str(), false))
                                {
                                    ImVec2* value = static_cast<ImVec2*>(GStyleVarInfo[j].GetVarPtr(&ImGui::GetStyle()));
                                    ctx->style_var_vec2s.push_back({ static_cast<ImGuiStyleVar_>(j), *value });
                                }
								if (ImGui::IsItemHovered())
								{
									ImGui::SetTooltip(get_style_var_description(static_cast<ImGuiStyleVar_>(j)));
								}
                            }
                        }
                        ImGui::EndPopup();
                    }
                    int size = ctx->style_var_vec2s.size();
					if (ImGui::InputInt(F("inspector.size"), &size))
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
					for (size_t j = 0, maxj = ctx->style_var_vec2s.size(); j < maxj; ++j)
					{
						ImGui::PushID(j);
						std::string preview = ImGui::GetEnumName(ctx->style_var_vec2s[j].idx, false);
						if (ImGui::BeginCombo(string_format("%s[%u]", "idx", j).c_str(), preview.c_str()))
						{
							for (int k = 0; k < ImGuiStyleVar_COUNT; ++k)
							{
								if (GStyleVarInfo[k].Count == 2)
								{
									if (ImGui::Selectable(ImGui::GetEnumName(static_cast<ImGuiStyleVar_>(k), false).c_str(), ctx->style_var_vec2s[j].idx == k))
									{
										ctx->style_var_vec2s[j].idx = static_cast<ImGuiStyleVar_>(ImGuiConfigFlags_NavEnableKeyboard);
									}
								}
							}
							ImGui::EndCombo();
						}
						ImGui::DragFloat2(string_format("%s[%u]", "val", j).c_str(), &ctx->style_var_vec2s[j].val.x);
						ImGui::Text(get_style_var_description(ctx->style_var_vec2s[j].idx));
						ImGui::PopID();
					}
					ImGui::TreePop();
				}
			}
			ImGui::EndChild();
			ImGui::EndGroup();

			if (ImGui::IsItemActivated())
			{
				// before
			}

			if (ImGui::IsItemEdited() || changed)
			{
				context->project.dirty = true;
			}

			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				if (ImGui::IsItemActivated())
				{
					// next frame before
				}

				// before->after
			}
		}

	}
}