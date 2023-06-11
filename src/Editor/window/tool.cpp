#include "Precompiled.h"

#include <magic_enum/magic_enum.hpp>

#include "editor/imgui_editor.h"
#include "editor/selection.h"
#include "editor/command.h"

namespace imgui_editor
{
    extern ImVec2 g_unitSize;
    static std::unordered_map<widget_type, std::string> s_category = 
    {
	    {widget_type::widget_type_begin_end_window, "Windows/BeginEndWindow"},
	    {widget_type::widget_type_begin_end_child, "Windows/BeginEndChild"},
	    {widget_type::widget_type_set_next_window_pos, "Window manipulation/SetNextWindowPos"},
	    {widget_type::widget_type_set_next_window_size, "Window manipulation/SetNextWindowSize"},
	    {widget_type::widget_type_set_next_window_content_size, "Window manipulation/SetNextWindowContentSize"},
	    {widget_type::widget_type_set_next_window_collapsed, "Window manipulation/SetNextWindowCollapsed"},
	    {widget_type::widget_type_set_next_window_focus, "Window manipulation/SetNextWindowFocus"},
	    {widget_type::widget_type_set_next_window_bg_alpha, "Window manipulation/SetNextWindowBgAlpha"},
	    {widget_type::widget_type_push_pop_item_width, "Parameters stacks (current window)/PushPopItemWidth"},
	    {widget_type::widget_type_push_pop_text_wrap_pos, "Parameters stacks (current window)/PushPopTextWrapPos"},
	    {widget_type::widget_type_separator, "Layout/Separator"},
	    {widget_type::widget_type_same_line, "Layout/SameLine"},
	    {widget_type::widget_type_spacing, "Layout/Spacing"},
	    {widget_type::widget_type_dummy, "Layout/Dummy"},
	    {widget_type::widget_type_indent, "Layout/Indent"},
	    {widget_type::widget_type_unindent, "Layout/Unindent"},
	    {widget_type::widget_type_begin_end_group, "Layout/BeginEndGroup"},
	    {widget_type::widget_type_set_cursor_pos, "Layout/SetCursorPos"},
	    {widget_type::widget_type_text, "Widgets/Text/Text"},
	    {widget_type::widget_type_text_colored, "Widgets/Text/TextColored"},
	    {widget_type::widget_type_label_text, "Widgets/Text/LabelText"},
	    {widget_type::widget_type_bullet_text, "Widgets/Text/BulletText"},
	    {widget_type::widget_type_button, "Widgets/Basic/Button"},
	    {widget_type::widget_type_small_button, "Widgets/Basic/SmallButton"},
	    {widget_type::widget_type_checkbox, "Widgets/Basic/Checkbox"},
	    {widget_type::widget_type_checkbox_flags, "Widgets/Basic/CheckboxFlags"},
	    {widget_type::widget_type_radio_button, "Widgets/Basic/RadioButton"},
	    {widget_type::widget_type_bullet, "Widgets/Basic/Bullet"},
	    {widget_type::widget_type_begin_end_combo, "Widgets/Combo Box/BeginEndCombo"},
	    {widget_type::widget_type_drag_float, "Widgets/Drag Sliders/DragFloat"},
	    {widget_type::widget_type_drag_float2, "Widgets/Drag Sliders/DragFloat2"},
	    {widget_type::widget_type_drag_float3, "Widgets/Drag Sliders/DragFloat3"},
	    {widget_type::widget_type_drag_float4, "Widgets/Drag Sliders/DragFloat4"},
	    {widget_type::widget_type_drag_int, "Widgets/Drag Sliders/DragInt"},
	    {widget_type::widget_type_drag_int2, "Widgets/Drag Sliders/DragInt2"},
	    {widget_type::widget_type_drag_int3, "Widgets/Drag Sliders/DragInt3"},
	    {widget_type::widget_type_drag_int4, "Widgets/Drag Sliders/DragInt4"},
	    {widget_type::widget_type_slider_float, "Widgets/Regular Sliders/SliderFloat"},
	    {widget_type::widget_type_slider_float2, "Widgets/Regular Sliders/SliderFloat2"},
	    {widget_type::widget_type_slider_float3, "Widgets/Regular Sliders/SliderFloat3"},
	    {widget_type::widget_type_slider_float4, "Widgets/Regular Sliders/SliderFloat4"},
	    {widget_type::widget_type_slider_angle, "Widgets/Regular Sliders/SliderAngle"},
	    {widget_type::widget_type_slider_int, "Widgets/Regular Sliders/SliderInt"},
	    {widget_type::widget_type_slider_int2, "Widgets/Regular Sliders/SliderInt2"},
	    {widget_type::widget_type_slider_int3, "Widgets/Regular Sliders/SliderInt3"},
	    {widget_type::widget_type_slider_int4, "Widgets/Regular Sliders/SliderInt4"},
	    {widget_type::widget_type_input_text, "Widgets/Input with Keyboard/InputText"},
	    {widget_type::widget_type_input_text_multiline, "Widgets/Input with Keyboard/InputTextMultiline"},
	    {widget_type::widget_type_input_text_with_hint, "Widgets/Input with Keyboard/InputTextWithHint"},
	    {widget_type::widget_type_input_float, "Widgets/Input with Keyboard/InputFloat"},
	    {widget_type::widget_type_input_float2, "Widgets/Input with Keyboard/InputFloat2"},
	    {widget_type::widget_type_input_float3, "Widgets/Input with Keyboard/InputFloat3"},
	    {widget_type::widget_type_input_float4, "Widgets/Input with Keyboard/InputFloat4"},
	    {widget_type::widget_type_input_int, "Widgets/Input with Keyboard/InputInt"},
	    {widget_type::widget_type_input_int2, "Widgets/Input with Keyboard/InputInt2"},
	    {widget_type::widget_type_input_int3, "Widgets/Input with Keyboard/InputInt3"},
	    {widget_type::widget_type_input_int4, "Widgets/Input with Keyboard/InputInt4"},
	    {widget_type::widget_type_input_double, "Widgets/Input with Keyboard/InputDouble"},
	    {widget_type::widget_type_color_edit3, "Widgets/Color/ColorEdit3"},
	    {widget_type::widget_type_color_edit4, "Widgets/Color/ColorEdit4"},
	    {widget_type::widget_type_color_picker3, "Widgets/Color/ColorPicker3"},
	    {widget_type::widget_type_color_picker4, "Widgets/Color/ColorPicker4"},
	    {widget_type::widget_type_color_button, "Widgets/Color/ColorButton"},
	    {widget_type::widget_type_push_pop_tree_node, "Widgets/Trees/PushPopTreeNode"},
	    {widget_type::widget_type_collapsing_header, "Widgets/Trees/CollapsingHeader"},
	    {widget_type::widget_type_selectable, "Widgets/Selectable"},
	    {widget_type::widget_type_begin_end_list_box, "Widgets/List Boxes/BeginEndListBox"},
	    {widget_type::widget_type_begin_end_menu_bar, "Widgets/Menus/BeginEndMenuBar"},
	    {widget_type::widget_type_begin_end_menu, "Widgets/Menus/BeginEndMenu"},
	    {widget_type::widget_type_menu_item, "Widgets/Menus/MenuItem"},
	    {widget_type::widget_type_begin_end_popup, "Popups, Modals/BeginEndPopup"},
	    {widget_type::widget_type_begin_end_table, "Tables/BeginEndTable"},
	    {widget_type::widget_type_table_next_row, "Tables/TableNextRow"},
	    {widget_type::widget_type_table_next_column, "Tables/TableNextColumn"},
	    {widget_type::widget_type_table_set_column_index, "Tables/TableSetColumnIndex"},
    };

