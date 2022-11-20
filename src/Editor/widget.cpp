#include "Precompiled.h"

#include "Editor/widget.h"
#include "Editor/widget_data.h"
#include "Editor/selection.h"
#include "Editor/history.h"


namespace imgui_editor
{
	void draw_children(widget* ctx)
	{
		for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
		{
			ImGui::PushID(i);
			draw_widget(ctx->children[i]);
			ImGui::PopID();
		}
	}

	void draw_widget(widget* ctx)
	{
		bool begin_type = false;
		switch (ctx->type)
		{
		case widget_type::widget_type_button:
		{
			ImGui::Button(ctx->label.c_str(), ctx->size);
		}
		break;
		case widget_type::widget_type_checkbox:
		{
			widget_checkbox* args = (widget_checkbox*)ctx->args;

			ImGui::Checkbox(ctx->label.c_str(), &args->check);
		}
		break;
		case widget_type::widget_type_radio_button:
		{
			widget_radio_button* args = (widget_radio_button*)ctx->args;

			ImGui::RadioButton(ctx->label.c_str(), args->active);
		}
		break;
		case widget_type::widget_type_small_button:
		{
			ImGui::SmallButton(ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_checkbox_flags:
		{
			widget_checkbox_flags* args = (widget_checkbox_flags*)ctx->args;
			ImGui::CheckboxFlags(ctx->label.c_str(), &args->flags, args->flags_value);
		}
		break;
		case widget_type::widget_type_text:
		{
			ImGui::Text("%s", ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_text_colored:
		{
			widget_text_colored* args = (widget_text_colored*)ctx->args;
			ImGui::TextColored(args->color, "%s", ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_bullet_text:
		{
			ImGui::BulletText("%s", ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_bullet:
		{
			ImGui::Bullet();
		}
		break;
		case widget_type::widget_type_selectable:
		{
			widget_text_selectable* args = (widget_text_selectable*)ctx->args;
			ImGui::Selectable(ctx->label.c_str(), args->selected, args->flags, ctx->size);
		}
		break;
		case widget_type::widget_type_label_text:
		{
			widget_label_text* args = (widget_label_text*)ctx->args;
			ImGui::LabelText(ctx->label.c_str(), "%s", args->text.c_str());
		}
		break;
		case widget_type::widget_type_input_text:
		{
			widget_input_text* args = (widget_input_text*)ctx->args;
			ImGui::InputText(ctx->label.c_str(), &args->text);
		}
		break;
		case widget_type::widget_type_input_text_with_hint:
		{
			widget_input_text_with_hint* args = (widget_input_text_with_hint*)ctx->args;
			ImGui::InputTextWithHint(ctx->label.c_str(), args->hint.c_str(), &args->text, args->flags);
		}
		break;
		case widget_type::widget_type_input_int:
		{
			widget_input_int* args = (widget_input_int*)ctx->args;
			ImGui::InputInt(ctx->label.c_str(), &args->value, args->step, args->step_fast, args->flags);
		}
		break;
		case widget_type::widget_type_input_int2:
		{
			widget_input_int2* args = (widget_input_int2*)ctx->args;
			ImGui::InputInt2(ctx->label.c_str(), args->value, args->flags);
		}
		break;
		case widget_type::widget_type_input_int3:
		{
			widget_input_int3* args = (widget_input_int3*)ctx->args;
			ImGui::InputInt3(ctx->label.c_str(), args->value, args->flags);
		}
		break;
		case widget_type::widget_type_input_int4:
		{
			widget_input_int4* args = (widget_input_int4*)ctx->args;
			ImGui::InputInt4(ctx->label.c_str(), args->value, args->flags);
		}
		break;
		case widget_type::widget_type_input_float:
		{
			widget_input_float* args = (widget_input_float*)ctx->args;
			ImGui::InputFloat(ctx->label.c_str(), &args->value, args->step, args->step_fast,args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_input_double:
		{
            widget_input_double* args = (widget_input_double*)ctx->args;
            ImGui::InputDouble(ctx->label.c_str(), &args->value);
		}
		break;
		case widget_type::widget_type_input_float3:
		{
            widget_input_float3* args = (widget_input_float3*)ctx->args;
            ImGui::InputFloat3(ctx->label.c_str(), args->value);
		}
		break;
		case widget_type::widget_type_drag_int:
		{
            widget_drag_int* args = (widget_drag_int*)ctx->args;
            ImGui::DragInt(ctx->label.c_str(), &args->value);
		}
		break;
		case widget_type::widget_type_drag_float:
		{
            widget_drag_float* args = (widget_drag_float*)ctx->args;
            ImGui::DragFloat(ctx->label.c_str(), &args->value);
		}
		break;
		case widget_type::widget_type_slider_int:
		{
            widget_slider_int* args = (widget_slider_int*)ctx->args;
            ImGui::SliderInt(ctx->label.c_str(), &args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_int2:
		{
            widget_slider_int2* args = (widget_slider_int2*)ctx->args;
            ImGui::SliderInt2(ctx->label.c_str(), args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_int3:
		{
            widget_slider_int3* args = (widget_slider_int3*)ctx->args;
            ImGui::SliderInt3(ctx->label.c_str(), args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_int4:
		{
            widget_slider_int4* args = (widget_slider_int4*)ctx->args;
            ImGui::SliderInt4(ctx->label.c_str(), args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_float:
		{
            widget_slider_float* args = (widget_slider_float*)ctx->args;
            ImGui::SliderFloat(ctx->label.c_str(), &args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_float2:
		{
			widget_slider_float2* args = (widget_slider_float2*)ctx->args;
			ImGui::SliderFloat2(ctx->label.c_str(), args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_float3:
		{
			widget_slider_float3* args = (widget_slider_float3*)ctx->args;
			ImGui::SliderFloat3(ctx->label.c_str(), args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_float4:
		{
			widget_slider_float4* args = (widget_slider_float4*)ctx->args;
			ImGui::SliderFloat4(ctx->label.c_str(), args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_slider_angle:
		{
			widget_slider_angle* args = (widget_slider_angle*)ctx->args;
			ImGui::SliderAngle(ctx->label.c_str(), &args->value, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_color_edit3:
		{
			widget_color_edit3* args = (widget_color_edit3*)ctx->args;
			ImGui::ColorEdit3(ctx->label.c_str(), args->value, args->flags);
		}
		break;
		case widget_type::widget_type_color_edit4:
		{
			widget_color_edit4* args = (widget_color_edit4*)ctx->args;
			ImGui::ColorEdit4(ctx->label.c_str(), args->value, args->flags);
		}
		break;
		case widget_type::widget_type_list_box:
		{
   			widget_list_box* args = (widget_list_box*)ctx->args;

			auto items = new const char*[args->items.size()];

			for(size_t i = 0, max = args->items.size(); i < max; ++i)
			{
				items[i] = args->items[i].c_str();
			}

			ImGui::ListBox(ctx->label.c_str(), &args->current_item, items, args->items.size(), args->height_in_items);

			delete[] items;
		}
		break;
		case widget_type::widget_type_collapsing_header:
		{
			widget_collapsing_header* args = (widget_collapsing_header*)ctx->args;
			ImGui::CollapsingHeader(ctx->label.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_separator:
		{
			ImGui::Separator();
		}
		break;
		case widget_type::widget_type_same_line:
		{
			ImGui::SameLine();
		}
		break;
		case widget_type::widget_type_spacing:
		{
			ImGui::Spacing();
		}
		break;
		case widget_type::widget_type_dummy:
		{
			// ImGui::Dummy();
		}
		break;
		case widget_type::widget_type_indent:
		{
			ImGui::Indent();
		}
		break;
		case widget_type::widget_type_unindent:
		{
			ImGui::Unindent();
		}
		break;
		case widget_type::widget_type_begin_end_window:
		{
			begin_type = true;
			if (ImGui::Begin(ctx->label.c_str()))
			{
				draw_children(ctx);
				ImGui::End();
			}
		}
		break;
		case widget_type::widget_type_begin_end_child:
		{
			begin_type = true;
			if (ImGui::BeginChild(ctx->label.c_str()))
			{
				draw_children(ctx);
			}
			ImGui::EndChild();
		}
		break;
		case widget_type::widget_type_begin_end_list_box:
		{
			begin_type = true;
			if (ImGui::BeginListBox(ctx->label.c_str()))
			{
				draw_children(ctx);
				ImGui::EndListBox();
			}
		}
		break;
		case widget_type::widget_type_begin_end_table:
		{
			begin_type = true;
			if(ImGui::BeginTable(ctx->label.c_str(), 2))
			{
				ImGui::EndTable();
			}
		}
		break;
		case widget_type::widget_type_push_pop_tree_node:
		{
			begin_type = true;
			if (ImGui::TreeNode(ctx->label.c_str()))
			{
				draw_children(ctx);
				ImGui::TreePop();
			}
		}
		break;
		case widget_type::widget_type_begin_end_combo:
		{
			begin_type = true;
			widget_begin_end_combo* args = (widget_begin_end_combo*)ctx->args;
			if (ImGui::BeginCombo(ctx->label.c_str(), args->preview_value.c_str()))
			{
				draw_children(ctx);
				ImGui::EndCombo();
			}
		}
		break;
		default:
		case widget_type::widget_type_none:			break;
		}

		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			selection::select(ctx);
		}
		if (ImGui::IsItemHovered(ImGuiMouseButton_Left))
		{
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));
		}

		if (!begin_type)
		{
			draw_children(ctx);
		}
	}

	void draw_inspector_widget(widget* args)
	{
		std::string temp;
		temp.reserve(args->label.capacity() * 2);
		temp = args->label;
		if (ImGui::InputText("label", const_cast<char*>(temp.c_str()), temp.capacity(), args->label.capacity()))
		{
			if (args->label.capacity() < temp.length())
			{
				args->label.reserve(temp.capacity());
			}
			args->label = temp.c_str();
		}
	}

	widget* new_widget(widget_type type)
	{
		auto w = new widget();
		w->type = type;
		switch (type)
		{
		case widget_type::widget_type_button:
		{
		}
		break;
		case widget_type::widget_type_checkbox:
		{
			w->args = new widget_checkbox();
		}
		break;
		case widget_type::widget_type_radio_button:
		{
			w->args = new widget_radio_button();
		}
		break;
		case widget_type::widget_type_small_button:
		{
		}
		break;
		case widget_type::widget_type_checkbox_flags:
		{

		}
		break;
		case widget_type::widget_type_text:
		{

		}
		break;
		case widget_type::widget_type_text_colored:
		{

		}
		break;
		case widget_type::widget_type_bullet_text:
		{

		}
		break;
		case widget_type::widget_type_bullet:
		{

		}
		break;
		case widget_type::widget_type_selectable:
		{

		}
		break;
		case widget_type::widget_type_label_text:
		{

		}
		break;
		case widget_type::widget_type_input_text:
		{

		}
		break;
		case widget_type::widget_type_input_text_with_hint:
		{

		}
		break;
		case widget_type::widget_type_input_int:
		{

		}
		break;
		case widget_type::widget_type_input_float:
		{

		}
		break;
		case widget_type::widget_type_input_double:
		{

		}
		break;
		case widget_type::widget_type_input_float3:
		{

		}
		break;
		case widget_type::widget_type_drag_int:
		{

		}
		break;
		case widget_type::widget_type_drag_float:
		{
			w->args = new widget_drag_float();
		}
		break;
		case widget_type::widget_type_slider_int:
		{

		}
		break;
		case widget_type::widget_type_slider_float:
		{

		}
		break;
		case widget_type::widget_type_slider_angle:
		{

		}
		break;
		case widget_type::widget_type_color_edit3:
		{

		}
		break;
		case widget_type::widget_type_color_edit4:
		{

		}
		break;
		case widget_type::widget_type_list_box:
		{

		}
		break;
		case widget_type::widget_type_collapsing_header:
		{

		}
		break;
		case widget_type::widget_type_same_line:
		{

		}
		break;
		case widget_type::widget_type_spacing:
		{

		}
		break;
		case widget_type::widget_type_dummy:
		{

		}
		break;
		case widget_type::widget_type_indent:
		{

		}
		break;
		case widget_type::widget_type_unindent:
		{

		}
		break;
		case widget_type::widget_type_begin_end_window:
		{

		}
		break;
		case widget_type::widget_type_begin_end_child:
		{

		}
		break;
		case widget_type::widget_type_begin_end_list_box:
		{

		}
		break;
		case widget_type::widget_type_begin_end_table:
		{

		}
		break;
		case widget_type::widget_type_push_pop_tree_node:
		{

		}
		case widget_type::widget_type_begin_end_combo:
		{
			w->args = new widget_begin_end_combo();
		}
		break;
		default:
		case widget_type::widget_type_none:
			break;
		}
		return w;
	}

	struct command_attach_child
	{
		widget* parent;
		widget* child;
		size_t index;
	};

	void command_attach_child_undo(void* _context)
	{
		command_attach_child* ctx = (command_attach_child*)_context;
		ctx->parent->children.erase(ctx->parent->children.begin() + ctx->index);
	}

	void command_attach_child_redo(void* _context)
	{
		command_attach_child* ctx = (command_attach_child*)_context;
		ctx->parent->children.push_back(ctx->child);
		ctx->index = ctx->parent->children.size() - 1;
	}

	void command_attach_child_destructor(void* ctx)
	{
		command_attach_child* cmd = (command_attach_child*)ctx;
		delete cmd;
	}

	void attach_child(widget* parent, widget* child)
	{
		imgui_editor::command* cmd = new imgui_editor::command();
		cmd->label = "attach child";

		command_attach_child* ctx = new command_attach_child();

		ctx->parent = parent;
		ctx->child = child;

		cmd->argument_data = ctx;
		cmd->undo = command_attach_child_undo;
		cmd->redo = command_attach_child_redo;
		cmd->destructor = command_attach_child_destructor;

		commit(cmd);

		// parent->children.push_back(child);
	}
}
