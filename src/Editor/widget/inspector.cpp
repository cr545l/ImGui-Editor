#include "Precompiled.h"

#include "editor/extension.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"
#include "editor/selection.h"

struct ImGuiStyleVarInfo
{
    ImGuiDataType   Type;
    ImU32           Count;
    ImU32           Offset;
    void*           GetVarPtr(ImGuiStyle* style) const { return (void*)((unsigned char*)style + Offset); }
};

static const ImGuiStyleVarInfo GStyleVarInfo[] =
{
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, Alpha) },               // ImGuiStyleVar_Alpha
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, DisabledAlpha) },       // ImGuiStyleVar_DisabledAlpha
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowPadding) },       // ImGuiStyleVar_WindowPadding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowRounding) },      // ImGuiStyleVar_WindowRounding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowBorderSize) },    // ImGuiStyleVar_WindowBorderSize
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowMinSize) },       // ImGuiStyleVar_WindowMinSize
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowTitleAlign) },    // ImGuiStyleVar_WindowTitleAlign
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ChildRounding) },       // ImGuiStyleVar_ChildRounding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ChildBorderSize) },     // ImGuiStyleVar_ChildBorderSize
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, PopupRounding) },       // ImGuiStyleVar_PopupRounding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, PopupBorderSize) },     // ImGuiStyleVar_PopupBorderSize
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, FramePadding) },        // ImGuiStyleVar_FramePadding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, FrameRounding) },       // ImGuiStyleVar_FrameRounding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, FrameBorderSize) },     // ImGuiStyleVar_FrameBorderSize
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, ItemSpacing) },         // ImGuiStyleVar_ItemSpacing
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, ItemInnerSpacing) },    // ImGuiStyleVar_ItemInnerSpacing
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, IndentSpacing) },       // ImGuiStyleVar_IndentSpacing
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, CellPadding) },         // ImGuiStyleVar_CellPadding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ScrollbarSize) },       // ImGuiStyleVar_ScrollbarSize
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, ScrollbarRounding) },   // ImGuiStyleVar_ScrollbarRounding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, GrabMinSize) },         // ImGuiStyleVar_GrabMinSize
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, GrabRounding) },        // ImGuiStyleVar_GrabRounding
    { ImGuiDataType_Float, 1, (ImU32)IM_OFFSETOF(ImGuiStyle, TabRounding) },         // ImGuiStyleVar_TabRounding
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, ButtonTextAlign) },     // ImGuiStyleVar_ButtonTextAlign
    { ImGuiDataType_Float, 2, (ImU32)IM_OFFSETOF(ImGuiStyle, SelectableTextAlign) }, // ImGuiStyleVar_SelectableTextAlign
};

namespace imgui_editor
{
    extern ImVec2 g_unitSize;

