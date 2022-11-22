#include "Precompiled.h"

#include <algorithm>
#include <magic_enum.hpp>
#include "Editor/widget_editor.h"

#include "Editor/selection.h"
#include "Editor/history.h"

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
				ImGui::EndChild();
			}
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
			auto ctx = selection::get_targets()[0];

			ImGui::Separator();
			
			if(ImGui::TreeNode("Output"))
			{
				std::string s =  widget_data_serialize(ctx->type, ctx->args);
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
					widget_data_deserialize(ctx->type, ctx->args, context->input.c_str());
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

		constexpr static ImGuiWindowFlags flag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar;

		const ImVec2 toolSize{g_unitSize.x * 50, g_windowSize.y};
		ImGui::SetNextWindowSize(toolSize);
		ImGui::SetNextWindowPos({0, 0});
		if (ImGui::Begin("tool", nullptr, flag))
		{
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

		const ImVec2 viewSize{g_windowSize.x - toolSize.x * 2, g_windowSize.y};
		ImGui::SetNextWindowSize(viewSize);
		ImGui::SetNextWindowPos({toolSize.x, 0});
		if (ImGui::Begin("view", nullptr, flag | ImGuiWindowFlags_NoBackground))
		{
			draw_widget(ctx->root);
			// const ImVec2 pos = ImGui::GetCurrentWindow()->Pos;
			// const ImVec2 cursor = pos + ImGui::GetCursorPos();
			// const ImVec2 max = cursor + ImVec2(g_unitSize.x * 0.5f, g_unitSize.y);
			// ImGui::GetWindowDrawList()->AddRectFilled(cursor, max, IM_COL32_WHITE);
		}
		ImGui::End();

		ImGui::SetNextWindowSize(toolSize);
		ImGui::SetNextWindowPos({g_windowSize.x - toolSize.x, 0});
		if (ImGui::Begin("inspector", nullptr, flag))
		{
			draw_widget_inspector(&ctx->inspector);
		}
		ImGui::End();
	}
}
