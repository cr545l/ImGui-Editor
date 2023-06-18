#include "Precompiled.h"
#include "editor/selection.h"

#include <set>

#include "editor/history.h"
#include "editor/widget.h"

namespace imgui_editor
{
	static selection_context* s_context = nullptr;

	void init_selection(selection_context* ctx)
	{
		s_context = ctx;
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
				const data* ctx = static_cast<data*>(_context);
				s_context->target = find(ctx->original);
				s_context->targets.clear();
				push_back_widgets(s_context->targets, ctx->originals);
			}

			void redo(void* _context)
			{
				const data* ctx = static_cast<data*>(_context);
				s_context->target = find(ctx->select);
				s_context->targets.clear();
				push_back_widgets(s_context->targets, ctx->selects);
			}

			void destructor(void* ctx)
			{
				const data* cmd = static_cast<data*>(ctx);
				delete cmd;
			}
		}

		void select(const widget* target)
		{
			if (s_context->target == target) return;

			command_data* cmd = new command_data();
			cmd->label = string_format( "Select %s (ID : %d / %s)", target->label.c_str(),target->id, get_pretty_name(target->type));

			select_context_command::data* ctx = new select_context_command::data();

			ctx->select = target->id;
			ctx->selects.push_back(target->id);
			ctx->original = target->id;
			push_back_ids(ctx->originals,s_context->targets);

			cmd->argument_data = ctx;
			cmd->undo = select_context_command::undo;
			cmd->redo = select_context_command::redo;
			cmd->destructor = select_context_command::destructor;

			commit(cmd);
		}

		void select(const std::initializer_list<widget*> targets)
		{
			const std::set<widget*> targets_set(targets.begin(), targets.end());
			const std::set<widget*> context_targets_set(s_context->targets.begin(), s_context->targets.end());

			if (targets_set == context_targets_set) 
			{
				return;
			}
			command_data* cmd = new command_data();

			select_context_command::data* ctx = new select_context_command::data();

			// assert(0 < targets.size());
			for (const widget* target : targets)
			{
				if (-1 == ctx->select) ctx->select = target->id;
				ctx->selects.push_back(target->id);
			}
			ctx->original = s_context->target->id;
			push_back_ids(ctx->originals,s_context->targets);

			cmd->argument_data = ctx;
			cmd->undo = select_context_command::undo;
			cmd->redo = select_context_command::redo;
			cmd->destructor = select_context_command::destructor;

			commit(cmd);
		}

		void select(const std::vector<widget*>& targets)
		{
			const std::set<widget*> targets_set(targets.begin(), targets.end());
			const std::set<widget*> context_targets_set(s_context->targets.begin(), s_context->targets.end());

			if (targets_set == context_targets_set)
			{
				return;
			}
			command_data* cmd = new command_data();

			select_context_command::data* ctx = new select_context_command::data();

			// assert(0 < targets.size());
			for (const widget* target : targets)
			{
				if (-1 == ctx->select) ctx->select = target->id;
				ctx->selects.push_back(target->id);
			}
			ctx->original = s_context->target->id;
			push_back_ids(ctx->originals, s_context->targets);

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
			return s_context->target;
		}

		const std::vector<widget*>& get_targets()
		{
			return s_context->targets;
		}

		void reset()
		{
			s_context->target = nullptr;
			s_context->targets.clear();
		}

		void clear()
		{
			command::select(nullptr);
		}
	}
}
