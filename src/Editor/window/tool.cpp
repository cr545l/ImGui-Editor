#include "Precompiled.h"

#include <magic_enum/magic_enum.hpp>
#include <simpleini/SimpleIni.h>

#include "editor/imgui_editor.h"
#include "editor/selection.h"
#include "editor/command.h"

namespace imgui_editor
{
    extern ImVec2 g_unit_size;

	static std::string s_current_language_key;
	static std::unordered_map<widget_type, std::string> category_map;

	void update_category_map()
	{
		if(s_current_language_key == get_language()) return;
		s_current_language_key = get_language();

		const std::string path = "lang/" + s_current_language_key + ".ini";
		CSimpleIniA ini;
		ini.SetUnicode();
		SI_Error error = ini.LoadFile(path.c_str());
		if (error < 0)
		{
			error = ini.SaveFile("imgui_editor.ini");
			if (error < 0)
			{
				LOG("failed to save imgui_editor.ini");
				return;
			}
		}

		category_map.clear();
		magic_enum::enum_for_each<widget_type>([&](widget_type t)
			{
				const std::string name(magic_enum::enum_name(t));
				const char* category = ini.GetValue("widget_category", name.c_str());
				if (category)
				{
					category_map[t] = category;
					category_map[t].append("/");
					category_map[t].append(get_widget_name(t));
				}
			});
	}


	void draw_category_menu(const imgui_editor_context* ctx)
	{
		update_category_map();

		const std::string path = "lang/" + get_language() + ".ini";
        for (const auto& pair : category_map)
        {
            // 카테고리 문자열을 '/'로 구분하여 토큰으로 분리
            std::vector<std::string> tokens;
            std::string category = pair.second;
            size_t startPos = 0;
            size_t delimiterPos = category.find('/');
            while (delimiterPos != std::string::npos)
            {
                tokens.push_back(category.substr(startPos, delimiterPos - startPos));
                startPos = delimiterPos + 1;
                delimiterPos = category.find('/', startPos);
            }
            tokens.push_back(category.substr(startPos));

            // 메뉴 아이템의 깊이에 맞게 ImGui::BeginMenu와 ImGui::MenuItem 호출
            int depth = 0;
            for (const auto& token : tokens)
            {
                if (depth < tokens.size() - 1)
                {
                    if (ImGui::BeginMenu(token.c_str()))
                    {
                        depth++;
                    }
                    else
                    {
                        break;
                    }
                }
				else
				{
					widget_type t = pair.first;
					if (ImGui::Selectable(token.c_str()))
					{
						const std::vector<widget*>& selects = selection::get_targets();
						if (!selects.empty())
						{
							for (const auto& i : selects)
							{
								command::create_widget(i, ctx->create_widget_type);
							}
						}
						else
						{
							command::create_widget(ctx->root, ctx->create_widget_type);
						}
					}
					if (ImGui::IsItemHovered())
					{
						ImGui::SetTooltip(get_widget_description(t));
					}

					if (ImGui::BeginDragDropSource())
					{
						ImGui::Text("Create %s", get_widget_name(t));
						ImGui::SetDragDropPayload("create_widget", &t, sizeof(widget_type*));
						ImGui::EndDragDropSource();
					}
				}
			}

			// 메뉴 아이템의 깊이에 맞게 ImGui::EndMenu 호출
			for (int i = 0; i < depth; ++i)
			{
				ImGui::EndMenu();
			}
        }
    }

    void draw_tool(imgui_editor_context* editor_context)
    {
        if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unit_size.y * 20), true))
        {
            if (ImGui::BeginChild("Types"))
            {
                draw_category_menu(editor_context);

				ImGui::Separator();

				magic_enum::enum_for_each<widget_type>([&](widget_type t)
					{
						if (t == widget_type::widget_type_none) return;

						std::string name = get_widget_name(t);

						const bool selected = t == editor_context->create_widget_type;
						if (ImGui::Selectable(name.c_str(), selected))
						{
							editor_context->create_widget_type = t;
						}

						if (ImGui::IsItemHovered())
						{
							ImGui::SetTooltip(get_widget_description(t));
						}

						if (ImGui::BeginDragDropSource())
						{
							ImGui::Text("Create %s", get_widget_name(t));
							ImGui::SetDragDropPayload("create_widget", &t, sizeof(widget_type*));
							ImGui::EndDragDropSource();
						}

						if (selected)
						{
							// 현재 윈도우의 너비를 가져옴
							const float windowWidth = ImGui::GetWindowWidth();

							// 버튼을 오른쪽에 위치하여 출력
							ImGui::SetCursorPosX(windowWidth - g_unit_size.x * 75); // 버튼의 너비를 고려하여 위치 조정

							ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
							ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));

							const auto selects = selection::get_targets();
							const bool selected = !selects.empty();
							const bool disabled = !selected || selected && nullptr == selects[0]->parent;

							ImGui::BeginDisabled(disabled);
							if (ImGui::Button("Insert front"))
							{
								auto target = selects[0];
								auto parent = target->parent;
								auto it = std::find(parent->children.begin(), parent->children.end(), target);
								if (it != parent->children.end())
								{
									auto index = std::distance(parent->children.begin(), it);
									command::create_widget(parent, editor_context->create_widget_type, index);
								}
							}
							ImGui::SameLine();
							if (ImGui::Button("Insert back"))
							{
								auto target = selects[0];
								auto parent = target->parent;
								auto it = std::find(parent->children.begin(), parent->children.end(), target);
								if (it != parent->children.end())
								{
									auto index = std::distance(parent->children.begin(), it);
									command::create_widget(parent, editor_context->create_widget_type, index + 1);
								}
							}
							ImGui::EndDisabled();

							ImGui::SameLine();
							if (ImGui::Button("Add Child"))
							{
								if (selected)
								{
									for (auto i : selects)
									{
										command::create_widget(i, editor_context->create_widget_type);
									}
								}
								else
								{
									command::create_widget(editor_context->root, editor_context->create_widget_type);
								}
							}

							ImGui::PopStyleVar(2);
						}
					});
            }
            ImGui::EndChild();
        }
        ImGui::EndChild();
    }
}