    void draw_category_menu(const imgui_editor_context* ctx, const std::unordered_map<widget_type, std::string>& categoryMap)
    {
        for (const auto& pair : categoryMap)
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
						auto selects = selection::get_targets();
						if (0 < selects.size())
						{
							for (auto i : selects)
							{
								command::create_widget(i, ctx->create_widget_type);
							}
						}
						else
						{
							command::create_widget(ctx->root, ctx->create_widget_type);
						}
					}
					if (ImGui::BeginDragDropSource())
					{
						ImGui::Text("Create %s", get_pretty_name(t));
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
        if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unitSize.y * 20), true))
        {
            if (ImGui::BeginChild("Types"))
            {
                draw_category_menu(editor_context, s_category);

				ImGui::Separator();

				magic_enum::enum_for_each<widget_type>([&](widget_type t)
					{
						if (t == widget_type::widget_type_none) return;

						std::string name = get_pretty_name(t);

						const bool selected = t == editor_context->create_widget_type;
						if (ImGui::Selectable(name.c_str(), selected))
						{
							editor_context->create_widget_type = t;
						}

						if (ImGui::BeginDragDropSource())
						{
							ImGui::Text("Create %s", get_pretty_name(t));
							ImGui::SetDragDropPayload("create_widget", &t, sizeof(widget_type*));
							ImGui::EndDragDropSource();
						}

						if (selected)
						{
							// 현재 윈도우의 너비를 가져옴
							const float windowWidth = ImGui::GetWindowWidth();

							// 버튼을 오른쪽에 위치하여 출력
							ImGui::SetCursorPosX(windowWidth - g_unitSize.x * 75); // 버튼의 너비를 고려하여 위치 조정

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