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

                if(context->index == -1)
                {
                    context->index = context->parent->children.size();     
                    context->parent->children.push_back(widget);
                }
                else
                {
                    context->parent->children.insert(context->parent->children.begin() + context->index, widget);
                }
                widget->parent = context->parent;
            }

            void destructor(void* ctx)
            {
                data* cmd = (data*)ctx;
                delete cmd;
            } 
        }
        
	    void create_widget(widget* parent, const widget_type& type, size_t index)
        {
            imgui_editor::command_data* cmd = new imgui_editor::command_data();
            cmd->label = string_format("Create widget (%s)", get_pretty_name(type));

            create_widget_command::data* ctx = new create_widget_command::data();

            ctx->parent = parent;
            ctx->type = type;
            ctx->index = index;

            cmd->argument_data = ctx;
            cmd->undo = create_widget_command::undo;
            cmd->redo = create_widget_command::redo;
            cmd->destructor = create_widget_command::destructor;

            commit(cmd);
        }

        namespace attach_child_command
        {
            struct data
            {
                widget* new_parent;
                widget* target;
                size_t index;

                widget* old_parent;
            };

            void undo(void* _context)
            {
                data* ctx = (data*)_context;
                ctx->new_parent->children.erase(std::find(ctx->new_parent->children.begin(), ctx->new_parent->children.end(), ctx->target));
                if(ctx->old_parent)
                {
                    ctx->old_parent->children.insert(ctx->old_parent->children.begin() + ctx->index, ctx->target);
                }
                ctx->target->parent = ctx->old_parent;
            }

            void redo(void* _context)
            {
                data* ctx = (data*)_context;
                ctx->new_parent->children.push_back(ctx->target);
                ctx->old_parent = ctx->target->parent;
                if(ctx->old_parent)
                {
                    ctx->old_parent->children.erase(std::find(ctx->old_parent->children.begin(), ctx->old_parent->children.end(), ctx->target));
                }
                ctx->target->parent = ctx->new_parent;
                ctx->index = ctx->new_parent->children.size() - 1;
            }

            void destructor(void* ctx)
            {
                data* cmd = (data*)ctx;
                delete cmd;
            } 
        }

        void attach_child(widget* parent, widget* child)
        {
            imgui_editor::command_data* cmd = new imgui_editor::command_data();
            cmd->label = "Attach child";

            attach_child_command::data* ctx = new attach_child_command::data();

            ctx->new_parent = parent;
            ctx->target = child;

            cmd->argument_data = ctx;
            cmd->undo = attach_child_command::undo;
            cmd->redo = attach_child_command::redo;
            cmd->destructor = attach_child_command::destructor;

            commit(cmd);
        }

        namespace remove_widget_command
        {
            struct data
            {
                widget* parent;
                size_t index;

                std::string widget;
            };

            void undo(void* _context)
            {
                data* ctx = (data*)_context;

                widget* w = new_widget(widget_type::widget_type_none);
                widget_deserialize(w,ctx->widget.c_str());

                ctx->parent->children.insert(ctx->parent->children.begin() + ctx->index, w);
            }

            void redo(void* _context)
            {
                data* ctx = (data*)_context;
                ctx->widget = widget_serialize(ctx->parent->children[ctx->index]);
                ctx->parent->children.erase(ctx->parent->children.begin() + ctx->index);
            }

            void destructor(void* ctx)
            {
                data* cmd = (data*)ctx;
                delete cmd;
            }
        }

        void remove_widget(widget* target)
        {
            size_t index = std::find(target->parent->children.begin(), target->parent->children.end(), target)-target->parent->children.begin();
            if(index < target->parent->children.size())
            {
                imgui_editor::command_data* cmd = new imgui_editor::command_data();
                cmd->label = "Remove widget";

                remove_widget_command::data* ctx = new remove_widget_command::data();

                ctx->parent = target->parent;
                ctx->index = index;
                ctx->widget = widget_serialize(target);

                cmd->argument_data = ctx;
                cmd->undo = remove_widget_command::undo;
                cmd->redo = remove_widget_command::redo;
                cmd->destructor = remove_widget_command::destructor;
                
                commit(cmd);
            }
            else
            {
                debug_break();
            }
        }
    }
}
