#ifndef __IE_HISTORY_H__
#define __IE_HISTORY_H__

namespace ie
{
struct command
{
    const char* label = "empty";
    void* context;
    void(*undo)(void*);
    void(*redo)(void*);
    void(*deconst)(void*);
};

void commit(command* ctx);

void undo();
void redo();
bool has_undo_command();
bool has_redo_command();
}

#endif
