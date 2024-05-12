#include "Precompiled.h"
#include "editor/imgui_editor.h"

#include <fstream>

#include <portable-file-dialogs/portable-file-dialogs.h>
#include <simpleini/SimpleIni.h>

#include "extension.h"
#include "editor/history.h"

namespace imgui_editor
{
	ImVec2 g_windowSize;
	ImVec2 g_unit_size;
	size_t g_widget_id = 0;
	static imgui_editor_context* s_instance = nullptr;

	imgui_editor_context* get_context()
	{
		return s_instance;
	}

	void initialize_editor(imgui_editor_context* ctx, const char* init)
	{
		g_widget_id = 0;

		s_instance = ctx;

		ctx->root = new_widget(widget_type::widget_type_begin_end_window);
		regist_widget(ctx->root);

		ctx->root->label = "root";

		if (0 != strcmp("", init))
		{
			widget_deserialize(ctx->root, init);
		}

		CSimpleIniA ini;
		ini.SetUnicode();
		SI_Error error = ini.LoadFile("imgui_editor.ini");
		if (error < 0)
		{
			error = ini.SaveFile("imgui_editor.ini");
			if (error < 0)
			{
				LOG("failed to save imgui_editor.ini");
			}
		}

		char *stop = nullptr;
		const char *count_string = ini.GetValue("last_open_paths", "count");
		const int count = count_string ? strtod(count_string, &stop) : 0;

		for (int i = 0; i < count; i++)
		{
			const char *path = ini.GetValue("last_open_paths", std::to_string(i).c_str());
			if (path)
			{
				ctx->last_open_paths.emplace_back(path);
			}
		}

		const char* current_language = ini.GetValue("common", "language");
		set_language(nullptr == current_language || 0 == strcmp("", current_language) ? "en" : current_language);
	}

	void draw_language_menu()
	{
		if (ImGui::BeginMenu(F("common.language")))
		{
			if (ImGui::Selectable(F("language.ko"), get_language() == "ko"))
			{
				set_language("ko");
			}

			if (ImGui::Selectable(F("language.en"), get_language() == "en"))
			{
				set_language("en");
			}

			ImGui::EndMenu();
		}
	}

	void draw_editor_context(imgui_editor_context *ctx, history *history)
	{
		auto &io = ImGui::GetIO();
		g_windowSize = io.DisplaySize;
		g_unit_size = ImGui::CalcTextSize(" ");

		const bool is_shortcut_key = io.ConfigMacOSXBehaviors ? (io.KeyMods & ImGuiModFlags_Super) : (io.KeyMods & ImGuiModFlags_Ctrl);
		const bool is_redo = ((is_shortcut_key && ImGui::IsKeyPressed(ImGuiKey_Y)) || (is_shortcut_key && io.KeyMods & ImGuiModFlags_Shift && ImGui::IsKeyPressed(ImGuiKey_Z))) && has_redo_command();
		const bool is_undo = !(io.KeyMods & ImGuiModFlags_Shift) && ((is_shortcut_key && ImGui::IsKeyPressed(ImGuiKey_Z)) && has_undo_command());

		if (is_redo)
			redo();
		else if (is_undo)
            undo();

        if (ImGui::IsMouseDragging(0) && ::ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            ImGui::ResetMouseDragDelta(0);
            ImGui::GetCurrentContext()->DragDropActive = false;
            ImGui::GetCurrentContext()->DragDropTargetId = 0;
            // ImGui::BeginDragDropTarget()
        }

        if (!ctx->project.ready)
        {
            // 프로젝트를 열기 전
            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu(F("common.file")))
                {
                    if (ImGui::MenuItem(F("common.new_project")))
                    {
                        ctx->project.ready = true;
                    }

                    if (ImGui::MenuItem(F("common.open")))
                    {
                        pfd::open_file open(F("common.open"));

                        const auto& result = open.result();
                        if (!result.empty())
                        {
                            std::string path = normalize_utf8(result[0]);
                            if (!open_project(ctx, path.c_str()))
                            {
                            }
                        }
                    }
                    ImGui::EndMenu();
                }

                draw_language_menu();

                ImGui::EndMainMenuBar();
            }

