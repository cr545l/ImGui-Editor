#include "Precompiled.h"

#include "Editor/widget.h"
#include "Editor/widget_data.h"

#include "Editor/imgui.h"

namespace imgui_editor
{
    void draw_inspector_widget(widget *ctx)
    {
        ImGui::InputText("label", &ctx->label);

        switch (ctx->type)
        {
        case widget_type::widget_type_none:
        break;
        case widget_type::widget_type_button:
        break;
        case widget_type::widget_type_small_button:
        break;
        case widget_type::widget_type_checkbox:
        {
            widget_checkbox *args = (widget_checkbox *)ctx->args;
            ImGui::Checkbox("check", &args->check);
        }
        break;
        case widget_type::widget_type_checkbox_flags:
        {
            widget_checkbox_flags *args = (widget_checkbox_flags *)ctx->args;
            ImGui::InputInt("flags", &args->flags);
            ImGui::InputInt("flags_value", &args->flags_value);         
        }
        break;
        case widget_type::widget_type_radio_button:
        {
            widget_radio_button *args = (widget_radio_button *)ctx->args;
            ImGui::Checkbox("active", &args->active);
        }
        break;
        case widget_type::widget_type_text:
        break;
        case widget_type::widget_type_text_colored:
        {
            widget_text_colored *args = (widget_text_colored *)ctx->args;
            ImGui::ColorEdit4("color", &args->color.Value.x);
        }
        break;
        case widget_type::widget_type_bullet_text:
        break;
        case widget_type::widget_type_bullet:
        break;
        case widget_type::widget_type_selectable:
        {
            widget_selectable *args = (widget_selectable *)ctx->args;

            ImGui::Checkbox("selected", &args->selected);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_label_text:
        break;
        case widget_type::widget_type_input_text:
        {
            widget_input_text *args = (widget_input_text *)ctx->args;

            ImGui::InputText("text", &args->text);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_text_multiline:
        {
            widget_input_text_multiline *args = (widget_input_text_multiline *)ctx->args;

            ImGui::InputTextMultiline("text", &args->text);
            ImGui::DragFloat2("size", &args->size.x);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_text_with_hint:
        {
            widget_input_text_with_hint *args = (widget_input_text_with_hint *)ctx->args;

            ImGui::InputText("text", &args->text);
            ImGui::InputText("hint", &args->hint);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int:
        {
            widget_input_int *args = (widget_input_int *)ctx->args;

            ImGui::DragInt("value", &args->value);
            ImGui::DragInt("step", &args->step);
            ImGui::DragInt("step_fast", &args->step_fast);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int2:
        {
            widget_input_int2 *args = (widget_input_int2 *)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int3:
        {
            widget_input_int3 *args = (widget_input_int3 *)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int4:
        {
            widget_input_int4 *args = (widget_input_int4 *)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_float:
        {
            widget_input_float *args = (widget_input_float *)ctx->args;

            ImGui::DragFloat("value", &args->value);
            ImGui::DragFloat("step", &args->step);
            ImGui::DragFloat("step_fast", &args->step_fast);
        }
        break;
        case widget_type::widget_type_input_float2:
        {
            widget_input_float2 *args = (widget_input_float2 *)ctx->args;

            ImGui::DragFloat2("value", args->value);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_float3:
        {
            widget_input_float3 *args = (widget_input_float3 *)ctx->args;

            ImGui::DragFloat3("value", args->value);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_float4:
        {
            widget_input_float4 *args = (widget_input_float4 *)ctx->args;

            ImGui::DragFloat4("value", args->value);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_double:
        {
            widget_input_double *args = (widget_input_double *)ctx->args;

            // ImGui::DragScalar("value", ImGuiDataType_Double, &args->value);
            // ImGui::DragFloat("step", &args->step);
            // ImGui::DragScalar("step_fast", &args->step_fast);
        }
        break;
        case widget_type::widget_type_drag_int:
        {
            widget_drag_int *args = (widget_drag_int *)ctx->args;

            ImGui::DragInt("value", &args->value);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_int2:
        {
            widget_drag_int2 *args = (widget_drag_int2 *)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_int3:
        {
            widget_drag_int3 *args = (widget_drag_int3 *)ctx->args;

            ImGui::DragInt3("value", args->value);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_int4:
        {
            widget_drag_int4 *args = (widget_drag_int4 *)ctx->args;

            ImGui::DragInt4("value", args->value);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_float:
        {
            widget_drag_float *args = (widget_drag_float *)ctx->args;

            ImGui::DragFloat("value", &args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_float2:
        {
            widget_drag_float2 *args = (widget_drag_float2 *)ctx->args;

            ImGui::DragFloat2("value", args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_float3:
        {
            widget_drag_float3 *args = (widget_drag_float3 *)ctx->args;

            ImGui::DragFloat3("value", args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_float4:
        {
            widget_drag_float4 *args = (widget_drag_float4 *)ctx->args;

            ImGui::DragFloat4("value", args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int:
        {
            widget_slider_int *args = (widget_slider_int *)ctx->args;

            ImGui::SliderInt("value", &args->value, args->min, args->max);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int2:
        {
            widget_slider_int2 *args = (widget_slider_int2 *)ctx->args;

            ImGui::SliderInt2("value", args->value, args->min, args->max);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int3:
        {
            widget_slider_int3 *args = (widget_slider_int3 *)ctx->args;

            ImGui::SliderInt3("value", args->value, args->min, args->max);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int4:
        {
            widget_slider_int4 *args = (widget_slider_int4 *)ctx->args;

            ImGui::SliderInt4("value", args->value, args->min, args->max);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_float:
        {
            widget_slider_float *args = (widget_slider_float *)ctx->args;

            ImGui::SliderFloat("value", &args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_float2:
        {
            widget_slider_float2 *args = (widget_slider_float2 *)ctx->args;

            ImGui::SliderFloat2("value", args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_float3:
        {
            widget_slider_float3 *args = (widget_slider_float3 *)ctx->args;

            ImGui::SliderFloat3("value", args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_float4:
        {
            widget_slider_float4 *args = (widget_slider_float4 *)ctx->args;

            ImGui::SliderFloat4("value", args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_edit3:
        {
            widget_color_edit3 *args = (widget_color_edit3 *)ctx->args;

            ImGui::ColorEdit3("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_edit4:
        {
            widget_color_edit4 *args = (widget_color_edit4 *)ctx->args;

            ImGui::ColorEdit4("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_picker3:
        {
            widget_color_picker3 *args = (widget_color_picker3 *)ctx->args;

            ImGui::ColorPicker3("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_picker4:
        {
            widget_color_picker4 *args = (widget_color_picker4 *)ctx->args;

            ImGui::ColorPicker4("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_button:
        {
            widget_color_button *args = (widget_color_button *)ctx->args;
            ImGui::DragFloat4("col", &args->col.x);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_list_box:
        {
            widget_list_box *args = (widget_list_box *)ctx->args;

            ImGui::DragInt("current_item", &args->current_item);
            ImGui::InputTexts("items", args->items);
            ImGui::DragInt("height_in_items", &args->height_in_items);
        }
        break;
        case widget_type::widget_type_collapsing_header:
        {
            widget_collapsing_header *args = (widget_collapsing_header *)ctx->args;

            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_separator:
        break;
        case widget_type::widget_type_same_line:
        {
            widget_same_line *args = (widget_same_line *)ctx->args;

            ImGui::DragFloat("offset_from_start_x", &args->offset_from_start_x);
            ImGui::DragFloat("spacing", &args->spacing);
        }
        case widget_type::widget_type_spacing:
        break;
        case widget_type::widget_type_dummy:
        {
            widget_dummy *args = (widget_dummy *)ctx->args;

            ImGui::DragFloat2("size", &args->size.x);
        }
        break;
        case widget_type::widget_type_indent:
        {
            widget_indent *args = (widget_indent *)ctx->args;

            ImGui::DragFloat("indent_w", &args->indent_w);
        }
        break;
        case widget_type::widget_type_unindent:
        {
            widget_unindent *args = (widget_unindent *)ctx->args;

            ImGui::DragFloat("indent_w", &args->indent_w);
        }
        break;
        case widget_type::widget_type_begin_end_window:
        {
            widget_begin_end_window *args = (widget_begin_end_window *)ctx->args;

            ImGui::Checkbox("open", &args->open);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_begin_end_child:
        {
            widget_begin_end_child *args = (widget_begin_end_child *)ctx->args;

            ImGui::DragFloat2("size", &args->size.x);
            ImGui::Checkbox("border", &args->border);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_begin_end_popup:
        {
            widget_begin_end_popup *args = (widget_begin_end_popup *)ctx->args;

            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_begin_end_list_box:
        {
            widget_begin_end_list_box *args = (widget_begin_end_list_box *)ctx->args;

            ImGui::DragFloat2("size", &args->size.x);
                   
            ImGui::DragInt("items_count", &args->items_count);
            ImGui::DragInt("items_height", &args->items_height);
        }
        break;        
        case widget_type::widget_type_begin_end_table:
        {
            widget_begin_end_table *args = (widget_begin_end_table *)ctx->args;

            ImGui::DragInt("columns", &args->columns);
            ImGui::Combo("flags", &args->flags);
            ImGui::DragFloat2("outer_size", &args->outer_size.x);
            ImGui::DragFloat("inner_width", &args->inner_width);
        }
        break;
        case widget_type::widget_type_begin_end_group:
        break;
        case widget_type::widget_type_begin_end_combo:
        {
            widget_begin_end_combo *args = (widget_begin_end_combo *)ctx->args;
    
            ImGui::InputText("preview_value", &args->preview_value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_begin_end_menu:
        {
            widget_begin_end_menu *args = (widget_begin_end_menu *)ctx->args;

            ImGui::Checkbox("enabled", &args->enabled);
        }
        break;
		default:
			debug_break();
            break;
        }
    }
}