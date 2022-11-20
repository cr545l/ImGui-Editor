#include "Precompiled.h"
#include "Editor/selection.h"

#include "Editor/history.h"

namespace imgui_editor
{
	static selection_context* g_context = nullptr;

	void init_selection(selection_context* ctx)
	{
		g_context = ctx;
	}

	namespace selection
	{
		struct command_select_context
		{
			widget* select = nullptr;
			std::vector<widget*> selects;

			widget* original = nullptr;
			std::vector<widget*> originals;
		};

		void command_select_undo(void* _context)
		{
			command_select_context* ctx = (command_select_context*)_context;
			g_context->target = ctx->original;
			g_context->targets = ctx->originals;
		}

		void command_select_redo(void* _context)
		{
			command_select_context* ctx = (command_select_context*)_context;
			g_context->target = ctx->select;
			g_context->targets = ctx->selects;
		}

		void command_select_destructor(void* ctx)
		{
			command_select_context* cmd = (command_select_context*)ctx;
			delete cmd;
		}

		void select(widget* target)
		{
			command* cmd = new imgui_editor::command();
			cmd->label = "select";

			command_select_context* ctx = new command_select_context();

			ctx->select = target;
			ctx->selects.push_back(target);
			ctx->original = target;
			ctx->originals = g_context->targets;

			cmd->argument_data = ctx;
			cmd->undo = command_select_undo;
			cmd->redo = command_select_redo;
			cmd->destructor = command_select_destructor;

			commit(cmd);
		}

		void select(std::initializer_list<widget*> targets)
		{
			command* cmd = new imgui_editor::command();
			command_select_context* ctx = new command_select_context();

			assert(0 < targets.size());
			for (auto target : targets)
			{
				if (nullptr == ctx->select) ctx->select = target;
				ctx->selects.push_back(target);
			}
			ctx->original = g_context->target;
			ctx->originals = targets;

			cmd->argument_data = ctx;
			cmd->undo = command_select_undo;
			cmd->redo = command_select_redo;
			cmd->destructor = command_select_destructor;

			commit(cmd);
		}

		widget* get_target()
		{
			return g_context->target;
		}

		const std::vector<widget*> get_targets()
		{
			return g_context->targets;
		}
	}
}
