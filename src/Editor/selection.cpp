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
		void push_back_widgets(std::vector<widget*>& widgets, const std::vector<size_t> ids)
		{
			for (const size_t id : ids)
			{
				widgets.push_back(find(id));
			}
		}

		void push_back_ids(std::vector<size_t>& ids, const std::vector<widget*> targets)
		{
			for (const widget* target : targets)
			{
				ids.push_back(target->id);
			}
		}

		namespace select_context_command
		{
			struct data
			{
				size_t select = -1;
				std::vector<size_t> selects;

				size_t original = -1;
				std::vector<size_t> originals;
			};

			void undo(void* _context)
			{
				data* ctx = static_cast<data*>(_context);
				g_context->target = find(ctx->original);
				g_context->targets.clear();
				push_back_widgets(g_context->targets, ctx->originals);
			}

			void redo(void* _context)
			{
				data* ctx = static_cast<data*>(_context);
				g_context->target = find(ctx->select);
				g_context->targets.clear();
				push_back_widgets(g_context->targets, ctx->selects);
			}

			void destructor(void* ctx)
			{
				data* cmd = static_cast<data*>(ctx);
				delete cmd;
			}
		}

		void select(const widget* target)
		{
			command_data* cmd = new imgui_editor::command_data();
			cmd->label = string_format( "Select %s (ID : %d / %s)", target->label.c_str(),target->id, get_pretty_name(target->type));

			select_context_command::data* ctx = new select_context_command::data();

			ctx->select = target->id;
			ctx->selects.push_back(target->id);
			ctx->original = target->id;
			push_back_ids(ctx->originals,g_context->targets);

			cmd->argument_data = ctx;
			cmd->undo = select_context_command::undo;
			cmd->redo = select_context_command::redo;
			cmd->destructor = select_context_command::destructor;

			commit(cmd);
		}

		void select(const std::initializer_list<widget*> targets)
		{
			command_data* cmd = new imgui_editor::command_data();
			select_context_command::data* ctx = new select_context_command::data();

			assert(0 < targets.size());
			for (const widget* target : targets)
			{
				if (-1 == ctx->select) ctx->select = target->id;
				ctx->selects.push_back(target->id);
			}
			ctx->original = g_context->target->id;
			push_back_ids(ctx->originals,g_context->targets);

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

		const std::vector<widget*>& get_targets()
		{
			return g_context->targets;
		}
	}
}
