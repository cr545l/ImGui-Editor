#include "Precompiled.h"
#include "editor/imgui_editor.h"

#include <fstream>

#include <magic_enum/magic_enum.hpp>
#include <portable-file-dialogs/portable-file-dialogs.h>
#include <simpleini/SimpleIni.h>

#include "extension.h"
#include "editor/selection.h"
#include "editor/history.h"

namespace imgui_editor
{
	ImVec2 g_windowSize;
	ImVec2 g_unitSize;
	size_t g_widget_id = 0;
	static imgui_editor_context* s_instance;

	imgui_editor_context* get_context()
	{
		return s_instance;
	}

	void initialize_editor(imgui_editor_context* ctx, const char* init)
	{
		g_widget_id = 0;

		s_instance = ctx;

		ctx->root = new_widget(widget_type::widget_type_begin_end_window);
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
	}


	void draw_editor_context(imgui_editor_context *ctx, history *history)
	{
		auto &io = ImGui::GetIO();
		g_windowSize = io.DisplaySize;
		g_unitSize = ImGui::CalcTextSize(" ");

		const bool is_shortcut_key = io.ConfigMacOSXBehaviors ? (io.KeyMods & ImGuiModFlags_Super) : (io.KeyMods & ImGuiModFlags_Ctrl);
		const bool is_redo = ((is_shortcut_key && ImGui::IsKeyPressed(ImGuiKey_Y)) || (is_shortcut_key && io.KeyMods & ImGuiModFlags_Shift && ImGui::IsKeyPressed(ImGuiKey_Z))) && has_redo_command();
		const bool is_undo = !(io.KeyMods & ImGuiModFlags_Shift) && ((is_shortcut_key && ImGui::IsKeyPressed(ImGuiKey_Z)) && has_undo_command());

		if (is_redo)
			redo();
		else if (is_undo)
			undo();

		if (ctx->project.ready)
		{
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open"))
					{
						pfd::open_file open("Open");

						const auto &result = open.result();
						if (!result.empty())
						{
							std::string path = normalize_utf8(result[0]);
							open_project(ctx, path.c_str());
						}
					}

					ImGui::BeginDisabled(!ctx->project.dirty);
					if (ImGui::MenuItem("Save"))
					{
						std::ofstream ofs(ctx->project.absolutePath);
						ofs << widget_serialize(ctx->root);
						ctx->project.dirty = false;
					}

					ImGui::EndDisabled();

					if (ImGui::MenuItem("Save As"))
					{
						pfd::save_file save("Save");
						const auto& result = save.result();
						if (!result.empty())
						{
							std::ofstream ofs(result);
							ofs << widget_serialize(ctx->root);
						}
					}

					if (ImGui::MenuItem("Close Project"))
					{
						close_project(ctx);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Edit"))
				{
					if (ImGui::MenuItem("Undo", nullptr, nullptr, has_undo_command()))
					{
						undo();
					}

					if (ImGui::MenuItem("Redo", nullptr, nullptr, has_redo_command()))
					{
						redo();
					}

					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

			float mainMenuSizeY = ImGui::GetFrameHeight();
			constexpr static ImGuiWindowFlags flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar;
			static ImVec2 toolSize{g_unitSize.x * 50, g_windowSize.y};
			ImGui::SetNextWindowSize(toolSize);
			ImGui::SetNextWindowPos({0, mainMenuSizeY});
			if (ImGui::Begin("tool", nullptr, flag))
			{
				toolSize = ImGui::GetWindowSize();
				toolSize.y = g_windowSize.y - mainMenuSizeY;

				static CR_STATE bool demo = false;
				ImGui::Checkbox("Demo", &demo);
				if (demo)
				{
					ImGui::ShowDemoWindow(&demo);
				}
				draw_tool(ctx);
				draw_hierarchy(ctx);
			}
			ImGui::End();

			draw_widget(ctx->root);

			static ImVec2 inspectorSize{g_unitSize.x * 50, g_windowSize.y};
			ImGui::SetNextWindowSize(inspectorSize);
			ImGui::SetNextWindowPos({g_windowSize.x - inspectorSize.x, mainMenuSizeY});
			if (ImGui::Begin("inspector", nullptr, flag))
			{
				draw_history(history);

				inspectorSize = ImGui::GetWindowSize();
				inspectorSize.y = g_windowSize.y - mainMenuSizeY;
				draw_inspector(ctx);
			}
			ImGui::End();
		}
		else
		{
			// 프로젝트를 열기 전
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open"))
					{
						pfd::open_file open("Open");

						const auto& result = open.result();
						if (result.size())
						{
							std::string path = normalize_utf8(result[0]);
							if (!open_project(ctx, path.c_str()))
							{
							}
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

			draw_start_page(ctx);
		}
	}
}
