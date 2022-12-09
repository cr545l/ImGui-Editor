#include "Precompiled.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"
#include "editor/selection.h"
#include "editor/command.h"

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
		for(size_t i = 0, max = ctx->style_colors.size(); i < max; ++i)
		{
			ImGui::PushStyleColor(ctx->style_colors[i].idx, (ImVec4)ctx->style_colors[i].col);
		}
		for(size_t i = 0, max = ctx->style_var_floats.size(); i < max; ++i)
		{
			ImGui::PushStyleVar(ctx->style_var_floats[i].idx, ctx->style_var_floats[i].val);
		}
		for(size_t i = 0, max = ctx->style_var_vec2s.size(); i < max; ++i)
		{
			ImGui::PushStyleVar(ctx->style_var_vec2s[i].idx, ctx->style_var_vec2s[i].val);
		}

		bool begin_type = false;
		switch (ctx->type)
		{
		case widget_type::widget_type_none:	
		break;

#pragma region // Windows
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
			if (ImGui::BeginChild(ctx->label.c_str(), ctx->size, args->border, args->flags))
			{
				draw_children(ctx);
			}
			ImGui::EndChild();
		}
		break;
#pragma endregion // Windows

#pragma region // Parameters stacks (current window)
		case widget_type::widget_type_push_pop_item_width:
		{
			begin_type = true;
			widget_push_pop_item_width* args = (widget_push_pop_item_width*)ctx->args;
			ImGui::PushItemWidth(args->item_width);
			draw_children(ctx);
			ImGui::PopItemWidth();
		}
		break;
		case widget_type::widget_type_push_pop_text_wrap_pos:
		{
			begin_type = true;
			widget_push_pop_text_wrap_pos* args = (widget_push_pop_text_wrap_pos*)ctx->args;
			ImGui::PushTextWrapPos(args->item_width);
			draw_children(ctx);
			ImGui::PopTextWrapPos();
		}
		break;
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
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
			ImGui::Dummy(ctx->size);
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
		case widget_type::widget_type_begin_end_group:
		{
			begin_type = true;
			widget_begin_end_group* args = (widget_begin_end_group*)ctx->args;
			ImGui::BeginGroup();
			draw_children(ctx);
			ImGui::EndGroup();
		}
		break;
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
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
		case widget_type::widget_type_label_text:
		{
			widget_label_text* args = (widget_label_text*)ctx->args;
			ImGui::LabelText(ctx->label.c_str(), "%s", args->text.c_str());
		}
		break;
		case widget_type::widget_type_bullet_text:
		{
			ImGui::BulletText("%s", ctx->label.c_str());
		}
		break;
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
		case widget_type::widget_type_button:
		{
			ImGui::Button(ctx->label.c_str(), ctx->size);
		}
		break;
		case widget_type::widget_type_small_button:
		{
			ImGui::SmallButton(ctx->label.c_str());
		}
		break;
		case widget_type::widget_type_checkbox:
		{
			widget_checkbox* args = (widget_checkbox*)ctx->args;

			ImGui::Checkbox(ctx->label.c_str(), &args->check);
		}
		break;
		case widget_type::widget_type_checkbox_flags:
		{
			widget_checkbox_flags* args = (widget_checkbox_flags*)ctx->args;

			ImGui::CheckboxFlags(ctx->label.c_str(), &args->flags, args->flags_value);
		}
		break;
		case widget_type::widget_type_radio_button:
		{
			widget_radio_button* args = (widget_radio_button*)ctx->args;

			ImGui::RadioButton(ctx->label.c_str(), args->active);
		}
		break;
		case widget_type::widget_type_bullet:
		{
			ImGui::Bullet();
		}
		break;
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
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
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
		case widget_type::widget_type_drag_float:
		{
            widget_drag_float* args = (widget_drag_float*)ctx->args;
            ImGui::DragFloat(ctx->label.c_str(), &args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_drag_float2:
		{
			widget_drag_float2* args = (widget_drag_float2*)ctx->args;
			ImGui::DragFloat2(ctx->label.c_str(), args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_drag_float3:
		{
			widget_drag_float3* args = (widget_drag_float3*)ctx->args;
			ImGui::DragFloat3(ctx->label.c_str(), args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_drag_float4:
		{
			widget_drag_float4* args = (widget_drag_float4*)ctx->args;
			ImGui::DragFloat4(ctx->label.c_str(), args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_drag_int:
		{
            widget_drag_int* args = (widget_drag_int*)ctx->args;
            ImGui::DragInt(ctx->label.c_str(), &args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_drag_int2:
		{
			widget_drag_int2* args = (widget_drag_int2*)ctx->args;
			ImGui::DragInt2(ctx->label.c_str(), args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_drag_int3:
		{
			widget_drag_int3* args = (widget_drag_int3*)ctx->args;
			ImGui::DragInt3(ctx->label.c_str(), args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
		case widget_type::widget_type_drag_int4:
		{
			widget_drag_int4* args = (widget_drag_int4*)ctx->args;
			ImGui::DragInt4(ctx->label.c_str(), args->value, args->speed, args->min, args->max, args->format.c_str(), args->flags);
		}
		break;
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
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
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
		case widget_type::widget_type_input_text:
		{
			widget_input_text* args = (widget_input_text*)ctx->args;
			ImGui::InputText(ctx->label.c_str(), &args->text, args->flags);
		}
		break;
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
		case widget_type::widget_type_input_double:
		{
            widget_input_double* args = (widget_input_double*)ctx->args;
            ImGui::InputDouble(ctx->label.c_str(), &args->value);
		}
		break;
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
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
		case widget_type::widget_type_color_picker3:
		{
			widget_color_picker3* args = (widget_color_picker3*)ctx->args;
			ImGui::ColorPicker3(ctx->label.c_str(), args->value, args->flags);
		}
		break;
		case widget_type::widget_type_color_picker4:
		{
			widget_color_picker4* args = (widget_color_picker4*)ctx->args;
			ImGui::ColorPicker4(ctx->label.c_str(), args->value, args->flags);
		}
		break;
		case widget_type::widget_type_color_button:
		{
			widget_color_button* args = (widget_color_button*)ctx->args;
			ImGui::ColorButton(ctx->label.c_str(), args->col, args->flags, ctx->size);
		}
		break;
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
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
		case widget_type::widget_type_collapsing_header:
		{
			widget_collapsing_header* args = (widget_collapsing_header*)ctx->args;
			ImGui::CollapsingHeader(ctx->label.c_str(), args->flags);
		}
		break;
#pragma endregion // Widgets: Trees
		
#pragma region // Widgets: Selectables
		case widget_type::widget_type_selectable:
		{
			widget_selectable* args = (widget_selectable*)ctx->args;
			ImGui::Selectable(ctx->label.c_str(), args->selected, args->flags, ctx->size);
		}
		break;
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
		case widget_type::widget_type_begin_end_list_box:
		{
			begin_type = true;
			widget_begin_end_list_box* args = (widget_begin_end_list_box*)ctx->args;
			if (ImGui::BeginListBox(ctx->label.c_str(), ctx->size))
			{
				draw_children(ctx);
				ImGui::EndListBox();
			}
		}
		break;
#pragma endregion // Widgets: List Boxes
		
#pragma region // Widgets: Menus
		case widget_type::widget_type_begin_end_menu:
		{
			begin_type = true;
			widget_begin_end_menu* args = (widget_begin_end_menu*)ctx->args;
			if (ImGui::BeginMenu(ctx->label.c_str(), args->enabled))
			{
				draw_children(ctx);
				ImGui::EndMenu();
			}
		}
		break;
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
		case widget_type::widget_type_begin_end_popup:
		{
			begin_type = true;
			widget_begin_end_popup* args = (widget_begin_end_popup*)ctx->args;
			if (ImGui::BeginPopup(ctx->label.c_str(), args->flags))
			{
				draw_children(ctx);
				ImGui::EndPopup();
			}
		}
		break;
#pragma endregion // Popups, Modals
		
#pragma region // Tables
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
		case widget_type::widget_type_table_next_row:
		{
			widget_table_next_row* args = (widget_table_next_row*)ctx->args;
			ImGui::TableNextRow(args->flags, args->min_row_height);
		}
		break;
		case widget_type::widget_type_table_next_column:
		{
			widget_table_next_column* args = (widget_table_next_column*)ctx->args;
			ImGui::TableNextColumn();
		}
		break;
		case widget_type::widget_type_table_set_column_index:
		{
			widget_table_set_column_index* args = (widget_table_set_column_index*)ctx->args;
			ImGui::TableSetColumnIndex(args->column_n);
		}
		break;
#pragma endregion // Tables

		default:
			debug_break();
			break;
		}

		for(size_t i = 0, max = ctx->style_var_vec2s.size(); i < max; ++i)
		{
			ImGui::PopStyleVar();
		}
		for(size_t i = 0, max = ctx->style_var_floats.size(); i < max; ++i)
		{
			ImGui::PopStyleVar();
		}
		for(size_t i = 0, max = ctx->style_colors.size(); i < max; ++i)
		{
			ImGui::PopStyleColor();
		}

		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			command::select(ctx);
		}

		if (ImGui::IsItemHovered(ImGuiMouseButton_Left))
		{
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));
		}

		if(ImGui::BeginDragDropSource( ImGuiDragDropFlags_SourceAllowNullID))
		{
			ImGui::SetDragDropPayload("widget", &ctx, sizeof(widget*));
			ImGui::Text(ctx->label.c_str());
			ImGui::EndDragDropSource();
		}

		if(ImGui::BeginDragDropTarget())
		{
			if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("widget"))
			{
				widget* source = *(widget**)payload->Data;
				if(source != ctx)
				{
					command::attach_child(ctx, source);
				}
			}
			ImGui::EndDragDropTarget();
		}

		if (!begin_type)
		{
			draw_children(ctx);
		}
	}
}