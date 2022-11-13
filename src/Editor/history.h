#ifndef __HISTORY_H__
#define __HISTORY_H__

namespace imgui_editor
{
	struct command
	{
		const char* label = "empty";
		void* context;
		void(*undo)(void*);
		void(*redo)(void*);
		void(*destructor)(void*);
	};

	struct history
	{
		std::vector<command*> commands;
		size_t index = SIZE_MAX;
	};

	void init_history(history* history);

	void commit(command* ctx);

	void undo();
	void redo();
	bool has_undo_command();
	bool has_redo_command();
}

#endif
