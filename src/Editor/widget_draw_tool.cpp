#include "Precompiled.h"

#include "editor/widget_editor.h"
#include "editor/selection.h"
#include "editor/history.h"

extern ImVec2 g_unitSize;

namespace imgui_editor
{
    constexpr static widget_type s_addTypes[]
    {
        widget_type::widget_type_button,
        widget_type::widget_type_small_button,
        widget_type::widget_type_checkbox,
        widget_type::widget_type_checkbox_flags,
        widget_type::widget_type_radio_button,
        widget_type::widget_type_text,
        widget_type::widget_type_text_colored,
        widget_type::widget_type_bullet_text,
        widget_type::widget_type_bullet,
        widget_type::widget_type_selectable,
        widget_type::widget_type_label_text,
        widget_type::widget_type_input_text,
        widget_type::widget_type_input_text_multiline,
        widget_type::widget_type_input_text_with_hint,
        widget_type::widget_type_input_int,
        widget_type::widget_type_input_int2,
        widget_type::widget_type_input_int3,
        widget_type::widget_type_input_int4,
        widget_type::widget_type_input_float,
        widget_type::widget_type_input_float2,
        widget_type::widget_type_input_float3,
        widget_type::widget_type_input_float4,
        widget_type::widget_type_input_double,
        widget_type::widget_type_drag_int,
        widget_type::widget_type_drag_int2,
        widget_type::widget_type_drag_int3,
        widget_type::widget_type_drag_int4,		
        widget_type::widget_type_drag_float,
        widget_type::widget_type_drag_float2,
        widget_type::widget_type_drag_float3,
        widget_type::widget_type_drag_float4,
        widget_type::widget_type_slider_int,
        widget_type::widget_type_slider_int2,
        widget_type::widget_type_slider_int3,
        widget_type::widget_type_slider_int4,
        widget_type::widget_type_slider_float,
        widget_type::widget_type_slider_float2,
        widget_type::widget_type_slider_float3,
        widget_type::widget_type_slider_float4,
        widget_type::widget_type_slider_angle,
        widget_type::widget_type_color_edit3,
        widget_type::widget_type_color_edit4,
        widget_type::widget_type_color_picker3,
        widget_type::widget_type_color_picker4,
        widget_type::widget_type_color_button,
        widget_type::widget_type_collapsing_header,		
        widget_type::widget_type_separator,
        widget_type::widget_type_same_line,
        widget_type::widget_type_spacing,
        widget_type::widget_type_dummy,
        widget_type::widget_type_indent,
        widget_type::widget_type_unindent,
        widget_type::widget_type_begin_end_window,
        widget_type::widget_type_begin_end_child,
        widget_type::widget_type_begin_end_popup,
        widget_type::widget_type_begin_end_list_box,
        widget_type::widget_type_begin_end_table,
        widget_type::widget_type_begin_end_group,
        widget_type::widget_type_begin_end_combo,
        widget_type::widget_type_begin_end_menu,
        widget_type::widget_type_push_pop_tree_node,
        widget_type::widget_type_push_pop_item_width,
        widget_type::widget_type_push_pop_text_wrap_pos,
    };

    void draw_widget_tool(widget_tool *ctx)
    {
        if (ImGui::BeginChild("add widget", ImVec2(0.f, g_unitSize.y * 25), true))
        {
            if (ImGui::BeginChild("Types", ImVec2(0.f, g_unitSize.y * 20)))
            {  
                for(size_t i =0, max = sizeof(s_addTypes)/sizeof(widget_type); i < max; ++i)
                {
                    auto type = s_addTypes[i];   
                    std::string name = get_pretty_name(type);
                    if ("" != name && ImGui::Selectable(name.c_str(), type == ctx->type))
                    {
                        ctx->type = type;
                    };
                }
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
}