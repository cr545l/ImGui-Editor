#include "Precompiled.h"
#include "editor/imgui_editor.h"

#include <algorithm>
#include <fstream>

#include <magic_enum/magic_enum.hpp>
#include <portable-file-dialogs/portable-file-dialogs.h>
#include <simpleini/SimpleIni.h>

#include "editor/history.h"
#include "editor/selection.h"

namespace imgui_editor
{
	extern ImVec2 g_unitSize;
	extern size_t g_widget_id;
	extern std::unordered_map<size_t, widget*>* g_widget_table;

	void close_project(imgui_editor_context *ctx)
	{
		ctx->project.ready = false;
		ctx->project.absolutePath = "";
		ctx->project.root = nullptr;
		ctx->project.dirty = false;

		delete_widget(ctx->root);
		selection::reset();
		reset_history();

		g_widget_id = 0;

		assert(g_widget_table->empty());

		ctx->root = new_widget(widget_type::widget_type_begin_end_window);
		regist_widget(ctx->root);

		ctx->root->label = "root";
	}

	bool open_project(imgui_editor_context *ctx, const char *path)
	{
		std::ifstream ifs(path);
        
    	if(!ifs.good()) return false;

		const std::string content((std::istreambuf_iterator<char>(ifs)),
		                          (std::istreambuf_iterator<char>()));

		widget_deserialize(ctx->root, content.c_str());

		ctx->last_open_paths.insert(ctx->last_open_paths.begin(), path);

		ctx->project.absolutePath = path;
		ctx->project.root = ctx->root;
		ctx->project.ready = true;
		ctx->project.dirty = false;

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
				LOG("failed to save imgui_editor.ini");
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
			LOG("failed to save imgui_editor.ini");
		}
        return true;
	}
    
	void draw_start_page(imgui_editor_context* ctx)
	{
		// 창의 크기와 위치를 계산
		const ImVec2 window_size(g_unitSize.x * 150, g_unitSize.y * 20);
		const ImVec2 window_pos((ImGui::GetIO().DisplaySize.x - window_size.x) * 0.5f, (ImGui::GetIO().DisplaySize.y - window_size.y) * 0.5f);

        // center child window
        ImGui::SetNextWindowPos(window_pos);
        ImGui::SetNextWindowSize(window_size);
        if (ImGui::Begin("project", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
        {
            // show last open paths
            ImGui::Text(F("start_page.last_opened"));

			int failOpenIndex = -1;
			auto& paths= ctx->last_open_paths;
            for(size_t i = 0, max = paths.size(); i < max; ++i)
            {
                const std::string& path = paths[i];
                if (ImGui::Button(path.c_str()))
                {
                    const bool opened = open_project(ctx, path.c_str());
					// LOG("%s", opened?"True":"False");
                    if(!opened)
					{
						failOpenIndex = i;
					}
                }
            }

			if(-1 != failOpenIndex)
			{
				for (auto it = paths.begin(); it != paths.end(); ++it) {
					if (*it == paths[failOpenIndex]) {
						paths.erase(it);
						break;
					}
				}

				CSimpleIniA ini;
				ini.SetUnicode();
				SI_Error rc = ini.LoadFile("imgui_editor.ini");
				if (rc == 0)
				{
					ini.SetValue("last_open_paths", "count", std::to_string(paths.size()).c_str());
					for (int i = 0; i < paths.size(); i++)
					{
						ini.SetValue("last_open_paths", std::to_string(i).c_str(), paths[i].c_str());
					}

					rc = ini.SaveFile("imgui_editor.ini");
					if (rc < 0)
					{
						LOG("failed to save imgui_editor.ini");
					}
				}
			}
        }
        ImGui::End();
    }
}
