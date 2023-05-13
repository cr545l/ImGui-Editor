#include "Precompiled.h"
#include "editor/imgui_editor.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include <cpp-unicodelib/unicodelib.h>
#include <cpp-unicodelib/unicodelib_encodings.h>

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

	void open_path(widget_editor *ctx, const char *path)
	{
		std::ifstream ifs(path);
		std::string content((std::istreambuf_iterator<char>(ifs)),
							(std::istreambuf_iterator<char>()));

		widget_deserialize(ctx->root, content.c_str());

		ctx->last_open_paths.insert(ctx->last_open_paths.begin(), path);

		// remove duplicate paths
		std::vector<std::string> unique_paths;

		for (size_t i = 0, max = ctx->last_open_paths.size(); i < max; ++i)
		{
			const auto &path = ctx->last_open_paths[i];
			if (std::find(unique_paths.begin(), unique_paths.end(), path) == unique_paths.end())
			{
				unique_paths.push_back(path);
			}

			// limit 5, remove oldest path
			if (5 < unique_paths.size())
				break;
		}

		ctx->last_open_paths.assign(unique_paths.begin(), unique_paths.end());

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

		ini.SetValue("last_open_paths", "count", std::to_string(ctx->last_open_paths.size()).c_str());
		for (int i = 0; i < ctx->last_open_paths.size(); i++)
		{
			ini.SetValue("last_open_paths", std::to_string(i).c_str(), ctx->last_open_paths[i].c_str());
		}

		rc = ini.SaveFile("imgui_editor.ini");
		if (rc < 0)
		{
			printf("failed to save imgui_editor.ini");
		}
	}


	std::string normalizeUTF8(const std::string& input) 
	{
		std::string output;
		auto w = unicode::to_wstring(input);
		std::u32string nfd;
		unicode::utf8::decode(input.c_str(), input.length(), nfd);
		std::u32string nfc = unicode::to_nfc(nfd);
		unicode::utf8::encode(nfc.c_str(), nfc.length(), output);
		// std::wstring::to_wstring(input.c_str(), input.length())
		return output;
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
						std::string path = normalizeUTF8(result[0]);
						open_path(ctx, path.c_str());
					}
				}

				if (ImGui::MenuItem("Save"))
				{
					pfd::save_file save("Save");
					const auto &result = save.result();
					if (result.size())
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

		if (ctx->project)
		{
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
			// center child window
			ImGui::SetNextWindowPos({g_windowSize.x * 0.5f, g_windowSize.y * 0.5f}, ImGuiCond_Appearing, {0.5f, 0.5f});
			ImGui::SetNextWindowSize({g_windowSize.x * 0.5f, g_windowSize.y * 0.5f}, ImGuiCond_Appearing);
			if (ImGui::Begin("project", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
			{
				// show last open paths
				ImGui::Text(u8"마지막 경로Last Open Paths");

				for(size_t i =0, max = ctx->last_open_paths.size(); i < max; ++i)
				{
					const std::string& path = ctx->last_open_paths[i];
					if (ImGui::Button(path.c_str()))
					{
						open_path(ctx, path.c_str());
					}
				}

				static std::string utf8_string = u8"비어있음";
				if (ImGui::Button("Open"))
				{
					// 파일을 열고 내용을 읽습니다.
					std::ifstream file("utf8.txt");
					if (!file) {
						// 파일 열기 에러 핸들링
						return;
					}
					std::stringstream buffer;
					buffer << file.rdbuf();

					// UTF-8로 인코딩된 문자열을 가져옵니다.
					// 이 경우, 파일의 내용이 이미 UTF-8로 인코딩되어 있다고 가정하였습니다.
					utf8_string = buffer.str();
				}

				// ImGui를 사용하여 문자열을 출력합니다.
				ImGui::TextUnformatted(utf8_string.c_str());

			}
			ImGui::End();
		}
	}
}
