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

namespace imgui_editor
{
	std::string normalize_utf8(const std::string& input) 
	{
		std::string output;
		auto w = unicode::to_wstring(input);
		std::u32string nfd;
		unicode::utf8::decode(input.c_str(), input.length(), nfd);
		std::u32string nfc = unicode::to_nfc(nfd);
		unicode::utf8::encode(nfc.c_str(), nfc.length(), output);
		return output;
	}
	
	void close_project(widget_editor *ctx)
	{
		ctx->project.ready = false;
		ctx->project.absolutePath = "";
		ctx->project.root = nullptr;
	}

	bool open_project(widget_editor *ctx, const char *path)
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
        return true;
	}
    
	void draw_start_page(widget_editor* ctx)
	{
		const float unit_size = ImGui::GetFontSize();

		// 창의 크기와 위치를 계산
		const ImVec2 window_size(unit_size * 30, unit_size * 20);
		const ImVec2 window_pos((ImGui::GetIO().DisplaySize.x - window_size.x) * 0.5f, (ImGui::GetIO().DisplaySize.y - window_size.y) * 0.5f);

        // center child window
        ImGui::SetNextWindowPos(window_pos);
        ImGui::SetNextWindowSize(window_size);
        if (ImGui::Begin("project", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
        {
            // show last open paths
            ImGui::Text("Last Open Paths");

			int failOpenIndex = -1;
			auto& paths= ctx->last_open_paths;
            for(size_t i = 0, max = paths.size(); i < max; ++i)
            {
                const std::string& path = paths[i];
                if (ImGui::Button(path.c_str()))
                {
                    const bool opened = open_project(ctx, path.c_str());
                    printf("%s", opened?"True":"False");
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
						printf("failed to save imgui_editor.ini");
					}
				}
			}
        }
        ImGui::End();
    }
}
