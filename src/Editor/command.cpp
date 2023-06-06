#include "Precompiled.h"

#include "editor/history.h"
#include "editor/command.h"

#include "imgui_editor.h"
#include "editor/widget.h"

namespace imgui_editor
{
    namespace command
    {
        namespace create_widget_command
        {
            struct data
            {
                bool dirty = false;
				
                widget* parent = nullptr;
                widget_type type = widget_type::widget_type_none;
                size_t index = -1;
                size_t id = -1;
            };

            void undo(void* c)
            {
	            const data* ctx = static_cast<data*>(c);
                delete_widget(ctx->parent->children[ctx->index]);
                ctx->parent->children.erase(ctx->parent->children.begin() + ctx->index);
                get_context()->project.dirty = ctx->dirty;
            }

            void redo(void* c)
            {
                data* ctx = static_cast<data*>(c);
                widget* widget = nullptr;
                if(-1 == ctx->id)
                {
                    widget = new_widget(ctx->type);
                    ctx->id = widget->id;
                }
                else
                {
                    widget = new_widget_by_id(ctx->type, ctx->id);
                }

                if(ctx->index == -1)
                {
                    ctx->index = ctx->parent->children.size();     
                    ctx->parent->children.push_back(widget);
                }
                else
                {
                    ctx->parent->children.insert(ctx->parent->children.begin() + ctx->index, widget);
                }
                widget->parent = ctx->parent;
                get_context()->project.dirty = true;
            }

            void destructor(void* ctx)
            {
	            const data* cmd = static_cast<data*>(ctx);
                delete cmd;
            } 
        }
        
	    void create_widget(widget* parent, const widget_type& type, size_t index)
        {
            command_data* cmd = new command_data();
            cmd->label = string_format("Create widget (%s)", get_pretty_name(type));

            create_widget_command::data* ctx = new create_widget_command::data();

            ctx->dirty = get_context()->project.dirty;

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
                bool dirty = false;
                widget* new_parent;
                widget* target;
                size_t index;

                widget* old_parent;
            };

            void undo(void* c)
            {
	            const data* ctx = static_cast<data*>(c);
                ctx->new_parent->children.erase(std::find(ctx->new_parent->children.begin(), ctx->new_parent->children.end(), ctx->target));
                if(ctx->old_parent)
                {
                    ctx->old_parent->children.insert(ctx->old_parent->children.begin() + ctx->index, ctx->target);
                }
                ctx->target->parent = ctx->old_parent;
                get_context()->project.dirty = ctx->dirty;
            }

            void redo(void* c)
            {
                data* ctx = (data*)c;
                ctx->new_parent->children.push_back(ctx->target);
                ctx->old_parent = ctx->target->parent;
                if(ctx->old_parent)
                {
                    ctx->old_parent->children.erase(std::find(ctx->old_parent->children.begin(), ctx->old_parent->children.end(), ctx->target));
                }
                ctx->target->parent = ctx->new_parent;
                ctx->index = ctx->new_parent->children.size() - 1;
                get_context()->project.dirty = true;
            }

            void destructor(void* ctx)
            {
                data* cmd = static_cast<data*>(ctx);
                delete cmd;
            } 
        }

        void attach_child(widget* parent, widget* child)
        {
            imgui_editor::command_data* cmd = new imgui_editor::command_data();
            cmd->label = "Attach child";

            attach_child_command::data* ctx = new attach_child_command::data();

            ctx->dirty = get_context()->project.dirty;

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
                bool dirty = false;
                widget* parent = nullptr;
                size_t index = -1;
                size_t id = -1;

                std::string widget;
            };

            void undo(void* c)
            {
                data* ctx = static_cast<data*>(c);
                
                widget* w = new_widget_by_id(widget_type::widget_type_none, 0);
                widget_deserialize(w,ctx->widget.c_str());
                w->parent = ctx->parent;
                ctx->parent->children.insert(ctx->parent->children.begin() + ctx->index, w);
                get_context()->project.dirty = ctx->dirty;
            }

            void redo(void* c)
            {
                data* ctx = static_cast<data*>(c);
                ctx->widget = widget_serialize(ctx->parent->children[ctx->index]);
                ctx->parent->children.erase(ctx->parent->children.begin() + ctx->index);
                get_context()->project.dirty = true;
            }

            void destructor(void* ctx)
            {
                data* cmd = static_cast<data*>(ctx);
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

                ctx->dirty = get_context()->project.dirty;

                ctx->parent = target->parent;
                ctx->index = index;
                ctx->id = target->id;
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
