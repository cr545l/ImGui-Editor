#ifndef __HISTORY_H__
#define __HISTORY_H__

namespace imgui_editor
{
	struct command_data
	{
		const char* label = "empty";
		void* argument_data;
		void(*undo)(void*);
		void(*redo)(void*);
		void(*destructor)(void*);
	};

	struct history
	{
		std::vector<command_data*> commands;
		size_t index = SIZE_MAX;
	};

	void init_history(history* history);

	void commit(command_data* ctx);

	void undo();
	void redo();
	bool has_undo_command();
	bool has_redo_command();
}

#endif
