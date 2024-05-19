#include "Precompiled.h"

#include "editor/extension.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"

BEGIN_NS_IMGUI_EDITOR

template<typename ... Args>
void insert_variant(std::string& result, size_t& index, const std::string& format, Args ... args)
{
    const std::string variant = string_format(format, args ...);
    result = result.insert(index, variant);
    index += variant.size();
}

void widget_generate(generate_code code, widget* ctx, bool root, std::string& result)
{
    static size_t index = 0;
    if (root) index = 0;

    static std::string indent = "";

    switch (code)
    {
    case generate_code::cpp:
    {
        bool begin_type = false;

        for (size_t i = 0, max = ctx->style_colors.size(); i < max; ++i)
        {
            result += indent + "ImGui::PushStyleColor(" + std::string(magic_enum::enum_name(ctx->style_colors[i].idx)) +
                ", ImVec4(" +
                std::to_string(ctx->style_colors[i].col.Value.x) + "f, " +
                std::to_string(ctx->style_colors[i].col.Value.y) + "f, " +
                std::to_string(ctx->style_colors[i].col.Value.z) + "f, " +
                std::to_string(ctx->style_colors[i].col.Value.w) + "f));\n";
        }

        for (size_t i = 0, max = ctx->style_var_floats.size(); i < max; ++i)
        {
            result += indent + "ImGui::PushStyleVar(" + std::string(magic_enum::enum_name(ctx->style_var_floats[i].idx)) +
                ", " + std::to_string(ctx->style_var_floats[i].val) + "f);\n";
        }

        for (size_t i = 0, max = ctx->style_var_vec2s.size(); i < max; ++i)
        {
            result += indent + "ImGui::PushStyleVar(" + std::string(magic_enum::enum_name(ctx->style_var_vec2s[i].idx)) +
                ", ImVec2(" +
                std::to_string(ctx->style_var_vec2s[i].val.x) + "f, " +
                std::to_string(ctx->style_var_vec2s[i].val.y) + "f));\n";
        }


        // args
        // variants
        // draws

        switch (ctx->type)
        {
        case widget_type::widget_type_none:              break;

#pragma region // Windows
        case widget_type::widget_type_begin_end_window:
        {
            begin_type = true;
            widget_begin_end_window* args = (widget_begin_end_window*)ctx->args;

            insert_variant(result, index, "bool open_%s = %s;\n", ctx->string_id.c_str(), args->open ? "true" : "false");

            result += indent + string_format("open_%s = ImGui::Begin(\"%s\", &open_%s, (ImGuiWindowFlags_)%d);\n",
                ctx->string_id.c_str(),
                ctx->label.c_str(),
                ctx->string_id.c_str(),
                (int)args->flags);

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            indent.pop_back();
            result += indent + "}\n";
            result += indent + string_format("ImGui::End();\n");
        }
        break;
        case widget_type::widget_type_begin_end_child:
        {
            begin_type = true;

            widget_begin_end_child* args = (widget_begin_end_child*)ctx->args;

            insert_variant(result, index, "bool visible_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("visible_%s = ImGui::BeginChild(\"%s\", ImVec2(%f, %f), %s, (ImGuiWindowFlags_)%d);\n",
                ctx->string_id.c_str(),
                ctx->label.c_str(),
                args->size.x,
                args->size.y,
                args->border ? "true" : "false",
                (int)args->flags);

            result += indent + string_format("if(visible_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            indent.pop_back();
            result += indent + "}\n";
            result += indent + string_format("ImGui::EndChild();\n");
        }
        break;
#pragma endregion // Windows

#pragma region // Window manipulation
        case widget_type::widget_type_set_next_window_pos:
        {
            widget_set_next_window_pos* args = (widget_set_next_window_pos*)ctx->args;

            result += indent + string_format("ImGui::SetNextWindowPos(ImVec2(%f, %f), (ImGuiCond_)%d);\n",
                args->pos.x,
                args->pos.y,
                (int)args->cond);
        }
        break;
        case widget_type::widget_type_set_next_window_size:
        {
            widget_set_next_window_size* args = (widget_set_next_window_size*)ctx->args;

            result += indent + string_format("ImGui::SetNextWindowSize(ImVec2(%f, %f), (ImGuiCond_)%d);\n",
                args->size.x,
                args->size.y,
                (int)args->cond);
        }
        break;
        case widget_type::widget_type_set_next_window_content_size:
        {
            widget_set_next_window_content_size* args = (widget_set_next_window_content_size*)ctx->args;

            result += indent + string_format("ImGui::SetNextWindowContentSize(ImVec2(%f, %f));\n",
                args->size.x,
                args->size.y);
        }
        break;
        case widget_type::widget_type_set_next_window_collapsed:
        {
            widget_set_next_window_collapsed* args = (widget_set_next_window_collapsed*)ctx->args;

            result += indent + string_format("ImGui::SetNextWindowCollapsed(%s, (ImGuiCond_)%d);\n",
                args->collapsed ? "true" : "false",
                (int)args->cond);
        }
        break;
        case widget_type::widget_type_set_next_window_focus:
        {
            widget_set_next_window_focus* args = (widget_set_next_window_focus*)ctx->args;

            result += indent + string_format("ImGui::SetNextWindowFocus();\n");
        }
        break;
        case widget_type::widget_type_set_next_window_bg_alpha:
        {
            widget_set_next_window_bg_alpha* args = (widget_set_next_window_bg_alpha*)ctx->args;

            result += indent + string_format("ImGui::SetNextWindowBgAlpha(%f);\n",
                args->alpha);
        }
        break;
#pragma endregion // Window manipulation

#pragma region // Parameters stacks (current window)
        case widget_type::widget_type_push_pop_item_width:
        {
            begin_type = true;

            widget_push_pop_item_width* args = (widget_push_pop_item_width*)ctx->args;

            result += indent + string_format("ImGui::PushItemWidth(%f);\n", args->item_width);
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::PopItemWidth();\n");
        }
        break;
        case widget_type::widget_type_push_pop_text_wrap_pos:
        {
            begin_type = true;

            widget_push_pop_text_wrap_pos* args = (widget_push_pop_text_wrap_pos*)ctx->args;

            result += indent + string_format("ImGui::PushTextWrapPos(%f);\n", args->item_width);
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::PopTextWrapPos();\n");
        }
        break;
#pragma endregion // Parameters stacks (current window)

#pragma region // Cursor / Layout
        case widget_type::widget_type_separator:
        {
            result += indent + string_format("ImGui::Separator();\n");
        }
        break;
        case widget_type::widget_type_same_line:
        {
            widget_same_line* args = (widget_same_line*)ctx->args;

            result += indent + string_format("ImGui::SameLine(%f, %f);\n", args->offset_from_start_x, args->spacing);
        }
        break;
        case widget_type::widget_type_spacing:
        {
            result += indent + string_format("ImGui::Spacing();\n");
        }
        break;
        case widget_type::widget_type_dummy:
        {
            widget_dummy* args = (widget_dummy*)ctx->args;

            result += indent + string_format("ImGui::Dummy(ImVec2(%f, %f));\n", args->size.x, args->size.y);
        }
        break;
        case widget_type::widget_type_indent:
        {
            result += indent + string_format("ImGui::Indent();\n");
        }
        break;
        case widget_type::widget_type_unindent:
        {
            result += indent + string_format("ImGui::Unindent();\n");
        }
        break;
        case widget_type::widget_type_begin_end_group:
        {
            begin_type = true;

            result += indent + string_format("ImGui::BeginGroup();\n");
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + "ImGui::EndGroup();\n";
        }
        break;
        case widget_type::widget_type_set_cursor_pos:
        {
            widget_set_cursor_pos* args = (widget_set_cursor_pos*)ctx->args;

            result += indent + string_format("ImGui::SetCursorPos(ImVec2(%f, %f));\n", args->local_pos.x, args->local_pos.y);
        }
        break;
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
        case widget_type::widget_type_text:
        {
            result += indent + string_format("ImGui::Text(\"%s\");\n", ctx->label.c_str());
        }
        break;
        case widget_type::widget_type_text_colored:
        {
            widget_text_colored* args = (widget_text_colored*)ctx->args;

            result += indent + string_format("ImGui::TextColored(ImVec4(%f, %f, %f, %f), \"%s\");\n",
                args->color.Value.x, args->color.Value.y, args->color.Value.z, args->color.Value.w, ctx->label.c_str());
        }
        break;
        case widget_type::widget_type_label_text:
        {
            widget_label_text* args = (widget_label_text*)ctx->args;

            result += indent + string_format("ImGui::LabelText(\"%s\", \"%s\");\n", ctx->label.c_str(), args->text.c_str());
        }
        break;
        case widget_type::widget_type_bullet_text:
        {
            result += indent + string_format("ImGui::BulletText(\"%s\");\n", ctx->label.c_str());
        }
        break;
#pragma endregion // Widgets: Text

#pragma region // Widgets: Main
        case widget_type::widget_type_button:
        {
            widget_button* args = (widget_button*)ctx->args;

            insert_variant(result, index, "bool pressed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("pressed_%s = ImGui::Button(\"%s\", ImVec2(%f, %f));\n", ctx->string_id.c_str(), ctx->label.c_str(),
                args->size.x, args->size.y);
        }
        break;
        case widget_type::widget_type_small_button:
        {
            insert_variant(result, index, "bool pressed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("pressed_%s = ImGui::SmallButton(\"%s\");\n", ctx->string_id.c_str(), ctx->label.c_str());
        }
        break;
        case widget_type::widget_type_checkbox:
        {
            widget_checkbox* args = (widget_checkbox*)ctx->args;

            insert_variant(result, index, "bool check_%s = %s;\n", ctx->string_id.c_str(), args->check ? "true" : "false");
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::Checkbox(\"%s\", &check_%s);\n", ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str());
        }
        break;
        case widget_type::widget_type_checkbox_flags:
        {
            widget_checkbox_flags* args = (widget_checkbox_flags*)ctx->args;

            insert_variant(result, index, "int flags_%s = %d;\n", ctx->string_id.c_str(), args->flags);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::CheckboxFlags(\"%s\", &flags_%s, %d);\n", ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->flags_value);
        }
        break;
        case widget_type::widget_type_radio_button:
        {
            widget_radio_button* args = (widget_radio_button*)ctx->args;

            insert_variant(result, index, "int active_%s = %d;\n", ctx->string_id.c_str(), args->active);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("pressed_%s = ImGui::RadioButton(\"%s\", &active_%s);\n", ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str());
        }
        break;
        case widget_type::widget_type_bullet:
        {
            result += indent + string_format("ImGui::Bullet();\n");
        }
        break;
#pragma endregion // Widgets: Main

#pragma region // Widgets: Combo Box
        case widget_type::widget_type_begin_end_combo:
        {
            begin_type = true;

            widget_begin_end_combo* args = (widget_begin_end_combo*)ctx->args;

            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::BeginCombo(\"%s\", \"%s\", (ImGuiComboFlags_)%d);\n",
                ctx->string_id.c_str(),
                ctx->label.c_str(),
                args->preview_value.c_str(),
                (int)args->flags);

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::EndCombo();\n");
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
#pragma endregion // Widgets: Combo Box

#pragma region // Widgets: Drag Sliders
        case widget_type::widget_type_drag_float:
        {
            widget_drag_float* args = (widget_drag_float*)ctx->args;

            insert_variant(result, index, "float value_%s = %f;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragFloat(\"%s\", &value_%s, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_drag_float2:
        {
            widget_drag_float2* args = (widget_drag_float2*)ctx->args;

            insert_variant(result, index, "float value_%s[2] = {%f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragFloat2(\"%s\", value_%s, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_drag_float3:
        {
            widget_drag_float3* args = (widget_drag_float3*)ctx->args;

            insert_variant(result, index, "float value_%s[3] = {%f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragFloat3(\"%s\", value_%s, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_drag_float4:
        {
            widget_drag_float4* args = (widget_drag_float4*)ctx->args;

            insert_variant(result, index, "float value_%s[4] = {%f, %f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragFloat4(\"%s\", value_%s, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_drag_int:
        {
            widget_drag_int* args = (widget_drag_int*)ctx->args;

            insert_variant(result, index, "int value_%s = %d;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragInt(\"%s\", &value_%s, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_drag_int2:
        {
            widget_drag_int2* args = (widget_drag_int2*)ctx->args;

            insert_variant(result, index, "int value_%s[2] = {%d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragInt2(\"%s\", value_%s, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_drag_int3:
        {
            widget_drag_int3* args = (widget_drag_int3*)ctx->args;

            insert_variant(result, index, "int value_%s[3] = {%d, %d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragInt3(\"%s\", value_%s, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_drag_int4:
        {
            widget_drag_int4* args = (widget_drag_int4*)ctx->args;

            insert_variant(result, index, "int value_%s[4] = {%d, %d, %d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::DragInt4(\"%s\", value_%s, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
        case widget_type::widget_type_slider_float:
        {
            widget_slider_float* args = (widget_slider_float*)ctx->args;

            insert_variant(result, index, "float value_%s = %f;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderFloat(\"%s\", &value_%s, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_float2:
        {
            widget_slider_float2* args = (widget_slider_float2*)ctx->args;

            insert_variant(result, index, "float value_%s[2] = {%f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderFloat2(\"%s\", value_%s, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_float3:
        {
            widget_slider_float3* args = (widget_slider_float3*)ctx->args;

            insert_variant(result, index, "float value_%s[3] = {%f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderFloat3(\"%s\", value_%s, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_float4:
        {
            widget_slider_float4* args = (widget_slider_float4*)ctx->args;

            insert_variant(result, index, "float value_%s[4] = {%f, %f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderFloat4(\"%s\", value_%s, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_angle:
        {
            widget_slider_angle* args = (widget_slider_angle*)ctx->args;

            insert_variant(result, index, "float value_%s = %f;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderAngle(\"%s\", &value_%s, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_int:
        {
            widget_slider_int* args = (widget_slider_int*)ctx->args;

            insert_variant(result, index, "int value_%s = %d;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderInt(\"%s\", &value_%s, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_int2:
        {
            widget_slider_int2* args = (widget_slider_int2*)ctx->args;

            insert_variant(result, index, "int value_%s[2] = {%d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderInt2(\"%s\", value_%s, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_int3:
        {
            widget_slider_int3* args = (widget_slider_int3*)ctx->args;

            insert_variant(result, index, "int value_%s[3] = {%d, %d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderInt3(\"%s\", value_%s, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_slider_int4:
        {
            widget_slider_int4* args = (widget_slider_int4*)ctx->args;

            insert_variant(result, index, "int value_%s[4] = {%d, %d, %d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::SliderInt4(\"%s\", value_%s, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->min, args->max, args->format.c_str(), (int)args->flags);
        }
        break;
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
        case widget_type::widget_type_input_text:
        {
            widget_input_text* args = (widget_input_text*)ctx->args;

            insert_variant(result, index, "std::string text_%s = \"%s\";\n", ctx->string_id.c_str(), args->text.c_str());
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputText(\"%s\", &text_%s, (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_text_multiline:
        {
            widget_input_text_multiline* args = (widget_input_text_multiline*)ctx->args;

            insert_variant(result, index, "std::string text_%s = \"%s\";\n", ctx->string_id.c_str(), args->text.c_str());
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputTextMultiline(\"%s\", &text_%s, ImVec2(%f, %f), (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->size.x, args->size.y, (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_text_with_hint:
        {
            widget_input_text_with_hint* args = (widget_input_text_with_hint*)ctx->args;

            insert_variant(result, index, "std::string text_%s = \"%s\";\n", ctx->string_id.c_str(), args->text.c_str());
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputTextWithHint(\"%s\", \"%s\", &text_%s, (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), args->hint.c_str(), ctx->string_id.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_float:
        {
            widget_input_float* args = (widget_input_float*)ctx->args;

            insert_variant(result, index, "float value_%s = %f;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputFloat(\"%s\", &value_%s, %f, %f, \"%s\", (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->step, args->step_fast, args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_float2:
        {
            widget_input_float2* args = (widget_input_float2*)ctx->args;

            insert_variant(result, index, "float value_%s[2] = {%f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputFloat2(\"%s\", value_%s, \"%s\", (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_float3:
        {
            widget_input_float3* args = (widget_input_float3*)ctx->args;

            insert_variant(result, index, "float value_%s[3] = {%f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputFloat3(\"%s\", value_%s, \"%s\", (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_float4:
        {
            widget_input_float4* args = (widget_input_float4*)ctx->args;

            insert_variant(result, index, "float value_%s[4] = {%f, %f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputFloat4(\"%s\", value_%s, \"%s\", (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->format.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_int:
        {
            widget_input_int* args = (widget_input_int*)ctx->args;

            insert_variant(result, index, "int value_%s = %d;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputInt(\"%s\", &value_%s, %d, %d, (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->step, args->step_fast, (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_int2:
        {
            widget_input_int2* args = (widget_input_int2*)ctx->args;

            insert_variant(result, index, "int value_%s[2] = {%d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputInt2(\"%s\", value_%s, (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_int3:
        {
            widget_input_int3* args = (widget_input_int3*)ctx->args;

            insert_variant(result, index, "int value_%s[3] = {%d, %d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputInt3(\"%s\", value_%s, (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_int4:
        {
            widget_input_int4* args = (widget_input_int4*)ctx->args;

            insert_variant(result, index, "int value_%s[4] = {%d, %d, %d, %d};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputInt4(\"%s\", value_%s, (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), (int)args->flags);
        }
        break;
        case widget_type::widget_type_input_double:
        {
            widget_input_double* args = (widget_input_double*)ctx->args;

            result += indent + string_format("double value_%s = %f;\n", ctx->string_id.c_str(), args->value);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::InputDouble(\"%s\", &value_%s, %f, %f, \"%s\", (ImGuiInputTextFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->step, args->step_fast, args->format.c_str(), (int)args->flags);
        }
        break;
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
        case widget_type::widget_type_color_edit3:
        {
            widget_color_edit3* args = (widget_color_edit3*)ctx->args;

            insert_variant(result, index, "float value_%s[3] = {%f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::ColorEdit3(\"%s\", value_%s, (ImGuiColorEditFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->flags);
        }
        break;
        case widget_type::widget_type_color_edit4:
        {
            widget_color_edit4* args = (widget_color_edit4*)ctx->args;

            insert_variant(result, index, "float value_%s[4] = {%f, %f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::ColorEdit4(\"%s\", value_%s, (ImGuiColorEditFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->flags);
        }
        break;
        case widget_type::widget_type_color_picker3:
        {
            widget_color_picker3* args = (widget_color_picker3*)ctx->args;

            insert_variant(result, index, "float value_%s[3] = {%f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::ColorPicker3(\"%s\", value_%s, (ImGuiColorEditFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->flags);
        }
        break;
        case widget_type::widget_type_color_picker4:
        {
            widget_color_picker4* args = (widget_color_picker4*)ctx->args;
            insert_variant(result, index, "float value_%s[4] = {%f, %f, %f, %f};\n", ctx->string_id.c_str(), args->value[0], args->value[1], args->value[2], args->value[3]);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::ColorPicker4(\"%s\", value_%s, (ImGuiColorEditFlags_)%d);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->flags);
        }
        break;
        case widget_type::widget_type_color_button:
        {
            widget_color_button* args = (widget_color_button*)ctx->args;

            insert_variant(result, index, "float value_%s[4] = {%f, %f, %f, %f};\n", ctx->string_id.c_str(), args->col.x, args->col.y, args->col.z, args->col.w);
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::ColorButton(\"%s\", ImVec4(value_%s[0], value_%s[1], value_%s[2], value_%s[3]), (ImGuiColorEditFlags_)%d, ImVec2(%f, %f));\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), ctx->string_id.c_str(), ctx->string_id.c_str(), ctx->string_id.c_str(), args->flags, args->size.x, args->size.y);
        }
        break;
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
        case widget_type::widget_type_push_pop_tree_node:
        {
            begin_type = true;

            widget_push_pop_tree_node* args = (widget_push_pop_tree_node*)ctx->args;

            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::TreeNode(\"%s\");\n",
                ctx->string_id.c_str(),
                ctx->label.c_str());

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::TreePop();\n");
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
        case widget_type::widget_type_collapsing_header:
        {
            begin_type = true;

            widget_collapsing_header* args = (widget_collapsing_header*)ctx->args;

            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::CollapsingHeader(\"%s\", %s, %s);\n", ctx->label.c_str(), args->flags ? "ImGuiTreeNodeFlags_DefaultOpen" : "0", args->flags ? "ImGuiTreeNodeFlags_DefaultOpen" : "0");

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
#pragma endregion // Widgets: Trees

#pragma region // Widgets: Selectables
        case widget_type::widget_type_selectable:
        {
            widget_selectable* args = (widget_selectable*)ctx->args;

            insert_variant(result, index, "bool selected_%s = %s;\n", ctx->string_id.c_str(), args->selected ? "true" : "false");
            insert_variant(result, index, "bool changed_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("changed_%s = ImGui::Selectable(\"%s\", &selected_%s, %s, ImVec2(%f, %f));\n",
                ctx->string_id.c_str(), ctx->label.c_str(), ctx->string_id.c_str(), args->flags ? "ImGuiSelectableFlags_AllowDoubleClick" : "0", args->size.x, args->size.y);
        }
        break;
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
        case widget_type::widget_type_begin_end_list_box:
        {
            begin_type = true;

            widget_begin_end_list_box* args = (widget_begin_end_list_box*)ctx->args;

            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::BeginListBox(\"%s\", ImVec2(%f, %f));\n",
                ctx->string_id.c_str(),
                ctx->label.c_str(),
                args->size.x,
                args->size.y);

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::EndListBox();\n");
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
#pragma endregion // Widgets: List Boxes

#pragma region // Widgets: Menus
        case widget_type::widget_type_begin_end_menu_bar:
        {
            begin_type = true;
            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::BeginMenuBar();\n",
                ctx->string_id.c_str());

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::EndMenuBar();\n");
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
        case widget_type::widget_type_begin_end_menu:
        {
            begin_type = true;
            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::BeginMenu(\"%s\");\n",
                ctx->string_id.c_str(),
                ctx->label.c_str());

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::EndMenu();\n");
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
        case widget_type::widget_type_menu_item:
        {
            widget_menu_item* args = (widget_menu_item*)ctx->args;

            insert_variant(result, index, "bool selected_%s = %s;\n", ctx->string_id.c_str(), args->selected ? "true" : "false");
            insert_variant(result, index, "bool activated_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("activated_%s = ImGui::MenuItem(\"%s\", \"%s\", &selected_%s, %s);\n",
                ctx->string_id.c_str(), ctx->label.c_str(), args->shortcut.c_str(), ctx->string_id.c_str(), args->enabled ? "true" : "false");
        }
        break;
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
        case widget_type::widget_type_begin_end_popup:
        {
            begin_type = true;

            widget_begin_end_popup* args = (widget_begin_end_popup*)ctx->args;

            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::BeginPopup(\"%s\", (ImGuiWindowFlags_)%d);\n",
                ctx->string_id.c_str(),
                ctx->label.c_str(),
                (int)args->flags);

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::EndPopup();\n");
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
#pragma endregion // Popups, Modals

#pragma region // Tables
        case widget_type::widget_type_begin_end_table:
        {
            begin_type = true;

            widget_begin_end_table* args = (widget_begin_end_table*)ctx->args;

            insert_variant(result, index, "bool open_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("open_%s = ImGui::BeginTable(\"%s\", %d, (ImGuiTableFlags_)%d, ImVec2(%f, %f), %f);\n",
                ctx->string_id.c_str(),
                ctx->label.c_str(),
                args->columns,
                (int)args->flags,
                args->outer_size.x,
                args->outer_size.y,
                args->inner_width);

            result += indent + string_format("if(open_%s)\n", ctx->string_id.c_str());
            result += indent + "{\n";
            indent += '\t';
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
            result += indent + string_format("ImGui::EndTable();\n");
            indent.pop_back();
            result += indent + "}\n";
        }
        break;
        case widget_type::widget_type_table_next_row:
        {
            widget_table_next_row* args = (widget_table_next_row*)ctx->args;

            result += indent + string_format("ImGui::TableNextRow((ImGuiTableRowFlags_)%d, %f);\n",
                (int)args->flags,
                args->min_row_height);
        }
        break;
        case widget_type::widget_type_table_next_column:
        {
            widget_table_next_column* args = (widget_table_next_column*)ctx->args;

            insert_variant(result, index, "bool visible_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("visible_%s = ImGui::TableNextColumn();\n", ctx->string_id.c_str());
        }
        break;
        case widget_type::widget_type_table_set_column_index:
        {
            widget_table_set_column_index* args = (widget_table_set_column_index*)ctx->args;

            insert_variant(result, index, "bool visible_%s = false;\n", ctx->string_id.c_str());

            result += indent + string_format("visible_%s = ImGui::TableSetColumnIndex(%d);\n", ctx->string_id.c_str(), args->column_n);
        }
        break;
#pragma endregion // Tables
#pragma region // ImGui-Editor
        case widget_type::widget_type_caller:
        {
            insert_variant(result, index, "std::function<void()> caller_%s = nullptr;\n", ctx->string_id.c_str());

            result += indent + string_format("if(caller_%s) caller_%s();\n", ctx->string_id.c_str());
        }
        break;
#pragma endregion // ImGui-Editor

        default:
            break;
        }

        if (0 < ctx->style_var_vec2s.size())
        {
            for (size_t i = ctx->style_var_vec2s.size() - 1;; --i)
            {
                result += indent + "ImGui::PopStyleVar(); // " + ImGui::ToString(ctx->style_var_vec2s[i].idx) + "\n";
                if (0 == i) break;
            }
        }

        if (0 < ctx->style_var_floats.size())
        {
            for (size_t i = ctx->style_var_floats.size() - 1;; --i)
            {
                result += indent + "ImGui::PopStyleVar(); // " + ImGui::ToString(ctx->style_var_floats[i].idx) + "\n";
                if (0 == i) break;
            }
        }


        if (0 < ctx->style_colors.size())
        {
            for (size_t i = ctx->style_colors.size() - 1;; --i)
            {
                result += indent + "ImGui::PopStyleColor(); // " + ImGui::ToString(ctx->style_colors[i].idx) + "\n";
                if (0 == i) break;
            }
        }

        if (!begin_type)
        {
            for (size_t i = 0, max = ctx->children.size(); i < max; ++i)
            {
                widget_generate(code, ctx->children[i], false, result);
            }
        }
    }

    default:
        break;
    }
}

END_NS_IMGUI_EDITOR