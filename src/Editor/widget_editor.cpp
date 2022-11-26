#include "Precompiled.h"

#include <algorithm>
#include <magic_enum/magic_enum.hpp>
#include <portable-file-dialogs/portable-file-dialogs.h>
#include <simpleini/SimpleIni.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include "editor/widget_editor.h"

#include "editor/selection.h"
#include "editor/history.h"

ImVec2 g_windowSize;
ImVec2 g_unitSize;

namespace imgui_editor
{
	void draw_widget_tool(widget_tool *ctx)
	{
		if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unitSize.y * 25), true))
		{
			if (ImGui::BeginChild("Types", ImVec2(0.f, g_unitSize.y * 20)))
			{
				magic_enum::enum_for_each<widget_type>([&](widget_type t)
					{
						std::string name = std::string(magic_enum::enum_name(t));

						name = name.substr(12, name.length() - 12);
						// name replace _ to space
						std::replace(name.begin(), name.end(), '_', ' ');
						if (ImGui::Selectable(name.c_str(), t == ctx->type))
						{
							ctx->type = t;
						} });
			}
			ImGui::EndChild();

			ImGui::Separator();
			const bool disable = nullptr == ctx->root;
			ImGui::BeginDisabled(disable);
			if (ImGui::Button("Add Widget"))
			{
				auto selected = selection::get_targets();
				if (selected.size())
				{
					for (auto i : selected)
					{
						attach_child(i, new_widget(ctx->type));
					}
				}
				else
				{
					attach_child(ctx->root, new_widget(ctx->type));
				}
			}
			ImGui::EndDisabled();
		}
		ImGui::EndChild();
	}

	void init_widget_editor(widget_editor *ctx)
	{
		ctx->root = new_widget(widget_type::widget_type_begin_end_window);
		ctx->root->label = "root";

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
	}

	void draw_widget_hierarchy(widget_hierarchy *context)
	{
		auto selected = selection::get_targets();
		std::function<void(widget *)> drawNode = [&](widget *_widget)
		{
			ImGui::PushID(_widget->label.c_str());
			ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick;

			if (std::any_of(selected.begin(), selected.end(), [&](widget *w)
							{ return w == _widget; }))
			{
				flag |= ImGuiTreeNodeFlags_Selected;
			}

			if (_widget && ImGui::TreeNodeEx(_widget->label.c_str(), flag))
			{
				const auto &children = _widget->children;
				for (size_t i = 0, max = children.size(); i < max; ++i)
				{
					ImGui::PushID(i);
					drawNode(children[i]);
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				selection::select(_widget);
			}
			ImGui::PopID();
		};

		drawNode(context->root);
	}

	void draw_widget_inspector(widget_inspector *context)
	{
		auto selected = selection::get_targets();
		ImGui::Text("Selected %lu", selected.size());

		if(selected.size())
		{
			widget* ctx = selection::get_targets()[0];

			ImGui::Separator();
			
			if(ImGui::TreeNode("Output"))
			{
				std::string s =  widget_serialize(ctx);
				ImGui::InputTextMultiline("##data", &s, ImVec2(0, 0), ImGuiInputTextFlags_ReadOnly);
				ImGui::TreePop();
			}

			if(ImGui::TreeNode("Input"))
			{
				// std::string s =  widget_data_serialize(ctx->type, ctx->args);
				ImGui::InputTextMultiline("##data", &context->input, ImVec2(0, 0));
				// widget_data_deserialize(ctx->type, ctx->args, s);
				if(ImGui::Button("Apply"))
				{
					widget_deserialize(ctx, context->input.c_str());
				}

				ImGui::TreePop();
			}

			ImGui::Separator();

			for (auto i : selected)
			{
				draw_inspector_widget(i);
			}
		}
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

					open.result();
				}

				if (ImGui::MenuItem("Save"))
				{
					pfd::save_file save("Save");
					save.result();
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

			ImGui::BeginDisabled(!has_undo_command());
			if (ImGui::Button("Undo"))
			{
				undo();
			}
			ImGui::EndDisabled();

			ImGui::SameLine();

			ImGui::BeginDisabled(!has_redo_command());
			if (ImGui::Button("Redo"))
			{
				redo();
			}
			ImGui::EndDisabled();

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
