#include "Precompiled.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"
#include "editor/selection.h"

#include "editor/extension.h"

BEGIN_NS_IMGUI_EDITOR

extern ImVec2 g_unit_size;

// 추후 인스펙터로 프리셋을 적용할 수 있는 형태의 구조가 추가된다면 값이 변경되었음을 제대로 바깥에 전달해주어야 한다.
void draw_inspector_widget(const widget* ctx)
{
    if (nullptr == ctx->args)
    {
        ImGui::Text("ERROR");
        return;
    }

    switch (ctx->type)
    {
    case widget_type::widget_type_none:
        break;
#pragma region // Windows
    case widget_type::widget_type_begin_end_window:
    {
        widget_begin_end_window* args = static_cast<widget_begin_end_window*>(ctx->args);

        ImGui::Checkbox("open", &args->open);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_begin_end_child:
    {
        widget_begin_end_child* args = static_cast<widget_begin_end_child*>(ctx->args);

        ImGui::DragFloat2("size", &args->size.x);
        ImGui::Checkbox("border", &args->border);
        ImGui::Combo("flags", &args->flags);
    }
    break;
#pragma endregion // Windows

#pragma region // Window manipulation
    case widget_type::widget_type_set_next_window_pos:
    {
        widget_set_next_window_pos* args = static_cast<widget_set_next_window_pos*>(ctx->args);

        ImGui::DragFloat2("pos", &args->pos.x);
        ImGui::Combo("cond", &args->cond);
        ImGui::DragFloat2("pivot", &args->pivot.x);
    }
    break;
    case widget_type::widget_type_set_next_window_size:
    {
        widget_set_next_window_size* args = static_cast<widget_set_next_window_size*>(ctx->args);

        ImGui::DragFloat2("size", &args->size.x);
        ImGui::Combo("cond", &args->cond);
    }
    break;
    case widget_type::widget_type_set_next_window_content_size:
    {
        widget_set_next_window_content_size* args = static_cast<widget_set_next_window_content_size*>(ctx->args);

        ImGui::DragFloat2("size", &args->size.x);
    }
    break;
    case widget_type::widget_type_set_next_window_collapsed:
    {
        widget_set_next_window_collapsed* args = static_cast<widget_set_next_window_collapsed*>(ctx->args);

        ImGui::Checkbox("collapsed", &args->collapsed);
        ImGui::Combo("cond", &args->cond);
    }
    break;
    case widget_type::widget_type_set_next_window_focus: break;
    case widget_type::widget_type_set_next_window_bg_alpha:
    {
        widget_set_next_window_bg_alpha* args = static_cast<widget_set_next_window_bg_alpha*>(ctx->args);

        ImGui::DragFloat("alpha", &args->alpha);
    }
    break;

#pragma region // Parameters stacks (current window)
    case widget_type::widget_type_push_pop_item_width:
    {
        widget_push_pop_item_width* args = static_cast<widget_push_pop_item_width*>(ctx->args);

        ImGui::DragFloat("item_width", &args->item_width);
    }
    break;
    case widget_type::widget_type_push_pop_text_wrap_pos:
    {
        widget_push_pop_text_wrap_pos* args = static_cast<widget_push_pop_text_wrap_pos*>(ctx->args);

        ImGui::DragFloat("item_width", &args->item_width);
    }
    break;
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
    case widget_type::widget_type_separator: break;
    case widget_type::widget_type_same_line:
    {
        widget_same_line* args = static_cast<widget_same_line*>(ctx->args);

        ImGui::DragFloat("offset_from_start_x", &args->offset_from_start_x);
        ImGui::DragFloat("spacing", &args->spacing);
    }
    case widget_type::widget_type_spacing: break;
    case widget_type::widget_type_dummy:
    {
        widget_dummy* args = static_cast<widget_dummy*>(ctx->args);

        ImGui::DragFloat2("size", &args->size.x);
    }
    break;
    case widget_type::widget_type_indent:
    {
        widget_indent* args = static_cast<widget_indent*>(ctx->args);

        ImGui::DragFloat("indent_w", &args->indent_w);
    }
    break;
    case widget_type::widget_type_unindent:
    {
        widget_unindent* args = static_cast<widget_unindent*>(ctx->args);

        ImGui::DragFloat("indent_w", &args->indent_w);
    }
    break;
    case widget_type::widget_type_begin_end_group: break;
    case widget_type::widget_type_set_cursor_pos:
    {
        widget_set_cursor_pos* args = static_cast<widget_set_cursor_pos*>(ctx->args);

        ImGui::DragFloat2("local_pos", &args->local_pos.x);
    }
    break;
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
    case widget_type::widget_type_text: break;
    case widget_type::widget_type_text_colored:
    {
        widget_text_colored* args = static_cast<widget_text_colored*>(ctx->args);
        ImGui::ColorEdit4("color", &args->color.Value.x);
    }
    break;
    case widget_type::widget_type_label_text:
    {
        widget_label_text* args = static_cast<widget_label_text*>(ctx->args);
        ImGui::InputText("text", &args->text);
    }
    break;
    case widget_type::widget_type_bullet_text: break;
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
    case widget_type::widget_type_button:
    {
        widget_button* args = static_cast<widget_button*>(ctx->args);

        ImGui::DragFloat2("size", &args->size.x);
    }
    break;
    case widget_type::widget_type_small_button: break;
    case widget_type::widget_type_checkbox:
    {
        widget_checkbox* args = static_cast<widget_checkbox*>(ctx->args);

        ImGui::Checkbox("check", &args->check);
    }
    break;
    case widget_type::widget_type_checkbox_flags:
    {
        widget_checkbox_flags* args = static_cast<widget_checkbox_flags*>(ctx->args);
        ImGui::InputInt("flags", &args->flags);
        ImGui::InputInt("flags_value", &args->flags_value);
    }
    break;
    case widget_type::widget_type_radio_button:
    {
        widget_radio_button* args = static_cast<widget_radio_button*>(ctx->args);
        ImGui::Checkbox("active", &args->active);
    }
    break;
    case widget_type::widget_type_bullet: break;
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
    case widget_type::widget_type_begin_end_combo:
    {
        widget_begin_end_combo* args = static_cast<widget_begin_end_combo*>(ctx->args);

        ImGui::InputText("preview_value", &args->preview_value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
    case widget_type::widget_type_drag_float:
    {
        widget_drag_float* args = static_cast<widget_drag_float*>(ctx->args);

        ImGui::DragFloat("value", &args->value);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_drag_float2:
    {
        widget_drag_float2* args = static_cast<widget_drag_float2*>(ctx->args);

        ImGui::DragFloat2("value", args->value);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_drag_float3:
    {
        widget_drag_float3* args = static_cast<widget_drag_float3*>(ctx->args);

        ImGui::DragFloat3("value", args->value);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_drag_float4:
    {
        widget_drag_float4* args = static_cast<widget_drag_float4*>(ctx->args);

        ImGui::DragFloat4("value", args->value);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_drag_int:
    {
        widget_drag_int* args = static_cast<widget_drag_int*>(ctx->args);

        ImGui::DragInt("value", &args->value);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_drag_int2:
    {
        widget_drag_int2* args = static_cast<widget_drag_int2*>(ctx->args);

        ImGui::DragInt2("value", args->value);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_drag_int3:
    {
        widget_drag_int3* args = static_cast<widget_drag_int3*>(ctx->args);

        ImGui::DragInt3("value", args->value);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_drag_int4:
    {
        widget_drag_int4* args = static_cast<widget_drag_int4*>(ctx->args);

        ImGui::DragInt4("value", args->value);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
    case widget_type::widget_type_slider_float:
    {
        widget_slider_float* args = static_cast<widget_slider_float*>(ctx->args);

        ImGui::SliderFloat("value", &args->value, args->min, args->max);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_float2:
    {
        widget_slider_float2* args = static_cast<widget_slider_float2*>(ctx->args);

        ImGui::SliderFloat2("value", args->value, args->min, args->max);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_float3:
    {
        widget_slider_float3* args = static_cast<widget_slider_float3*>(ctx->args);

        ImGui::SliderFloat3("value", args->value, args->min, args->max);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_float4:
    {
        widget_slider_float4* args = static_cast<widget_slider_float4*>(ctx->args);

        ImGui::SliderFloat4("value", args->value, args->min, args->max);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_angle:
    {
        widget_slider_angle* args = static_cast<widget_slider_angle*>(ctx->args);

        ImGui::SliderAngle("value", &args->value, args->min, args->max);
        ImGui::DragFloat("min", &args->min);
        ImGui::DragFloat("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_int:
    {
        widget_slider_int* args = static_cast<widget_slider_int*>(ctx->args);

        ImGui::SliderInt("value", &args->value, args->min, args->max);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_int2:
    {
        widget_slider_int2* args = static_cast<widget_slider_int2*>(ctx->args);

        ImGui::SliderInt2("value", args->value, args->min, args->max);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_int3:
    {
        widget_slider_int3* args = static_cast<widget_slider_int3*>(ctx->args);

        ImGui::SliderInt3("value", args->value, args->min, args->max);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_slider_int4:
    {
        widget_slider_int4* args = static_cast<widget_slider_int4*>(ctx->args);

        ImGui::SliderInt4("value", args->value, args->min, args->max);
        ImGui::DragInt("min", &args->min);
        ImGui::DragInt("max", &args->max);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
    case widget_type::widget_type_input_text:
    {
        widget_input_text* args = static_cast<widget_input_text*>(ctx->args);

        ImGui::InputText("text", &args->text);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_text_multiline:
    {
        widget_input_text_multiline* args = static_cast<widget_input_text_multiline*>(ctx->args);

        ImGui::InputTextMultiline("text", &args->text);
        ImGui::DragFloat2("size", &args->size.x);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_text_with_hint:
    {
        widget_input_text_with_hint* args = static_cast<widget_input_text_with_hint*>(ctx->args);

        ImGui::InputText("text", &args->text);
        ImGui::InputText("hint", &args->hint);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_float:
    {
        widget_input_float* args = static_cast<widget_input_float*>(ctx->args);

        ImGui::DragFloat("value", &args->value);
        ImGui::DragFloat("step", &args->step);
        ImGui::DragFloat("step_fast", &args->step_fast);
    }
    break;
    case widget_type::widget_type_input_float2:
    {
        widget_input_float2* args = static_cast<widget_input_float2*>(ctx->args);

        ImGui::DragFloat2("value", args->value);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_float3:
    {
        widget_input_float3* args = static_cast<widget_input_float3*>(ctx->args);

        ImGui::DragFloat3("value", args->value);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_float4:
    {
        widget_input_float4* args = static_cast<widget_input_float4*>(ctx->args);

        ImGui::DragFloat4("value", args->value);
        ImGui::InputText("format", &args->format);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_int:
    {
        widget_input_int* args = static_cast<widget_input_int*>(ctx->args);

        ImGui::DragInt("value", &args->value);
        ImGui::DragInt("step", &args->step);
        ImGui::DragInt("step_fast", &args->step_fast);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_int2:
    {
        widget_input_int2* args = static_cast<widget_input_int2*>(ctx->args);

        ImGui::DragInt2("value", args->value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_int3:
    {
        widget_input_int3* args = static_cast<widget_input_int3*>(ctx->args);

        ImGui::DragInt2("value", args->value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_int4:
    {
        widget_input_int4* args = static_cast<widget_input_int4*>(ctx->args);

        ImGui::DragInt2("value", args->value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_input_double:
    {
        widget_input_double* args = static_cast<widget_input_double*>(ctx->args);

        ImGui::DragScalar("value", ImGuiDataType_Double, &args->value);
        ImGui::DragScalar("step", ImGuiDataType_Double, &args->step);
        ImGui::DragScalar("step_fast", ImGuiDataType_Double, &args->step_fast);
    }
    break;
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
    case widget_type::widget_type_color_edit3:
    {
        widget_color_edit3* args = static_cast<widget_color_edit3*>(ctx->args);

        ImGui::ColorEdit3("value", args->value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_color_edit4:
    {
        widget_color_edit4* args = static_cast<widget_color_edit4*>(ctx->args);

        ImGui::ColorEdit4("value", args->value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_color_picker3:
    {
        widget_color_picker3* args = static_cast<widget_color_picker3*>(ctx->args);

        ImGui::ColorPicker3("value", args->value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_color_picker4:
    {
        widget_color_picker4* args = static_cast<widget_color_picker4*>(ctx->args);

        ImGui::ColorPicker4("value", args->value);
        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_color_button:
    {
        widget_color_button* args = static_cast<widget_color_button*>(ctx->args);
        ImGui::DragFloat4("col", &args->col.x);
        ImGui::Combo("flags", &args->flags);
        ImGui::DragFloat2("size", &args->size.x);
    }
    break;
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
    case widget_type::widget_type_push_pop_tree_node:
    {
        widget_push_pop_tree_node* args = static_cast<widget_push_pop_tree_node*>(ctx->args);

        ImGui::Combo("flags", &args->flags);
    }
    break;
    case widget_type::widget_type_collapsing_header:
    {
        widget_collapsing_header* args = static_cast<widget_collapsing_header*>(ctx->args);

        ImGui::Combo("flags", &args->flags);
    }
    break;
#pragma endregion // Widgets: Trees


#pragma region // Widgets: Selectable
    case widget_type::widget_type_selectable:
    {
        widget_selectable* args = static_cast<widget_selectable*>(ctx->args);

        ImGui::Checkbox("selected", &args->selected);
        ImGui::Combo("flags", &args->flags);
        ImGui::DragFloat2("size", &args->size.x);
    }
    break;
#pragma endregion // Widgets: Selectable

#pragma region // Widgets: List Boxes
    case widget_type::widget_type_begin_end_list_box:
    {
        widget_begin_end_list_box* args = static_cast<widget_begin_end_list_box*>(ctx->args);

        ImGui::DragInt("items_count", &args->items_count);
        ImGui::DragInt("items_height", &args->items_height);
        ImGui::DragFloat2("size", &args->size.x);
    }
    break;
#pragma endregion // Widgets: List Boxes

#pragma region // Widgets: Menus
    case widget_type::widget_type_begin_end_menu_bar: break;
    case widget_type::widget_type_begin_end_menu:
    {
        widget_begin_end_menu* args = static_cast<widget_begin_end_menu*>(ctx->args);

        ImGui::Checkbox("enabled", &args->enabled);
    }
    break;
    case widget_type::widget_type_menu_item:
    {
        widget_menu_item* args = static_cast<widget_menu_item*>(ctx->args);

        ImGui::InputText("shortcut", &args->shortcut);
        ImGui::Checkbox("selected", &args->selected);
        ImGui::Checkbox("enabled", &args->enabled);
    }
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
    case widget_type::widget_type_begin_end_popup:
    {
        widget_begin_end_popup* args = static_cast<widget_begin_end_popup*>(ctx->args);

        ImGui::Combo("flags", &args->flags);
    }
    break;
#pragma endregion // Popups, Modals

#pragma region // Tables
    case widget_type::widget_type_begin_end_table:
    {
        widget_begin_end_table* args = static_cast<widget_begin_end_table*>(ctx->args);

        ImGui::DragInt("columns", &args->columns);
        ImGui::Combo("flags", &args->flags);
        ImGui::DragFloat2("outer_size", &args->outer_size.x);
        ImGui::DragFloat("inner_width", &args->inner_width);
    }
    break;
    case widget_type::widget_type_table_next_row:
    {
        widget_table_next_row* args = static_cast<widget_table_next_row*>(ctx->args);

        ImGui::Combo("flags", &args->flags);
        ImGui::DragFloat("min_row_height", &args->min_row_height);
    }
    break;
    case widget_type::widget_type_table_next_column: break;
    case widget_type::widget_type_table_set_column_index:
    {
        widget_table_set_column_index* args = static_cast<widget_table_set_column_index*>(ctx->args);

        ImGui::DragInt("column_n", &args->column_n);
    }
    break;
#pragma endregion // Tables

#pragma region // ImGui-Editor
    case widget_type::widget_type_caller: break;
#pragma endregion // ImGui-Editor
    default:
        debug_break();
        break;
    }
}

END_NS_IMGUI_EDITOR