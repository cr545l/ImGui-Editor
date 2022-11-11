#include "Precompiled.h"
#include "Editor/selection.h"

#include "Editor/history.h"

namespace ie
{
namespace selection
{
static CR_STATE widget* _target;
static CR_STATE std::vector<widget*> _targets;

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
    _target = ctx->original;
    _targets = ctx->originals;
}

void command_select_redo(void* _context)
{
    command_select_context* ctx = (command_select_context*)_context;
    _target = ctx->select;
    _targets = ctx->selects;
}

void command_select_deconst(void* ctx)
{
    command_select_context* cmd = (command_select_context*)ctx;
    delete cmd;
}

void select(widget* target)
{
    ie::command* cmd = new ie::command();
    cmd->label = "select";
    
    command_select_context* ctx = new command_select_context();
    
    ctx->select = target;
    ctx->selects.push_back(target);
    ctx->original = target;
    ctx->originals = _targets;
    
    cmd->context = ctx;
    cmd->undo = command_select_undo;
    cmd->redo = command_select_redo;
    cmd->deconst = command_select_deconst;
}

void select(std::initializer_list<widget*> targets)
{
    ie::command* cmd = new ie::command();
    command_select_context* ctx = new command_select_context();
    
    assert(0 < targets.size());
    for(auto target : targets)
    {
        if (nullptr == ctx->select) ctx->select = target;
        ctx->selects.push_back(target);
    }
    ctx->original = _target;
    ctx->originals = targets;
    
    cmd->context = ctx;
    cmd->undo = command_select_undo;
    cmd->redo = command_select_redo;
    cmd->deconst = command_select_deconst;
    
    commit(cmd);
}

widget* get_target()
{
    return _target;
}

const std::vector<widget*> get_targets()
{
    return _targets;
}
}
}