            draw_start_page(ctx);
        }
        else
        {
            // 프로젝트가 열린 후
            ImGuiID id = ImGui::GetID("Save?");
            if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu(F("common.file")))
				{
					if (ImGui::MenuItem(F("common.open")))
					{
						pfd::open_file open(F("common.open"));

						const auto &result = open.result();
						if (!result.empty())
						{
							std::string path = normalize_utf8(result[0]);
							open_project(ctx, path.c_str());
						}
					}

					if (ImGui::MenuItem(F("common.new_project")))
					{
						if (ctx->project.dirty && !ctx->project.absolutePath.empty())
						{
							ImGui::OpenPopup(id);
						}
						else
						{
							close_project(ctx);
							ctx->project.ready = true;
						}
					}

					bool canSave = ctx->project.dirty || ctx->project.absolutePath.empty();

					ImGui::BeginDisabled(!canSave);
					if (ImGui::MenuItem(F("common.save")))
					{
						if (ctx->project.absolutePath.empty())
						{
							pfd::save_file save(F("common.save"));

							ctx->project.absolutePath = save.result();
						}

						if (!ctx->project.absolutePath.empty())
						{
							std::ofstream ofs(ctx->project.absolutePath);
							ofs << widget_serialize(ctx->root);
							ctx->project.dirty = false;
						}
					}

					ImGui::EndDisabled();

					if (ImGui::MenuItem(F("common.save_as")))
					{
						pfd::save_file save(F("common.save"));
						const auto& result = save.result();
						if (!result.empty())
						{
							std::ofstream ofs(result);
							ofs << widget_serialize(ctx->root);
						}
					}

					if (ImGui::MenuItem(F("common.close_project")))
					{
						close_project(ctx);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu(F("common.edit")))
				{
					if (ImGui::MenuItem(F("common.undo"), nullptr, nullptr, has_undo_command()))
					{
						undo();
					}

					if (ImGui::MenuItem(F("common.redo"), nullptr, nullptr, has_redo_command()))
					{
						redo();
					}

                    ImGui::EndMenu();
                }

			    draw_language_menu();

				ImGui::EndMainMenuBar();
			}

			float mainMenuSizeY = ImGui::GetFrameHeight();
            constexpr static ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar;
            static ImVec2 toolSize{g_unit_size.x * 150, g_windowSize.y};
            ImGui::SetNextWindowSize(toolSize);
            ImGui::SetNextWindowPos({ 0, mainMenuSizeY });
            if (ImGui::Begin("left", nullptr, flag))
            {
                toolSize = ImGui::GetWindowSize();
                toolSize.y = g_windowSize.y - mainMenuSizeY;

                static CR_STATE bool demo = false;
                ImGui::Checkbox(F("common.demo"), &demo);
                if (demo)
                {
                    ImGui::ShowDemoWindow(&demo);
                }
                draw_tool(ctx);
            }
            ImGui::End();

            draw_widget(ctx->root);

            static ImVec2 inspectorSize{g_unit_size.x * 300, g_windowSize.y};
            ImGui::SetNextWindowSize(inspectorSize);
            ImGui::SetNextWindowPos({ g_windowSize.x - inspectorSize.x, mainMenuSizeY });
            if (ImGui::Begin("right", nullptr, flag))
            {
				if (ImGui::BeginTable("Begin End Table", 2, ImGuiTableFlags_Resizable))
				{
					if(ImGui::TableNextColumn())
					{
						draw_hierarchy(ctx);
					}
					if(ImGui::TableNextColumn())
					{
						draw_history(history);
						inspectorSize = ImGui::GetWindowSize();
						inspectorSize.y = g_windowSize.y - mainMenuSizeY;
						draw_inspector(ctx);
					}
					ImGui::EndTable();
				}
			}
			ImGui::End();

			if (ImGui::BeginPopupModal("Save?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text(F("common.save_changes"));
				ImGui::Separator();
				bool invoke = false;
				if (ImGui::Button(F("common.yes")))
				{
					invoke = true;
					std::ofstream ofs(ctx->project.absolutePath);
					ofs << widget_serialize(ctx->root);
					ctx->project.dirty = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button(F("common.no")))
				{
					invoke = true;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				bool cancel = false;
				if (ImGui::Button(F("common.cancel")))
				{
					invoke = true;
					cancel = true;
					ImGui::CloseCurrentPopup();
				}

				if (invoke && !cancel)
				{
					close_project(ctx);
					ctx->project.ready = true;
				}

				ImGui::EndPopup();
			}
		}
	}
}