    void draw_inspector_widget(widget *ctx)
    {
        ImGui::Text("ID : %zu / %s", ctx->id, get_pretty_name(ctx->type));
        ImGui::InputText("label", &ctx->label);

        switch (ctx->type)
        {
        case widget_type::widget_type_none:
            break;
#pragma region // Windows
        case widget_type::widget_type_begin_end_window:
        {
            widget_begin_end_window* args = (widget_begin_end_window*)ctx->args;

            ImGui::Checkbox("open", &args->open);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_begin_end_child:
        {
            widget_begin_end_child* args = (widget_begin_end_child*)ctx->args;

            ImGui::DragFloat2("size", &args->size.x);
            ImGui::Checkbox("border", &args->border);
            ImGui::Combo("flags", &args->flags);
        }
        break;
#pragma endregion // Windows

#pragma region // Parameters stacks (current window)
        case widget_type::widget_type_push_pop_item_width:
        {
            widget_push_pop_item_width* args = (widget_push_pop_item_width*)ctx->args;

            ImGui::DragFloat("item_width", &args->item_width);
        }
        break;
        case widget_type::widget_type_push_pop_text_wrap_pos:
        {
            widget_push_pop_text_wrap_pos* args = (widget_push_pop_text_wrap_pos*)ctx->args;

            ImGui::DragFloat("item_width", &args->item_width);
        }
        break;
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
        case widget_type::widget_type_separator: break;
        case widget_type::widget_type_same_line:
        {
            widget_same_line* args = (widget_same_line*)ctx->args;

            ImGui::DragFloat("offset_from_start_x", &args->offset_from_start_x);
            ImGui::DragFloat("spacing", &args->spacing);
        }
        case widget_type::widget_type_spacing: break;
        case widget_type::widget_type_dummy: 
        {
            widget_dummy* args = (widget_dummy*)ctx->args;

            ImGui::DragFloat2("size", &args->size.x);
        }
        break;
        case widget_type::widget_type_indent:
        {
            widget_indent* args = (widget_indent*)ctx->args;

            ImGui::DragFloat("indent_w", &args->indent_w);
        }
        break;
        case widget_type::widget_type_unindent:
        {
            widget_unindent* args = (widget_unindent*)ctx->args;

            ImGui::DragFloat("indent_w", &args->indent_w);
        }
        break;
		case widget_type::widget_type_begin_end_group: break;
        case widget_type::widget_type_set_cursor_pos:
        {
            widget_set_cursor_pos* args = (widget_set_cursor_pos*)ctx->args;

            ImGui::DragFloat2("local_pos", &args->local_pos.x);
        }
        break;
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
        case widget_type::widget_type_text: break;
        case widget_type::widget_type_text_colored:
        {
            widget_text_colored* args = (widget_text_colored*)ctx->args;
            ImGui::ColorEdit4("color", &args->color.Value.x);
        }
        break;
        case widget_type::widget_type_label_text: 
        {
            widget_label_text* args = (widget_label_text*)ctx->args;
            ImGui::InputText("text", &args->text);
        }
        break;
        case widget_type::widget_type_bullet_text: break;
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
        case widget_type::widget_type_button: 
        {
            widget_button* args = (widget_button*)ctx->args;

            ImGui::DragFloat2("size", &args->size.x);
        }
        break;
        case widget_type::widget_type_small_button: break;
        case widget_type::widget_type_checkbox:
        {
            widget_checkbox* args = (widget_checkbox*)ctx->args;

            ImGui::Checkbox("check", &args->check);
        }
        break;
        case widget_type::widget_type_checkbox_flags:
        {
            widget_checkbox_flags* args = (widget_checkbox_flags*)ctx->args;
            ImGui::InputInt("flags", &args->flags);
            ImGui::InputInt("flags_value", &args->flags_value);
        }
        break;
        case widget_type::widget_type_radio_button:
        {
            widget_radio_button* args = (widget_radio_button*)ctx->args;
            ImGui::Checkbox("active", &args->active);
        }
        break;
        case widget_type::widget_type_bullet: break;
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
		case widget_type::widget_type_begin_end_combo:
		{
			widget_begin_end_combo* args = (widget_begin_end_combo*)ctx->args;

			ImGui::InputText("preview_value", &args->preview_value);
			ImGui::Combo("flags", &args->flags);
		}
		break;
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
        case widget_type::widget_type_drag_float:
        {
            widget_drag_float* args = (widget_drag_float*)ctx->args;

            ImGui::DragFloat("value", &args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_float2:
        {
            widget_drag_float2* args = (widget_drag_float2*)ctx->args;

            ImGui::DragFloat2("value", args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_float3:
        {
            widget_drag_float3* args = (widget_drag_float3*)ctx->args;

            ImGui::DragFloat3("value", args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_float4:
        {
            widget_drag_float4* args = (widget_drag_float4*)ctx->args;

            ImGui::DragFloat4("value", args->value);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_int:
        {
            widget_drag_int* args = (widget_drag_int*)ctx->args;

            ImGui::DragInt("value", &args->value);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_int2:
        {
            widget_drag_int2* args = (widget_drag_int2*)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_int3:
        {
            widget_drag_int3* args = (widget_drag_int3*)ctx->args;

            ImGui::DragInt3("value", args->value);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_drag_int4:
        {
            widget_drag_int4* args = (widget_drag_int4*)ctx->args;

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
            widget_slider_float* args = (widget_slider_float*)ctx->args;

            ImGui::SliderFloat("value", &args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_float2:
        {
            widget_slider_float2* args = (widget_slider_float2*)ctx->args;

            ImGui::SliderFloat2("value", args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_float3:
        {
            widget_slider_float3* args = (widget_slider_float3*)ctx->args;

            ImGui::SliderFloat3("value", args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_float4:
        {
            widget_slider_float4* args = (widget_slider_float4*)ctx->args;

            ImGui::SliderFloat4("value", args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_angle:
        {
	        widget_slider_angle* args = (widget_slider_angle*)ctx->args;

            ImGui::SliderAngle("value", &args->value, args->min, args->max);
            ImGui::DragFloat("min", &args->min);
            ImGui::DragFloat("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int:
        {
            widget_slider_int* args = (widget_slider_int*)ctx->args;

            ImGui::SliderInt("value", &args->value, args->min, args->max);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int2:
        {
            widget_slider_int2* args = (widget_slider_int2*)ctx->args;

            ImGui::SliderInt2("value", args->value, args->min, args->max);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int3:
        {
            widget_slider_int3* args = (widget_slider_int3*)ctx->args;

            ImGui::SliderInt3("value", args->value, args->min, args->max);
            ImGui::DragInt("min", &args->min);
            ImGui::DragInt("max", &args->max);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_slider_int4:
        {
            widget_slider_int4* args = (widget_slider_int4*)ctx->args;

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
            widget_input_text* args = (widget_input_text*)ctx->args;

            ImGui::InputText("text", &args->text);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_text_multiline:
        {
            widget_input_text_multiline* args = (widget_input_text_multiline*)ctx->args;

            ImGui::InputTextMultiline("text", &args->text);
            ImGui::DragFloat2("size", &args->size.x);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_text_with_hint:
        {
            widget_input_text_with_hint* args = (widget_input_text_with_hint*)ctx->args;

            ImGui::InputText("text", &args->text);
            ImGui::InputText("hint", &args->hint);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_float:
        {
            widget_input_float* args = (widget_input_float*)ctx->args;

            ImGui::DragFloat("value", &args->value);
            ImGui::DragFloat("step", &args->step);
            ImGui::DragFloat("step_fast", &args->step_fast);
        }
        break;
        case widget_type::widget_type_input_float2:
        {
            widget_input_float2* args = (widget_input_float2*)ctx->args;

            ImGui::DragFloat2("value", args->value);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_float3:
        {
            widget_input_float3* args = (widget_input_float3*)ctx->args;

            ImGui::DragFloat3("value", args->value);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_float4:
        {
            widget_input_float4* args = (widget_input_float4*)ctx->args;

            ImGui::DragFloat4("value", args->value);
            ImGui::InputText("format", &args->format);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int:
        {
            widget_input_int* args = (widget_input_int*)ctx->args;

            ImGui::DragInt("value", &args->value);
            ImGui::DragInt("step", &args->step);
            ImGui::DragInt("step_fast", &args->step_fast);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int2:
        {
            widget_input_int2* args = (widget_input_int2*)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int3:
        {
            widget_input_int3* args = (widget_input_int3*)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_int4:
        {
            widget_input_int4* args = (widget_input_int4*)ctx->args;

            ImGui::DragInt2("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_input_double:
        {
            widget_input_double* args = (widget_input_double*)ctx->args;

            ImGui::DragScalar("value", ImGuiDataType_Double, &args->value);
            ImGui::DragScalar("step", ImGuiDataType_Double, &args->step);
            ImGui::DragScalar("step_fast", ImGuiDataType_Double, &args->step_fast);
        }
        break;
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
        case widget_type::widget_type_color_edit3:
        {
            widget_color_edit3* args = (widget_color_edit3*)ctx->args;

            ImGui::ColorEdit3("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_edit4:
        {
            widget_color_edit4* args = (widget_color_edit4*)ctx->args;

            ImGui::ColorEdit4("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_picker3:
        {
            widget_color_picker3* args = (widget_color_picker3*)ctx->args;

            ImGui::ColorPicker3("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_picker4:
        {
            widget_color_picker4* args = (widget_color_picker4*)ctx->args;

            ImGui::ColorPicker4("value", args->value);
            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_color_button:
        {
            widget_color_button* args = (widget_color_button*)ctx->args;
            ImGui::DragFloat4("col", &args->col.x);
            ImGui::Combo("flags", &args->flags);
            ImGui::DragFloat2("size", &args->size.x);
        }
        break;
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
        case widget_type::widget_type_push_pop_tree_node:
        {
	        widget_push_pop_tree_node* args = (widget_push_pop_tree_node*)ctx->args;

            ImGui::Combo("flags", &args->flags);
        }
        break;
        case widget_type::widget_type_collapsing_header:
        {
            widget_collapsing_header* args = (widget_collapsing_header*)ctx->args;

            ImGui::Combo("flags", &args->flags);
        }
        break;
#pragma endregion // Widgets: Trees


#pragma region // Widgets: Selectables
        case widget_type::widget_type_selectable:
        {
            widget_selectable* args = (widget_selectable*)ctx->args;

            ImGui::Checkbox("selected", &args->selected);
            ImGui::Combo("flags", &args->flags);
            ImGui::DragFloat2("size", &args->size.x);
        }
        break;
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
        case widget_type::widget_type_begin_end_list_box:
        {
            widget_begin_end_list_box* args = (widget_begin_end_list_box*)ctx->args;

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
            widget_begin_end_menu* args = (widget_begin_end_menu*)ctx->args;

            ImGui::Checkbox("enabled", &args->enabled);
        }
        break;
        case widget_type::widget_type_menu_item:
        {
            widget_menu_item* args = (widget_menu_item*)ctx->args;

            ImGui::InputText("shortcut", &args->shortcut);
            ImGui::Checkbox("selected", &args->selected);
            ImGui::Checkbox("enabled", &args->enabled);
        }
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
        case widget_type::widget_type_begin_end_popup:
        {
            widget_begin_end_popup* args = (widget_begin_end_popup*)ctx->args;

            ImGui::Combo("flags", &args->flags);
        }
        break;
#pragma endregion // Popups, Modals
		
#pragma region // Tables
		case widget_type::widget_type_begin_end_table:
		{
			widget_begin_end_table* args = (widget_begin_end_table*)ctx->args;

			ImGui::DragInt("columns", &args->columns);
			ImGui::Combo("flags", &args->flags);
			ImGui::DragFloat2("outer_size", &args->outer_size.x);
			ImGui::DragFloat("inner_width", &args->inner_width);
		}
		break;
        case widget_type::widget_type_table_next_row:
        {
            widget_table_next_row* args = (widget_table_next_row*)ctx->args;

            ImGui::Combo("flags", &args->flags);
            ImGui::DragFloat("min_row_height", &args->min_row_height);
        }
        break;
        case widget_type::widget_type_table_next_column: break;
        case widget_type::widget_type_table_set_column_index:
        {
            widget_table_set_column_index* args = (widget_table_set_column_index*)ctx->args;

            ImGui::DragInt("column_n", &args->column_n);
        }
        break;
#pragma endregion // Tables
		default:
			debug_break();
            break;
        }

        ImGui::Separator();

        ImGui::PushID("style_colors");
        {
            int size =ctx->style_colors.size();
            if(ImGui::InputInt("style_colors", (int*)&size))
            {
                if (size < 0)
                {
                    size = 0;
                }

                if ((int)ctx->style_colors.size() < size)
                {
                    ctx->style_colors.push_back({});
                }
                else
                {
                    ctx->style_colors.resize(size);
                }
            }
            for(size_t i =0, max = ctx->style_colors.size(); i < max; ++i)
            {
                ImGui::PushID(i);
                ImGui::Combo(string_format("%s[%u]", "idx", i).c_str(), &ctx->style_colors[i].idx, false);
                ImGui::ColorEdit4(string_format("%s[%u]", "col", i).c_str(), &ctx->style_colors[i].col.Value.x);
                ImGui::PopID();
            }
        }        
        ImGui::PopID(); 


        ImGui::PushID("style_var_floats");
        {
            int size =ctx->style_var_floats.size();
            if(ImGui::InputInt("style_var_floats", (int*)&size))
            {
                if (size < 0)
                {
                    size = 0;
                }

                if ((int)ctx->style_var_floats.size() < size)
                {
                    ctx->style_var_floats.push_back({});
                }
                else
                {
                    ctx->style_var_floats.resize(size);
                }
            }

            for(size_t i =0, max = ctx->style_var_floats.size(); i < max; ++i)
            {
                ImGui::PushID(i);
                std::string preview = ImGui::GetEnumName(ctx->style_var_floats[i].idx, false);
                if(ImGui::BeginCombo(string_format("%s[%u]", "idx", i).c_str(), preview.c_str()))
                {
                    for(int j = 0; j < ImGuiStyleVar_COUNT; ++j)
                    {
                        if(GStyleVarInfo[j].Count == 1)
                        {
                            if(ImGui::Selectable(ImGui::GetEnumName((ImGuiStyleVar_)j,false).c_str(), ctx->style_var_floats[i].idx == j))
                            {
                                ctx->style_var_floats[i].idx = (ImGuiStyleVar_)j;
                            }
                        }
                    }
                    ImGui::EndCombo();
                }

                ImGui::DragFloat(string_format("%s[%u]", "val", i).c_str(), &ctx->style_var_floats[i].val);
                ImGui::PopID();
            }
        }      
        ImGui::PopID();
        
        ImGui::PushID("style_var_vec2s");
        {
            int size =ctx->style_var_vec2s.size();
            if(ImGui::InputInt("style_var_vec2s", (int*)&size))
            {
                if (size < 0)
                {
                    size = 0;
                }

                if ((int)ctx->style_var_vec2s.size() < size)
                {
                    ctx->style_var_vec2s.push_back({});
                }
                else
                {
                    ctx->style_var_vec2s.resize(size);
                }
            }
            for(size_t i =0, max = ctx->style_var_vec2s.size(); i < max; ++i)
            {
                ImGui::PushID(i);
                std::string preview = ImGui::GetEnumName(ctx->style_var_vec2s[i].idx, false);
                if(ImGui::BeginCombo(string_format("%s[%u]", "idx", i).c_str(), preview.c_str()))
                {
                    for(int j = 0; j < ImGuiStyleVar_COUNT; ++j)
                    {
                        if(GStyleVarInfo[j].Count == 2)
                        {
                            if(ImGui::Selectable(ImGui::GetEnumName((ImGuiStyleVar_)j,false).c_str(), ctx->style_var_vec2s[i].idx == j))
                            {
                                ctx->style_var_vec2s[i].idx = (ImGuiStyleVar_)j;
                            }
                        }
                    }
                    ImGui::EndCombo();
                }
                ImGui::DragFloat2(string_format("%s[%u]", "val", i).c_str(), &ctx->style_var_vec2s[i].val.x);
                ImGui::PopID();
            }
        }
        ImGui::PopID();
    }
}