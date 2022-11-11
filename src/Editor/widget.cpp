#include "Precompiled.h"

#include "Editor/widget.h"
#include "Editor/selection.h"
#include "Editor/history.h"

namespace ie
{
struct widget_button
{
    
};
void draw_widget_button(widget* c)
{
    widget_button* button= (widget_button*)c->context;
    
    ImGui::Button(c->label.c_str());
    if(ImGui::IsItemClicked(ImGuiMouseButton_Left))
    {
        selection::select(c);
    }
}
void draw_widget(widget* ctx)
{    
    switch (ctx->type)
    {
        default:
        case widget_type::widget_type_button:
            ImGui::Button(ctx->label.c_str());
            ImGui::SameLine();
            ImGui::Text("Child %u", ctx->children.size());
            if(ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                selection::select(ctx);
            }
            break;
    }
    
    for(size_t i =0, max = ctx->children.size(); i < max;++i)
    {
        ImGui::PushID(i);
        draw_widget(ctx->children[i]);
        ImGui::PopID();
    }
}

widget* new_widget(widget_type type)
{
    auto w = new widget();
    w->type = type;
    switch (type)
    {
        case widget_type::widget_type_none:
        case widget_type::widget_type_window:
            
        case widget_type::widget_type_button:
        {
            w->context = new widget_button();
        }
        case widget_type::widget_type_checkbox:
        case widget_type::widget_type_radioButton:
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
    ctx->index = ctx->parent->children.size()-1;
}

void command_attach_child_deconst(void* ctx)
{
    command_attach_child* cmd = (command_attach_child*)ctx;
    delete cmd;
}

void attach_child(widget* parent, widget* child)
{
    //    ie::command* cmd = new ie::command();
    //    cmd->label = "attach child";
    //
    //    command_attach_child* ctx = new command_attach_child();
    //
    //    ctx->parent = parent;
    //    ctx->child = child;
    //
    //    cmd->context = ctx;
    //    cmd->undo = command_attach_child_undo;
    //    cmd->redo = command_attach_child_redo;
    //    cmd->deconst = command_attach_child_deconst;
    //
    //    commit(cmd);
    
    parent->children.push_back(child);
}
}
