#include "Precompiled.h"

#include "editor/imgui_ex.h"

#include "editor/widget.h"
#include "editor/widget/args_data.h"

namespace imgui_editor
{
	std::string widget_generate(generate_code code, widget* ctx)
    {
        static std::string indent = "";
        std::string result;
        switch (code)        
        {
        case generate_code::cpp:
        {
		    bool begin_type = false;

            for(size_t i = 0, max = ctx->style_colors.size(); i < max;++i)
            {
                result += indent + "ImGui::PushStyleColor(" + std::string(magic_enum::enum_name( ctx->style_colors[i].idx)) +
                 ", ImVec4(" + 
                 std::to_string(ctx->style_colors[i].col.Value.x) + "f, " +
                 std::to_string(ctx->style_colors[i].col.Value.y) + "f, " + 
                 std::to_string(ctx->style_colors[i].col.Value.z) + "f, " +
                  std::to_string(ctx->style_colors[i].col.Value.w) + "f));\n";
            }

            for(size_t i = 0, max = ctx->style_var_floats.size(); i < max;++i)
            {
                result += indent + "ImGui::PushStyleVar(" + std::string(magic_enum::enum_name( ctx->style_var_floats[i].idx)) +
                 ", " + std::to_string(ctx->style_var_floats[i].val) + "f);\n";
            }

            for(size_t i = 0, max = ctx->style_var_vec2s.size(); i < max;++i)
            {
                result += indent + "ImGui::PushStyleVar(" + std::string(magic_enum::enum_name( ctx->style_var_vec2s[i].idx)) +
                 ", ImVec2(" + 
                 std::to_string(ctx->style_var_vec2s[i].val.x) + "f, " +
                 std::to_string(ctx->style_var_vec2s[i].val.y) + "f));\n";
            }

            switch (ctx->type)
            {
            case widget_type::widget_type_none:              break; 

#pragma region // Windows
		    case widget_type::widget_type_begin_end_window:
            {
                begin_type = true;

                widget_begin_end_window* args = (widget_begin_end_window*)ctx->args;
                result += indent + string_format("bool open_%zu = %s;\n", ctx->id, args->open?"true":"false");
                result += indent + string_format("open_%zu = ImGui::Begin(\"%s\", &open_%zu, (ImGuiWindowFlags_)%d);\n",
                    ctx->id,
                    ctx->label.c_str(),
                    ctx->id,
                    (int)args->flags);
                
                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";
                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
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

                result += indent + string_format("bool open_%zu =ImGui::BeginChild(\"%s\", ImVec2(%f, %f), %s, (ImGuiWindowFlags_)%d);\n",
                    ctx->id,
                    ctx->label.c_str(),
                    ctx->size.x,
                    ctx->size.y,
                    args->border?"true":"false",
                    (int)args->flags);

                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";
                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }
                indent.pop_back();
                result += indent + "}\n";

                result += indent + string_format("ImGui::EndChild();\n");
            }
            break;
#pragma endregion // Windows

#pragma region // Parameters stacks (current window)
            case widget_type::widget_type_push_pop_item_width:
            {
                begin_type = true;
                widget_push_pop_item_width* args = (widget_push_pop_item_width*)ctx->args;
                result += indent + string_format("ImGui::PushItemWidth(%f);\n", args->item_width);

                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }

                result += indent + string_format("ImGui::PopItemWidth();\n");
            }
            break;
            case widget_type::widget_type_push_pop_text_wrap_pos:
            {
                begin_type = true;
                widget_push_pop_text_wrap_pos* args = (widget_push_pop_text_wrap_pos*)ctx->args;
                result += indent + string_format("ImGui::PushTextWrapPos(%f);\n", args->item_width);

                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
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
                result += indent + string_format("ImGui::Dummy(ImVec2(%f, %f));\n", ctx->size.x, ctx->size.y);
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
                result += indent + string_format("ImGui::BeginGroup();\n");

                begin_type = true;

                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }
                
                result += indent + "ImGui::EndGroup();\n";
            }
            break;
#pragma endregion // Cursor / Layout

#pragma region // Widgets: Text
            case widget_type::widget_type_text:
            {
                result += indent +string_format("ImGui::Text(\"%s\");\n", ctx->label.c_str());
            }
            break;
            case widget_type::widget_type_text_colored:
            {
                widget_text_colored* args = (widget_text_colored*)ctx->args;
                result += indent +string_format("ImGui::TextColored(ImVec4(%f, %f, %f, %f), \"%s\");\n", args->color.Value.x, args->color.Value.y, args->color.Value.z, args->color.Value.w, ctx->label.c_str());
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
                result += indent + string_format("ImGui::Button(\"%s\", ImVec2(%f, %f));\n", ctx->label.c_str(), ctx->size.x, ctx->size.y);
            }
            break;
            case widget_type::widget_type_small_button:
            {
                result += indent + string_format("ImGui::SmallButton(\"%s\");\n", ctx->label.c_str());
            }
            case widget_type::widget_type_checkbox:
            {
		    	widget_checkbox* args = (widget_checkbox*)ctx->args;
                result += indent + string_format("bool check_%zu = %s;\n", ctx->id, args->check?"true":"false");
                result += indent + string_format("ImGui::Checkbox(\"%s\", &check_%zu);\n", ctx->label.c_str(), ctx->id);
            }
            break;
		    case widget_type::widget_type_checkbox_flags:
            {
                widget_checkbox_flags* args = (widget_checkbox_flags*)ctx->args;
                result += indent +string_format("int flags_%zu = %d;\n", ctx->id, args->flags);
                result += indent +string_format("ImGui::CheckboxFlags(\"%s\", &flags_%zu, %d);\n", ctx->label.c_str(), ctx->id, args->flags_value);
            }
            break;
            case widget_type::widget_type_radio_button:
            {
                widget_radio_button* args = (widget_radio_button*)ctx->args;
                result += indent +string_format("int active_%zu = %d;\n", ctx->id, args->active);
                result += indent +string_format("ImGui::RadioButton(\"%s\", &active_%zu);\n", ctx->label.c_str(), ctx->id);
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
                widget_begin_end_combo* args = (widget_begin_end_combo*)ctx->args;

                result += indent + string_format("bool open_%zu =ImGui::BeginCombo(\"%s\", \"%s\", (ImGuiComboFlags_)%d);\n",
                    ctx->id,
                    ctx->label.c_str(),
                    args->preview_value.c_str(),
                    (int)args->flags);

                begin_type = true;

                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";

                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
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
                result += indent + string_format("float value_%zu = %f;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::DragFloat(\"%s\", &value_%zu, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_drag_float2:
            {
                widget_drag_float2* args = (widget_drag_float2*)ctx->args;
                result += indent + string_format("float value_%zu[2] = {%f, %f};\n", ctx->id, args->value[0], args->value[1]);
                result += indent + string_format("ImGui::DragFloat2(\"%s\", value_%zu, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_drag_float3:
            {
                widget_drag_float3* args = (widget_drag_float3*)ctx->args;
                result += indent + string_format("float value_%zu[3] = {%f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::DragFloat3(\"%s\", value_%zu, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_drag_float4:
            {
                widget_drag_float4* args = (widget_drag_float4*)ctx->args;
                result += indent + string_format("float value_%zu[4] = {%f, %f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::DragFloat4(\"%s\", value_%zu, %f, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_drag_int:
            {
                widget_drag_int* args = (widget_drag_int*)ctx->args;
                result += indent + string_format("int value_%zu = %d;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::DragInt(\"%s\", &value_%zu, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_drag_int2:
            {
                widget_drag_int2* args = (widget_drag_int2*)ctx->args;
                result += indent + string_format("int value_%zu[2] = {%d, %d};\n", ctx->id, args->value[0], args->value[1]);
                result += indent + string_format("ImGui::DragInt2(\"%s\", value_%zu, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_drag_int3:
            {
                widget_drag_int3* args = (widget_drag_int3*)ctx->args;
                result += indent + string_format("int value_%zu[3] = {%d, %d, %d};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::DragInt3(\"%s\", value_%zu, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_drag_int4:
            {
                widget_drag_int4* args = (widget_drag_int4*)ctx->args;
                result += indent + string_format("int value_%zu[4] = {%d, %d, %d, %d};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::DragInt4(\"%s\", value_%zu, %f, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->speed, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
#pragma endregion // Widgets: Drag Sliders

#pragma region // Widgets: Regular Sliders
            case widget_type::widget_type_slider_float:
            {
                widget_slider_float* args = (widget_slider_float*)ctx->args;
                result += indent + string_format("float value_%zu = %f;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::SliderFloat(\"%s\", &value_%zu, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_float2:
            {
                widget_slider_float2* args = (widget_slider_float2*)ctx->args;
                result += indent + string_format("float value_%zu[2] = {%f, %f};\n", ctx->id, args->value[0], args->value[1]);
                result += indent + string_format("ImGui::SliderFloat2(\"%s\", value_%zu, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_float3:
            {
                widget_slider_float3* args = (widget_slider_float3*)ctx->args;
                result += indent + string_format("float value_%zu[3] = {%f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::SliderFloat3(\"%s\", value_%zu, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_float4:
            {
                widget_slider_float4* args = (widget_slider_float4*)ctx->args;
                result += indent + string_format("float value_%zu[4] = {%f, %f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::SliderFloat4(\"%s\", value_%zu, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_angle:
            {
                widget_slider_angle* args = (widget_slider_angle*)ctx->args;
                result += indent + string_format("float value_%zu = %f;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::SliderAngle(\"%s\", &value_%zu, %f, %f, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_int:
            {
                widget_slider_int* args = (widget_slider_int*)ctx->args;
                result += indent + string_format("int value_%zu = %d;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::SliderInt(\"%s\", &value_%zu, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_int2:
            {
                widget_slider_int2* args = (widget_slider_int2*)ctx->args;
                result += indent + string_format("int value_%zu[2] = {%d, %d};\n", ctx->id, args->value[0], args->value[1]);
                result += indent + string_format("ImGui::SliderInt2(\"%s\", value_%zu, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_int3:
            {
                widget_slider_int3* args = (widget_slider_int3*)ctx->args;
                result += indent + string_format("int value_%zu[3] = {%d, %d, %d};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::SliderInt3(\"%s\", value_%zu, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_slider_int4:
            {
                widget_slider_int4* args = (widget_slider_int4*)ctx->args;
                result += indent + string_format("int value_%zu[4] = {%d, %d, %d, %d};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::SliderInt4(\"%s\", value_%zu, %d, %d, \"%s\", (ImGuiSliderFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->min, args->max, args->format.c_str(), (int)args->flags);
            }
            break;
#pragma endregion // Widgets: Regular Sliders

#pragma region // Widgets: Input with Keyboard
            case widget_type::widget_type_input_text:
            {                
                widget_input_text* args = (widget_input_text*)ctx->args;
                result += indent + string_format("std::string text_%zu = \"%s\";\n", ctx->id, args->text.c_str());
                result += indent + string_format("ImGui::InputText(\"%s\", &text_%zu, (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, (int)args->flags);
            }
            break;
		    case widget_type::widget_type_input_text_multiline:
            {
                widget_input_text_multiline* args = (widget_input_text_multiline*)ctx->args;
                result += indent + string_format("std::string text_%zu = \"%s\";\n", ctx->id, args->text.c_str());
                result += indent + string_format("ImGui::InputTextMultiline(\"%s\", &text_%zu, ImVec2(%f, %f), (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, ctx->size.x, ctx->size.y, (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_text_with_hint: 
            {
                widget_input_text_with_hint* args = (widget_input_text_with_hint*)ctx->args;
                result += indent + string_format("std::string text_%zu = \"%s\";\n", ctx->id, args->text.c_str());
                result += indent + string_format("ImGui::InputTextWithHint(\"%s\", \"%s\", &text_%zu, (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), args->hint.c_str(), ctx->id, (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_float:
            {
                widget_input_float* args = (widget_input_float*)ctx->args;
                result += indent + string_format("float value_%zu = %f;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::InputFloat(\"%s\", &value_%zu, %f, %f, \"%s\", (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->step, args->step_fast, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_float2:
            {
                widget_input_float2* args = (widget_input_float2*)ctx->args;
                result += indent + string_format("float value_%zu[2] = {%f, %f};\n", ctx->id, args->value[0], args->value[1]);
                result += indent + string_format("ImGui::InputFloat2(\"%s\", value_%zu, \"%s\", (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_float3:
            {
                widget_input_float3* args = (widget_input_float3*)ctx->args;
                result += indent + string_format("float value_%zu[3] = {%f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::InputFloat3(\"%s\", value_%zu, \"%s\", (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_float4:
            {
                widget_input_float4* args = (widget_input_float4*)ctx->args;
                result += indent + string_format("float value_%zu[4] = {%f, %f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::InputFloat4(\"%s\", value_%zu, \"%s\", (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->format.c_str(), (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_int:
            {
                widget_input_int* args = (widget_input_int*)ctx->args;
                result += indent + string_format("int value_%zu = %d;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::InputInt(\"%s\", &value_%zu, %d, %d, (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->step, args->step_fast, (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_int2:
            {
                widget_input_int2* args = (widget_input_int2*)ctx->args;
                result += indent + string_format("int value_%zu[2] = {%d, %d};\n", ctx->id, args->value[0], args->value[1]);
                result += indent + string_format("ImGui::InputInt2(\"%s\", value_%zu, (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_int3:
            {
                widget_input_int3* args = (widget_input_int3*)ctx->args;
                result += indent + string_format("int value_%zu[3] = {%d, %d, %d};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::InputInt3(\"%s\", value_%zu, (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_int4:
            {
                widget_input_int4* args = (widget_input_int4*)ctx->args;
                result += indent + string_format("int value_%zu[4] = {%d, %d, %d, %d};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::InputInt4(\"%s\", value_%zu, (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, (int)args->flags);
            }
            break;
            case widget_type::widget_type_input_double:
            {
                widget_input_double* args = (widget_input_double*)ctx->args;
                result += indent + string_format("double value_%zu = %f;\n", ctx->id, args->value);
                result += indent + string_format("ImGui::InputDouble(\"%s\", &value_%zu, %f, %f, \"%s\", (ImGuiInputTextFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->step, args->step_fast, args->format.c_str(), (int)args->flags);
            }
            break;
#pragma endregion // Widgets: Input with Keyboard

#pragma region // Widgets: Color Editor/Picker 
            case widget_type::widget_type_color_edit3:
            {                
                widget_color_edit3* args = (widget_color_edit3*)ctx->args;
                result += indent + string_format("float value_%zu[3] = {%f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::ColorEdit3(\"%s\", value_%zu, (ImGuiColorEditFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->flags);
            }
            break;
            case widget_type::widget_type_color_edit4:
            {
                widget_color_edit4* args = (widget_color_edit4*)ctx->args;
                result += indent + string_format("float value_%zu[4] = {%f, %f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::ColorEdit4(\"%s\", value_%zu, (ImGuiColorEditFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->flags);
            }
            break;
            case widget_type::widget_type_color_picker3:
            {
                widget_color_picker3* args = (widget_color_picker3*)ctx->args;
                result += indent + string_format("float value_%zu[3] = {%f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2]);
                result += indent + string_format("ImGui::ColorPicker3(\"%s\", value_%zu, (ImGuiColorEditFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->flags);
            }
            break;
            case widget_type::widget_type_color_picker4:
            {
                widget_color_picker4* args = (widget_color_picker4*)ctx->args;
                result += indent + string_format("float value_%zu[4] = {%f, %f, %f, %f};\n", ctx->id, args->value[0], args->value[1], args->value[2], args->value[3]);
                result += indent + string_format("ImGui::ColorPicker4(\"%s\", value_%zu, (ImGuiColorEditFlags_)%d);\n", ctx->label.c_str(), ctx->id, args->flags);
            }
            break;
            case widget_type::widget_type_color_button:
            {
                widget_color_button* args = (widget_color_button*)ctx->args;
                result += indent + string_format("float value_%zu[4] = {%f, %f, %f, %f};\n", ctx->id, args->col.x, args->col.y, args->col.z, args->col.w);
                result += indent + string_format("ImGui::ColorButton(\"%s\", ImVec4(value_%zu[0], value_%zu[1], value_%zu[2], value_%zu[3]), (ImGuiColorEditFlags_)%d, ImVec2(%f, %f));\n", ctx->label.c_str(), ctx->id, ctx->id, ctx->id, ctx->id, args->flags, args->size.x, args->size.y);
            }
            break;
#pragma endregion // Widgets: Color Editor/Picker 

#pragma region // Widgets: Trees
            case widget_type::widget_type_push_pop_tree_node:
            {
                widget_push_pop_tree_node* args = (widget_push_pop_tree_node*)ctx->args;

                result += indent + string_format("bool open_%zu =ImGui::TreeNode(\"%s\");\n",
                    ctx->id,
                    ctx->label.c_str());

                begin_type = true;

                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";

                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }

                result += indent + string_format("ImGui::TreePop();\n");

                indent.pop_back();

                result += indent + "}\n";
            }
            break;
		    case widget_type::widget_type_collapsing_header:
            {
                widget_collapsing_header* args = (widget_collapsing_header*)ctx->args;
                result += indent + string_format("ImGui::CollapsingHeader(\"%s\", %s, %s);\n", ctx->label.c_str(), args->flags?"ImGuiTreeNodeFlags_DefaultOpen":"0", args->flags?"ImGuiTreeNodeFlags_DefaultOpen":"0");
            }
            break;
#pragma endregion // Widgets: Trees

#pragma region // Widgets: Selectables
		    case widget_type::widget_type_selectable:
            {
                widget_selectable* args = (widget_selectable*)ctx->args;
                result += indent + string_format("bool selected_%zu = %s;\n", ctx->id, args->selected?"true":"false");
                result += indent + string_format("ImGui::Selectable(\"%s\", &selected_%zu, %s, ImVec2(%f, %f));\n", ctx->label.c_str(), ctx->id, args->flags?"ImGuiSelectableFlags_AllowDoubleClick":"0", ctx->size.x, ctx->size.y);
            }
            break;
#pragma endregion // Widgets: Selectables

#pragma region // Widgets: List Boxes
            case widget_type::widget_type_begin_end_list_box:
            {
                widget_begin_end_list_box* args = (widget_begin_end_list_box*)ctx->args;

                result += indent + string_format("bool open_%zu =ImGui::BeginListBox(\"%s\", ImVec2(%f, %f));\n",
                    ctx->id,
                    ctx->label.c_str(),
                    ctx->size.x,
                    ctx->size.y);

                begin_type = true;

                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";

                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }

                result += indent + string_format("ImGui::EndListBox();\n");

                indent.pop_back();

                result += indent + "}\n";
            }
            break;
#pragma endregion // Widgets: List Boxes
		
#pragma region // Widgets: Menus
            case widget_type::widget_type_begin_end_menu:
            {
                result += indent + string_format("bool open_%zu =ImGui::BeginMenu(\"%s\");\n",
                    ctx->id,
                    ctx->label.c_str());

                begin_type = true;

                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";

                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }

                result += indent + string_format("ImGui::EndMenu();\n");

                indent.pop_back();

                result += indent + "}\n";
            }
            break;
#pragma endregion // Widgets: Menus

#pragma region // Popups, Modals
		    case widget_type::widget_type_begin_end_popup:
            {
                widget_begin_end_popup* args = (widget_begin_end_popup*)ctx->args;

                result += indent + string_format("bool open_%zu =ImGui::BeginPopup(\"%s\", (ImGuiWindowFlags_)%d);\n",
                    ctx->id,
                    ctx->label.c_str(),
                    (int)args->flags);

                begin_type = true;

                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";

                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
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
                widget_begin_end_table* args = (widget_begin_end_table*)ctx->args;

                result += indent + string_format("bool open_%zu =ImGui::BeginTable(\"%s\", %d, (ImGuiTableFlags_)%d, ImVec2(%f, %f), %f);\n",
                    ctx->id,
                    ctx->label.c_str(),
                    args->columns,
                    (int)args->flags,
                    ctx->size.x,
                    ctx->size.y,
                    args->inner_width);

                begin_type = true;

                result += indent + string_format("if(open_%zu)\n", ctx->id);
                result += indent + "{\n";

                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
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

                result += indent + string_format("ImGui::TableNextColumn();\n");
            }
            break;
            case widget_type::widget_type_table_set_column_index:
            {
                widget_table_set_column_index* args = (widget_table_set_column_index*)ctx->args;

                result += indent + string_format("ImGui::TableSetColumnIndex(%d);\n", args->column_n);
            }
            break;
#pragma endregion // Tables

            default:
                break;
            }

            for(size_t i = 0, max = ctx->style_var_vec2s.size(); i < max;++i)
            {
                result += indent + "ImGui::PopStyleVar();\n";
            }

            for(size_t i = 0, max = ctx->style_var_floats.size(); i < max;++i)
            {
                result += indent + "ImGui::PopStyleVar();\n";
            }
            
            for(size_t i = 0, max = ctx->style_colors.size(); i < max;++i)
            {
                result += indent + "ImGui::PopStyleColor();\n";
            }

            if(!begin_type)
            {
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }
            }
        }
        
        default:
            break;
        }

        return result;
    }
}