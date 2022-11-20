#include "Precompiled.h"

#include "Editor/widget.h"
#include "Editor/widget_data.h"
#include "Editor/selection.h"

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
			widget_selectable* args = (widget_selectable*)ctx->args;
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
			ImGui::InputText(ctx->label.c_str(), &args->text, args->flags);
		}
		case widget_type::widget_type_input_text_multiline:
		{
			widget_input_text_multiline* args = (widget_input_text_multiline*)ctx->args;
			ImGui::InputTextMultiline(ctx->label.c_str(), &args->text, ctx->size, args->flags);
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
		case widget_type::widget_type_input_float2:
		{
            widget_input_float2* args = (widget_input_float2*)ctx->args;
            ImGui::InputFloat2(ctx->label.c_str(), args->value, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_input_float3:
		{
            widget_input_float3* args = (widget_input_float3*)ctx->args;
            ImGui::InputFloat3(ctx->label.c_str(), args->value, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_input_float4:
		{
            widget_input_float4* args = (widget_input_float4*)ctx->args;
            ImGui::InputFloat4(ctx->label.c_str(), args->value, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_input_double:
		{
            widget_input_double* args = (widget_input_double*)ctx->args;
            ImGui::InputDouble(ctx->label.c_str(), &args->value);
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
			widget_same_line* args = (widget_same_line*)ctx->args;
			ImGui::SameLine(args->offset_from_start_x, args->spacing);
		}
		break;
		case widget_type::widget_type_spacing:
		{
			ImGui::Spacing();
		}
		break;
		case widget_type::widget_type_dummy:
		{
			widget_dummy* args = (widget_dummy*)ctx->args;
			ImGui::Dummy(args->size);
		}
		break;
		case widget_type::widget_type_indent:
		{
			widget_indent* args = (widget_indent*)ctx->args;
			ImGui::Indent(args->indent_w);
		}
		break;
		case widget_type::widget_type_unindent:
		{
			widget_unindent* args = (widget_unindent*)ctx->args;
			ImGui::Unindent(args->indent_w);
		}
		break;
		case widget_type::widget_type_begin_end_window:
		{
			begin_type = true;
			widget_begin_end_window* args = (widget_begin_end_window*)ctx->args;
			if (ImGui::Begin(ctx->label.c_str(), &args->open, args->flags))
			{
				draw_children(ctx);
			}
			ImGui::End();
		}
		break;
		case widget_type::widget_type_begin_end_child:
		{
			begin_type = true;
			widget_begin_end_child* args = (widget_begin_end_child*)ctx->args;
			if (ImGui::BeginChild(ctx->label.c_str(), args->size, args->border, args->flags))
			{
				draw_children(ctx);
			}
			ImGui::EndChild();
		}
		break;
		case widget_type::widget_type_begin_end_popup:
		{
			begin_type = true;
			widget_begin_end_popup* args = (widget_begin_end_popup*)ctx->args;
			if (ImGui::BeginPopup(ctx->label.c_str(), args->flags))
			{
				draw_children(ctx);
			}
			ImGui::EndPopup();
		}
		break;
		case widget_type::widget_type_begin_end_list_box:
		{
			begin_type = true;
			widget_begin_end_list_box* args = (widget_begin_end_list_box*)ctx->args;
			if (ImGui::BeginListBox(ctx->label.c_str(), args->size))
			{
				draw_children(ctx);
				ImGui::EndListBox();
			}
		}
		break;
		case widget_type::widget_type_begin_end_table:
		{
			begin_type = true;
			widget_begin_end_table* args = (widget_begin_end_table*)ctx->args;
			if(ImGui::BeginTable(ctx->label.c_str(), args->columns, args->flags, args->outer_size, args->inner_width))
			{
				draw_children(ctx);
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
			if (ImGui::BeginCombo(ctx->label.c_str(), args->preview_value.c_str(), args->flags))
			{
				draw_children(ctx);
				ImGui::EndCombo();
			}
		}
		break;
		case widget_type::widget_type_begin_end_menu:
		{
			begin_type = true;
			widget_begin_end_menu *args = (widget_begin_end_menu*)ctx->args;
			if (ImGui::BeginMenu(ctx->label.c_str(), args->enabled))
			{
				draw_children(ctx);
				ImGui::EndMenu();
			}
		}
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
}