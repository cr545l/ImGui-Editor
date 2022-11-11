#include "Precompiled.h"
#include "Editor/history.h"

namespace ie
{
static CR_STATE std::vector<command*> commands;
static CR_STATE size_t index = SIZE_MAX;

void command_undo(command* ctx)
{
    ctx->undo(ctx->context);
}

void command_redo(command* ctx)
{
    ctx->undo(ctx->context);
}

void commit(command* ctx)
{
    for (size_t i = index + 1, max = commands.size(); i < max; ++i)
    {
        commands[i]->deconst(commands[i]->context);
        delete commands[i];
    }
    if (commands.size() != index + 1)
    {
        commands.resize(index + 1);
    }

    command_redo(ctx);
    commands.push_back(ctx);
    index = commands.size() - 1;
}

void undo()
{
    if(has_undo_command())
    {
        command_redo(commands[index]);
        ++index;
    }
}

void redo()
{
    if(has_undo_command())
    {
        command_undo(commands[index]);
        --index;
    }
}

bool has_undo_command(){ return SIZE_MAX != index; }
bool has_redo_command(){ return commands.size() && index + 1 < commands.size(); }
}
