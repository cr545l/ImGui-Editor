#include "Precompiled.h"
#include "editor/selection.h"

#include "editor/history.h"
#include "editor/widget.h"

namespace imgui_editor
{
	static selection_context* g_context = nullptr;

	void init_selection(selection_context* ctx)
	{
		g_context = ctx;
	}

	namespace command
	{
		namespace select_context_command
		{
			struct data
			{
				widget* select = nullptr;
				std::vector<widget*> selects;

				widget* original = nullptr;
				std::vector<widget*> originals;
			};

			void undo(void* _context)
			{
				data* ctx = (data*)_context;
				g_context->target = ctx->original;
				g_context->targets = ctx->originals;
			}

			void redo(void* _context)
			{
				data* ctx = (data*)_context;
				g_context->target = ctx->select;
				g_context->targets = ctx->selects;
			}

			void destructor(void* ctx)
			{
				data* cmd = (data*)ctx;
				delete cmd;
			}
		}

		void select(widget* target)
		{
			command_data* cmd = new imgui_editor::command_data();
			cmd->label = string_format( "Select %s (ID : %d / %s)", target->label.c_str(),target->id, get_pretty_name(target->type));

			select_context_command::data* ctx = new select_context_command::data();

			ctx->select = target;
			ctx->selects.push_back(target);
			ctx->original = target;
			ctx->originals = g_context->targets;

			cmd->argument_data = ctx;
			cmd->undo = select_context_command::undo;
			cmd->redo = select_context_command::redo;
			cmd->destructor = select_context_command::destructor;

			commit(cmd);
		}

		void select(std::initializer_list<widget*> targets)
		{
			command_data* cmd = new imgui_editor::command_data();
			select_context_command::data* ctx = new select_context_command::data();

			assert(0 < targets.size());
			for (auto target : targets)
			{
				if (nullptr == ctx->select) ctx->select = target;
				ctx->selects.push_back(target);
			}
			ctx->original = g_context->target;
			ctx->originals = targets;

			cmd->argument_data = ctx;
			cmd->undo = select_context_command::undo;
			cmd->redo = select_context_command::redo;
			cmd->destructor = select_context_command::destructor;

			commit(cmd);
		}
	}

	namespace selection
	{
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
