#include "Precompiled.h"

#include <sstream>
#include <magic_enum/magic_enum.hpp>
#include "editor/imgui_ex.h"

#include "editor/widget.h"
#include "editor/widget_data.h"

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
                result += indent + string_format("bool check = %s;\n", args->check?"true":"false");
                result += indent + string_format("ImGui::Checkbox(\"%s\", &check);\n", ctx->label.c_str());
            }
            break;
		    case widget_type::widget_type_checkbox_flags:
            {
                widget_checkbox_flags* args = (widget_checkbox_flags*)ctx->args;
                result += indent +string_format("int flags = %d;\n", args->flags);
                result += indent +string_format("ImGui::CheckboxFlags(\"%s\", &flags, %d);\n", ctx->label.c_str(), args->flags_value);
            }
            break;
            case widget_type::widget_type_radio_button:
            {
                widget_radio_button* args = (widget_radio_button*)ctx->args;
                result += indent +string_format("int active = %d;\n", args->active);
                result += indent +string_format("ImGui::RadioButton(\"%s\", &active);\n", ctx->label.c_str());
            }
            break;
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
		    case widget_type::widget_type_bullet_text:
            {
                result += indent + string_format("ImGui::BulletText(\"%s\");\n", ctx->label.c_str());
            }
            break;
	    	case widget_type::widget_type_bullet:
            {
                result += indent + string_format("ImGui::Bullet();\n");
            }
            break;
		    case widget_type::widget_type_selectable:
            {
                widget_selectable* args = (widget_selectable*)ctx->args;
                result += indent + string_format("bool selected = %s;\n", args->selected?"true":"false");
                result += indent + string_format("ImGui::Selectable(\"%s\", &selected, (ImGuiSelectableFlags_)%d, ImVec2(%f, %f));\n",
                    ctx->label.c_str(),
                    (int)args->flags, ctx->size.x, ctx->size.y);
            }
            break;




		    case widget_type::widget_type_begin_end_window:
            {
                widget_begin_end_window* args = (widget_begin_end_window*)ctx->args;

                result += indent + string_format("bool open = ImGui::Begin(\"%s\", &%s, (ImGuiWindowFlags_)%d);\n",
                    ctx->label.c_str(),
                    args->open?"true":"false",
                    (int)args->flags);

                begin_type = true;
                
                result += indent + "if(open)\n";
                result += indent + "{\n";

                indent += '\t';
                for(size_t i =0, max = ctx->children.size(); i < max; ++i)
                {
                    result += widget_generate(code, ctx->children[i]);
                }
                indent.pop_back();

                result += indent + "}\n";
            }
            break;

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

            if(begin_type)
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