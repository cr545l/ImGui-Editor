﻿#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "Precompiled.h"
#include "editor/widget/enum_type.h"

BEGIN_NS_IMGUI_EDITOR

struct style_color
{
    ImGuiCol_ idx;
    ImColor col;
};

struct style_var_float
{
    ImGuiStyleVar_ idx = ImGuiStyleVar_Alpha;
    float val;
};

struct style_var_vec2
{
    ImGuiStyleVar_ idx = ImGuiStyleVar_WindowPadding;
    ImVec2 val;
};

// imgui의 그려지는 모든 위젯을 관리하기 위한 데이터
struct widget
{
    widget_type type = widget_type::widget_type_none;
    void* args = nullptr;

    std::string label = "empty";

    std::vector<widget*> children;

    std::vector<style_color> style_colors;
    std::vector<style_var_float> style_var_floats;
    std::vector<style_var_vec2> style_var_vec2s;

    std::string string_id;
    size_t id = 0;
    widget* parent = nullptr;

    void(*draw)(widget*) = nullptr;
    void(*draw_inspector)(widget*) = nullptr;
};

widget* find(size_t id);
const char* get_widget_name(widget_type type);
const char* get_widget_description(widget_type type);

const char* get_col_name(ImGuiCol_ type);
const char* get_col_description(ImGuiCol_ type);

const char* get_style_var_name(ImGuiStyleVar_ type);
const char* get_style_var_description(ImGuiStyleVar_ type);

const std::vector<ImGuiCol_>& get_color_list(widget_type type);
const std::vector<ImGuiStyleVar_>& get_style_var_list(widget_type type);

int32_t to_fixed_type(widget_type type);
widget_type to_widget_type(int32_t fixed_type);

void draw_widget(widget* context);
void draw_inspector_widget(const widget* context);

IMGUI_EDITOR_EXPORT widget* new_widget(widget_type type);
IMGUI_EDITOR_EXPORT widget* new_widget_by_id(widget_type type, size_t id);
IMGUI_EDITOR_EXPORT	void regist_widget(widget* w);
IMGUI_EDITOR_EXPORT	void unregist_widget(const widget* w);
IMGUI_EDITOR_EXPORT void* new_widget_arg(widget_type type);
IMGUI_EDITOR_EXPORT void delete_widget(widget* target);
IMGUI_EDITOR_EXPORT void delete_widget_args(widget_type type, void* target);

void parse_args_data(widget_type type, void* data, std::string& inout, std::string& version, bool is_read);

std::string widget_serialize(widget* target);
IMGUI_EDITOR_EXPORT bool widget_deserialize(widget* target, const char* data);

enum class generate_code
{
    cpp,
};

void widget_generate(generate_code code, widget* target, bool root, std::string& result);

END_NS_IMGUI_EDITOR

#endif
