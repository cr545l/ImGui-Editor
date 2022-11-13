#include "Precompiled.h"
#include "Editor/history.h"

namespace imgui_editor
{

history* g_context = nullptr;

void command_undo(command* ctx)
{
	ctx->undo(ctx->context);
}

void command_redo(command* ctx)
{
    ctx->redo(ctx->context);
}

void init_history(history* history)
{
    g_context = history;
}

void commit(command* ctx)
{
    for (size_t i = g_context->index + 1, max = g_context->commands.size(); i < max; ++i)
    {
        g_context->commands[i]->destructor(g_context->commands[i]->context);
        delete g_context->commands[i];
    }
    if (g_context->commands.size() != g_context->index + 1)
    {
        g_context->commands.resize(g_context->index + 1);
    }

    command_redo(ctx);
    g_context->commands.push_back(ctx);
    g_context->index = g_context->commands.size() - 1;
}

void undo()
{
    if(has_undo_command())
    {
        command_undo(g_context->commands[g_context->index]);
        --g_context->index;
    }
}

void redo()
{
    if(has_redo_command())
    {
        ++g_context->index;
        command_redo(g_context->commands[g_context->index]);
    }
}

bool has_undo_command(){ return SIZE_MAX != g_context->index; }
bool has_redo_command(){ return g_context->commands.size() && g_context->index + 1 < g_context->commands.size(); }
}
