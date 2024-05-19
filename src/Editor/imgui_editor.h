#ifndef __IMGUI_EDITOR_H__
#define __IMGUI_EDITOR_H__

#include "editor/widget.h"

BEGIN_NS_IMGUI_EDITOR

struct widget;
struct imgui_editor_context;
struct history;

struct project_context
{
    bool ready = false;
    bool dirty = false;
    std::string absolutePath;
    widget* root = nullptr;
};

struct imgui_editor_context
{
    widget* root;
    project_context project;

    std::vector<std::string> last_open_paths;

    widget_type create_widget_type = widget_type::widget_type_none;
    std::string import_text;
};

IMGUI_EDITOR_EXPORT imgui_editor_context* get_context();

IMGUI_EDITOR_EXPORT void initialize_editor(imgui_editor_context* ctx, const char* init);
IMGUI_EDITOR_EXPORT bool open_project(imgui_editor_context* ctx, const char* path);

const char* get_language_text(const char* key);
#define F(key) imgui_editor::get_language_text(key)

void set_language(const char* key);
const std::string& get_language();

void close_project(imgui_editor_context* ctx);

void draw_start_page(imgui_editor_context* context);
void draw_tool(imgui_editor_context* editor_context);
void draw_hierarchy(const imgui_editor_context* editor_context);
void draw_inspector(imgui_editor_context* context);
void draw_history(history* ctx);

void draw_editor_context(imgui_editor_context* ctx, history* history);

END_NS_IMGUI_EDITOR

#endif
