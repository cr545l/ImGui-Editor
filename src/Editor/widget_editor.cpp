#include "Precompiled.h"

#include <algorithm>
#include <fstream>

#include <magic_enum/magic_enum.hpp>
#include <portable-file-dialogs/portable-file-dialogs.h>
#include <simpleini/SimpleIni.h>

#include "editor/widget_editor.h"
#include "editor/selection.h"
#include "editor/history.h"

ImVec2 g_windowSize;
ImVec2 g_unitSize;
size_t g_widget_id = 0;

namespace imgui_editor
{
	void init_widget_editor(widget_editor *ctx, const char* init)
	{
		g_widget_id = 0;
		ctx->root = new_widget(widget_type::widget_type_begin_end_window);
		ctx->root->label = "root";

		// debug_break();
		if(0 != strcmp("", init))
		{
			widget_deserialize(ctx->root, init);
		}

		ctx->tool.editor = ctx;
		ctx->tool.root = ctx->root;

		ctx->hirarchy.editor = ctx;
		ctx->hirarchy.root = ctx->root;
		ctx->inspector.editor = ctx;
	}
	
	void draw_widget_editor(widget_editor *ctx)
	{
		g_windowSize = ImGui::GetIO().DisplaySize;
		g_unitSize = ImGui::CalcTextSize(" ");
				
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{
					pfd::open_file open("Open");

					const auto& result = open.result();
					if(result.size())
					{
						std::ifstream ifs(result[0]);
						std::string content((std::istreambuf_iterator<char>(ifs)),
											(std::istreambuf_iterator<char>()));

						widget_deserialize(ctx->root, content.c_str());
					}
				}

				if (ImGui::MenuItem("Save"))
				{
					pfd::save_file save("Save");
					const auto& result = save.result();
					if(result.size())
					{
						std::ofstream ofs(result);
						ofs << widget_serialize(ctx->root);
					}
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
			draw_widget_tool(&ctx->tool);
			draw_widget_hierarchy(&ctx->hirarchy);
		}
		ImGui::End();

		draw_widget(ctx->root);

		static ImVec2 inspectorSize{ g_unitSize.x * 50, g_windowSize.y };
		ImGui::SetNextWindowSize(inspectorSize);
		ImGui::SetNextWindowPos({g_windowSize.x - inspectorSize.x, mainMenuSizeY });
		if (ImGui::Begin("inspector", nullptr, flag))
		{
			inspectorSize = ImGui::GetWindowSize();
			inspectorSize.y = g_windowSize.y - mainMenuSizeY;
			draw_widget_inspector(&ctx->inspector);
		}
		ImGui::End();
	}
}
