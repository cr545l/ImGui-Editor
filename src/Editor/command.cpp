#include "Precompiled.h"

#include "editor/history.h"
#include "editor/command.h"
#include "editor/widget.h"

namespace imgui_editor
{
    namespace command
    {
        namespace create_widget_command
        {
            struct data
            {
                widget* parent;
                widget_type type;
                size_t index;
            };

            void undo(void* ctx)
            {
                data* context = (data*)ctx;
                delete_widget(context->parent->children[context->index]);
                context->parent->children.erase(context->parent->children.begin() + context->index);
            }

            void redo(void* ctx)
            {
                data* context = (data*)ctx;
                widget* widget = new_widget(context->type);
                context->index = context->parent->children.size();     
                context->parent->children.push_back(widget);
                widget->parent = context->parent;
            }

            void destructor(void* ctx)
            {
                data* cmd = (data*)ctx;
                delete cmd;
            } 
        }
        
	    void create_widget(widget* parent, const widget_type& type)
        {
            imgui_editor::command_data* cmd = new imgui_editor::command_data();
            cmd->label = string_format("Create widget (%s)", get_pretty_name(type));

            create_widget_command::data* ctx = new create_widget_command::data();

            ctx->parent = parent;
            ctx->type = type;

            cmd->argument_data = ctx;
            cmd->undo = create_widget_command::undo;
            cmd->redo = create_widget_command::redo;
            cmd->destructor = create_widget_command::destructor;

            commit(cmd);
        }

        struct command_attach_child
        {
            widget* new_parent;
            widget* target;
            size_t index;

            widget* old_parent;
        };

        void command_attach_child_undo(void* _context)
        {
            command_attach_child* ctx = (command_attach_child*)_context;
            ctx->new_parent->children.erase(std::find(ctx->new_parent->children.begin(), ctx->new_parent->children.end(), ctx->target));
            if(ctx->old_parent)
            {
                ctx->old_parent->children.insert(ctx->old_parent->children.begin() + ctx->index, ctx->target);
            }
            ctx->target->parent = ctx->old_parent;
        }

        void command_attach_child_redo(void* _context)
        {
            command_attach_child* ctx = (command_attach_child*)_context;
            ctx->new_parent->children.push_back(ctx->target);
            ctx->old_parent = ctx->target->parent;
            if(ctx->old_parent)
            {
                ctx->old_parent->children.erase(std::find(ctx->old_parent->children.begin(), ctx->old_parent->children.end(), ctx->target));
            }
            ctx->target->parent = ctx->new_parent;
            ctx->index = ctx->new_parent->children.size() - 1;
        }

        void command_attach_child_destructor(void* ctx)
        {
            command_attach_child* cmd = (command_attach_child*)ctx;
            delete cmd;
        } 

        void attach_child(widget* parent, widget* child)
        {
            imgui_editor::command_data* cmd = new imgui_editor::command_data();
            cmd->label = "Attach child";

            command_attach_child* ctx = new command_attach_child();

            ctx->new_parent = parent;
            ctx->target = child;

            cmd->argument_data = ctx;
            cmd->undo = command_attach_child_undo;
            cmd->redo = command_attach_child_redo;
            cmd->destructor = command_attach_child_destructor;

            commit(cmd);
        }

        struct commamd_remove_widget
        {
            widget* parent;
            size_t index;

            std::string widget;
        };

        void command_remove_widget_undo(void* _context)
        {
            commamd_remove_widget* ctx = (commamd_remove_widget*)_context;

            widget* w = new_widget(widget_type::widget_type_none);
            widget_deserialize(w,ctx->widget.c_str());

            ctx->parent->children.insert(ctx->parent->children.begin() + ctx->index, w);
        }

        void command_remove_widget_redo(void* _context)
        {
            commamd_remove_widget* ctx = (commamd_remove_widget*)_context;
            ctx->widget = widget_serialize(ctx->parent->children[ctx->index]);
            ctx->parent->children.erase(ctx->parent->children.begin() + ctx->index);
        }

        void command_remove_widget_destructor(void* ctx)
        {
            commamd_remove_widget* cmd = (commamd_remove_widget*)ctx;
            delete cmd;
        }

        void remove_widget(widget* target)
        {
            size_t index = std::find(target->parent->children.begin(), target->parent->children.end(), target)-target->parent->children.begin();
            if(index < target->parent->children.size())
            {
                imgui_editor::command_data* cmd = new imgui_editor::command_data();
                cmd->label = "Remove widget";

                commamd_remove_widget* ctx = new commamd_remove_widget();

                ctx->parent = target->parent;
                ctx->index = index;
                ctx->widget = widget_serialize(target);

                cmd->argument_data = ctx;
                cmd->undo = command_remove_widget_undo;
                cmd->redo = command_remove_widget_redo;
                cmd->destructor = command_remove_widget_destructor;
                
                commit(cmd);
            }
            else
            {
                debug_break();
            }
        }
    }
}
