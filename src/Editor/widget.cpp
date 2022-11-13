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
			widget_checkbox* context = (widget_checkbox*)ctx->context;

			ImGui::Checkbox(ctx->label.c_str(), &context->check);
		}
		break;
		case widget_type::widget_type_radio_button:
		{
			widget_radio_button* context = (widget_radio_button*)ctx->context;

			ImGui::RadioButton(ctx->label.c_str(), &context->active);
		}
		break;
		case widget_type::widget_type_small_button:
		{
			ImGui::SmallButton(ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_checkbox_flags:
		{
			widget_checkbox_flags* context = (widget_checkbox_flags*)ctx->context;
			ImGui::CheckboxFlags(ctx->label.c_str(), &context->flags, context->flags_value);
		}
		break;
		case widget_type::widget_type_text:
		{
			ImGui::Text(ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_text_colored:
		{
			widget_text_colored* context = (widget_text_colored*)ctx->context;
			ImGui::TextColored(context->color, ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_bullet_text:
		{
			ImGui::BulletText(ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_bullet:
		{
			ImGui::Bullet();
		}
		break;
		case widget_type::widget_type_selectable:
		{
			widget_text_selectable* context = (widget_text_selectable*)ctx->context;
			ImGui::Selectable(ctx->label.c_str(), context->selected, context->flags, ctx->size);
		}
		break;
		case widget_type::widget_type_label_text:
		{
			widget_label_text* context = (widget_label_text*)ctx->context;
			ImGui::LabelText(ctx->label.c_str(), context->text.c_str());
		}
		break;
		case widget_type::widget_type_input_text:
		{
			widget_input_text* context = (widget_input_text*)ctx->context;
			ImGui::InputText(ctx->label.c_str(), &context->text);
		}
		break;
		case widget_type::widget_type_input_text_with_hint:
		{
			widget_input_text_with_hint* context = (widget_input_text_with_hint*)ctx->context;
			ImGui::InputTextWithHint(ctx->label.c_str(), context->hint.c_str(), &context->text, context->flags);
		}
		break;
		case widget_type::widget_type_input_int:
		{
			widget_input_int* context = (widget_input_int*)ctx->context;
			ImGui::InputInt(ctx->label.c_str(), &context->value, context->step, context->step_fast, context->flags);
		}
		break;
		case widget_type::widget_type_input_int2:
		{
			widget_input_int2* context = (widget_input_int2*)ctx->context;
			ImGui::InputInt2(ctx->label.c_str(), context->value, context->flags);
		}
		break;
		case widget_type::widget_type_input_int3:
		{
			widget_input_int3* context = (widget_input_int3*)ctx->context;
			ImGui::InputInt3(ctx->label.c_str(), context->value, context->flags);
		}
		break;
		case widget_type::widget_type_input_int4:
		{
			widget_input_int4* context = (widget_input_int4*)ctx->context;
			ImGui::InputInt4(ctx->label.c_str(), context->value, context->flags);
		}
		break;
		case widget_type::widget_type_input_float:
		{
			widget_input_float* context = (widget_input_float*)ctx->context;
			ImGui::InputFloat(ctx->label.c_str(), &context->value, context->step, context->step_fast, context->format.c_str(), context->flags);
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
			widget_begin_end_combo* context = (widget_begin_end_combo*)ctx->context;
			if (ImGui::BeginCombo(ctx->label.c_str(), context->preview_value.c_str()))
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

	void draw_inspector_widget(widget* context)
	{
		std::string temp;
		temp.reserve(context->label.capacity() * 2);
		temp = context->label;
		if (ImGui::InputText("label", const_cast<char*>(temp.c_str()), temp.capacity(), context->label.capacity()))
		{
			if (context->label.capacity() < temp.length())
			{
				context->label.reserve(temp.capacity());
			}
			context->label = temp.c_str();
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
			w->context = new widget_checkbox();
		}
		break;
		case widget_type::widget_type_radio_button:
		{
			w->context = new widget_radio_button();
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
			w->context = new widget_drag_float();
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
			w->context = new widget_begin_end_combo();
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

		cmd->context = ctx;
		cmd->undo = command_attach_child_undo;
		cmd->redo = command_attach_child_redo;
		cmd->destructor = command_attach_child_destructor;

		commit(cmd);

		// parent->children.push_back(child);
	}
}
