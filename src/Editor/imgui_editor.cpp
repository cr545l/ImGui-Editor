#include "Precompiled.h"
#include "editor/imgui_editor.h"

#include <fstream>

#include <magic_enum/magic_enum.hpp>
#include <portable-file-dialogs/portable-file-dialogs.h>
#include <simpleini/SimpleIni.h>

#include "editor/selection.h"
#include "editor/history.h"

namespace imgui_editor
{
	ImVec2 g_windowSize;
	ImVec2 g_unitSize;
	size_t g_widget_id = 0;

	void initialize(widget_editor *ctx, const char *init)
	{
		g_widget_id = 0;
		ctx->root = new_widget(widget_type::widget_type_begin_end_window);
		ctx->root->label = "root";

		// debug_break();
		if (0 != strcmp("", init))
		{
			widget_deserialize(ctx->root, init);
		}

		ctx->tool.editor = ctx;
		ctx->tool.root = ctx->root;

		ctx->hirarchy.editor = ctx;
		ctx->hirarchy.root = ctx->root;
		ctx->inspector.editor = ctx;

		CSimpleIniA ini;
		ini.SetUnicode();
		SI_Error rc = ini.LoadFile("imgui_editor.ini");
		if (rc < 0)
		{
			rc = ini.SaveFile("imgui_editor.ini");
			if (rc < 0)
			{
				printf("failed to save imgui_editor.ini");
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
				ctx->last_open_paths.push_back(path);
			}
		}
	}


	void draw(widget_editor *ctx, history *history)
	{
		auto &io = ImGui::GetIO();
		g_windowSize = io.DisplaySize;
		g_unitSize = ImGui::CalcTextSize(" ");

		const bool is_shortcut_key = io.ConfigMacOSXBehaviors ? (io.KeyMods == ImGuiModFlags_Super) : (io.KeyMods == ImGuiModFlags_Ctrl);
		const bool is_undo = ((is_shortcut_key && ImGui::IsKeyPressed(ImGuiKey_Z)) && has_undo_command());

		const bool is_osx = io.ConfigMacOSXBehaviors;
		const bool is_osx_shift_shortcut = is_osx && (io.KeyMods == (ImGuiModFlags_Super | ImGuiModFlags_Shift));
		const bool is_redo = ((is_shortcut_key && ImGui::IsKeyPressed(ImGuiKey_Y)) || (is_osx_shift_shortcut && ImGui::IsKeyPressed(ImGuiKey_Z))) && has_redo_command();

		if (is_undo)
			undo();
		if (is_redo)
			redo();


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
						if (result.size())
						{
							std::string path = normalize_utf8(result[0]);
							if(!open_project(ctx, path.c_str()))
							{
							}
						}
					}

					if (ImGui::MenuItem("Save"))
					{
						pfd::save_file save("Save");
						const auto &result = save.result();
						if (0 < result.size())
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
				draw_tool(&ctx->tool);
				draw_hierarchy(&ctx->hirarchy);
			}
			ImGui::End();

			draw_widget(ctx->root);

			static ImVec2 inspectorSize{g_unitSize.x * 50, g_windowSize.y};
			ImGui::SetNextWindowSize(inspectorSize);
			ImGui::SetNextWindowPos({g_windowSize.x - inspectorSize.x, mainMenuSizeY});
			if (ImGui::Begin("inspector", nullptr, flag))
			{
				draw_histroy(history);

				inspectorSize = ImGui::GetWindowSize();
				inspectorSize.y = g_windowSize.y - mainMenuSizeY;
				draw_inspector(&ctx->inspector);
			}
			ImGui::End();
		}
		else
		{
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
