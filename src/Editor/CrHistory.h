#ifndef __CR_HISTORY_H__
#define __CR_HISTORY_H__

class CrCommand
{
public:
	virtual ~CrCommand() = default;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

class CrHistroy
{
public:
	static void Commit(CrCommand* command)
	{
		for (size_t i = index + 1, max = commands.size(); i < max; ++i)
		{
			delete commands[i];
		}
		if (commands.size() != index + 1) 
		{
			commands.resize(index + 1);
		}

		command->Redo();
		commands.push_back(command);
		index = commands.size() - 1;
	}

	static bool CanRedo() { return commands.size() && index + 1 < commands.size(); }

	static void Redo()
	{
		if (CanRedo())
		{
			++index;
			commands[index]->Redo();
		}
	}

	static bool CanUndo() { return SIZE_MAX != index ; }

	static void Undo()
	{
		if (CanUndo())
		{
			commands[index]->Undo();
			--index;
		}
	}

private:
	static std::vector<CrCommand*> commands;
	static size_t index;
};

#endif