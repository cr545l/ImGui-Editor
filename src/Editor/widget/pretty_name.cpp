#include <magic_enum/magic_enum.hpp>

#include "Precompiled.h"
#include "editor/imgui_editor.h"
#include "editor/widget.h"

BEGIN_NS_IMGUI_EDITOR

const char* get_widget_name(widget_type type)
{
    std::string name(magic_enum::enum_name(type));
    name.insert(0, "widget_name.");
    return get_language_text(name.c_str());
}

const char* get_widget_description(widget_type type)
{
    std::string name(magic_enum::enum_name(type));
    name.insert(0, "widget_description.");
    return get_language_text(name.c_str());
}

const char* get_col_name(ImGuiCol_ type)
{
    std::string name(magic_enum::enum_name(type));
    name.insert(0, "ImGuiCol_name.");
    return get_language_text(name.c_str());
}
const char* get_col_description(ImGuiCol_ type)
{
    std::string name(magic_enum::enum_name(type));
    name.insert(0, "ImGuiCol_description.");
    return get_language_text(name.c_str());
}

const char* get_style_var_name(ImGuiStyleVar_ type)
{
    std::string name(magic_enum::enum_name(type));
    name.insert(0, "ImGuiStyleVar_name.");
    return get_language_text(name.c_str());
}

const char* get_style_var_description(ImGuiStyleVar_ type)
{
    std::string name(magic_enum::enum_name(type));
    name.insert(0, "ImGuiStyleVar_description.");
    return get_language_text(name.c_str());
}

// 해당 타입의 위젯에 적용 가능한 ImGuiCol_ 리스트를 반환한다
const std::vector<ImGuiCol_>& get_color_list(widget_type type)
{
    static const std::vector<ImGuiCol_> empty;
    switch (type)
    {
    case widget_type::widget_type_begin_end_window:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_WindowBg,
            ImGuiCol_ChildBg,
            ImGuiCol_PopupBg,
            ImGuiCol_Border,
            ImGuiCol_BorderShadow,
            ImGuiCol_TitleBg,
            ImGuiCol_TitleBgActive,
            ImGuiCol_TitleBgCollapsed,
            ImGuiCol_MenuBarBg,
            ImGuiCol_ScrollbarBg,
            ImGuiCol_ScrollbarGrab,
            ImGuiCol_ScrollbarGrabHovered,
            ImGuiCol_ScrollbarGrabActive,
            ImGuiCol_ResizeGrip,
            ImGuiCol_ResizeGripHovered,
            ImGuiCol_ResizeGripActive,
            ImGuiCol_Separator,
            ImGuiCol_SeparatorHovered,
            ImGuiCol_SeparatorActive,
            ImGuiCol_NavHighlight,
            ImGuiCol_NavWindowingHighlight,
            ImGuiCol_NavWindowingDimBg,
            ImGuiCol_ModalWindowDimBg,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_button:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_Button,
            ImGuiCol_ButtonHovered,
            ImGuiCol_ButtonActive,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_text:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_Text,
            ImGuiCol_TextDisabled,
            ImGuiCol_TextSelectedBg,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_input_text:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_Text,
            ImGuiCol_TextDisabled,
            ImGuiCol_FrameBg,
            ImGuiCol_FrameBgHovered,
            ImGuiCol_FrameBgActive,
            ImGuiCol_TextSelectedBg,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_slider_float:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_SliderGrab,
            ImGuiCol_SliderGrabActive,
            ImGuiCol_FrameBg,
            ImGuiCol_FrameBgHovered,
            ImGuiCol_FrameBgActive,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_separator:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_Separator,
            ImGuiCol_SeparatorHovered,
            ImGuiCol_SeparatorActive,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_color_edit3:
    case widget_type::widget_type_color_edit4:
    case widget_type::widget_type_color_picker3:
    case widget_type::widget_type_color_picker4:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_FrameBg,
            ImGuiCol_FrameBgHovered,
            ImGuiCol_FrameBgActive,
            ImGuiCol_Text,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_table_next_row:
    case widget_type::widget_type_table_next_column:
    case widget_type::widget_type_table_set_column_index:
    case widget_type::widget_type_begin_end_table:
    {
        static const std::vector<ImGuiCol_> list = {
            ImGuiCol_TableHeaderBg,
            ImGuiCol_TableBorderStrong,
            ImGuiCol_TableBorderLight,
            ImGuiCol_TableRowBg,
            ImGuiCol_TableRowBgAlt,
            // 추가적인 ImGuiCol_ 옵션
        };
        return list;
    }
    // 필요한 추가 widget_type에 대한 case 추가...
    }

    return empty;
}

// 해당 타입의 위젯에 적용 가능한 ImGuiStyleVar_ 리스트를 반환한다
const std::vector<ImGuiStyleVar_>& get_style_var_list(widget_type type)
{
    static const std::vector<ImGuiStyleVar_> empty;
    switch (type)
    {
    case widget_type::widget_type_begin_end_window:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_Alpha,
            ImGuiStyleVar_DisabledAlpha,
            ImGuiStyleVar_WindowPadding,
            ImGuiStyleVar_WindowRounding,
            ImGuiStyleVar_WindowBorderSize,
            ImGuiStyleVar_WindowMinSize,
            ImGuiStyleVar_WindowTitleAlign,
            ImGuiStyleVar_ChildRounding,
            ImGuiStyleVar_ChildBorderSize,
            ImGuiStyleVar_PopupRounding,
            ImGuiStyleVar_PopupBorderSize,
            ImGuiStyleVar_FramePadding,
            ImGuiStyleVar_FrameRounding,
            ImGuiStyleVar_FrameBorderSize,
            ImGuiStyleVar_ItemSpacing,
            ImGuiStyleVar_ItemInnerSpacing,
            ImGuiStyleVar_IndentSpacing,
            ImGuiStyleVar_ScrollbarSize,
            ImGuiStyleVar_ScrollbarRounding,
            ImGuiStyleVar_GrabMinSize,
            ImGuiStyleVar_GrabRounding,
            ImGuiStyleVar_TabRounding,
            ImGuiStyleVar_ButtonTextAlign,
            ImGuiStyleVar_SelectableTextAlign,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_button:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_Alpha,
            ImGuiStyleVar_DisabledAlpha,
            ImGuiStyleVar_FramePadding,
            ImGuiStyleVar_ItemSpacing,
            ImGuiStyleVar_ItemInnerSpacing,
            ImGuiStyleVar_ButtonTextAlign,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_text:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_Alpha,
            ImGuiStyleVar_DisabledAlpha,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_input_text:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_Alpha,
            ImGuiStyleVar_DisabledAlpha,
            ImGuiStyleVar_FramePadding,
            ImGuiStyleVar_ItemSpacing,
            ImGuiStyleVar_ItemInnerSpacing,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_slider_float:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_Alpha,
            ImGuiStyleVar_DisabledAlpha,
            ImGuiStyleVar_GrabMinSize,
            ImGuiStyleVar_GrabRounding,
            ImGuiStyleVar_FramePadding,
            ImGuiStyleVar_ItemSpacing,
            ImGuiStyleVar_ItemInnerSpacing,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_separator:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_ItemSpacing,
            ImGuiStyleVar_ItemInnerSpacing,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_color_edit3:
    case widget_type::widget_type_color_edit4:
    case widget_type::widget_type_color_picker3:
    case widget_type::widget_type_color_picker4:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_Alpha,
            ImGuiStyleVar_DisabledAlpha,
            ImGuiStyleVar_FramePadding,
            ImGuiStyleVar_ItemSpacing,
            ImGuiStyleVar_ItemInnerSpacing,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    case widget_type::widget_type_table_next_row:
    case widget_type::widget_type_table_next_column:
    case widget_type::widget_type_table_set_column_index:
    case widget_type::widget_type_begin_end_table:
    {
        static const std::vector<ImGuiStyleVar_> list = {
            ImGuiStyleVar_Alpha,
            ImGuiStyleVar_DisabledAlpha,
            ImGuiStyleVar_CellPadding,
            ImGuiStyleVar_ItemSpacing,
            ImGuiStyleVar_ItemInnerSpacing,
            // 추가적인 ImGuiStyleVar_ 옵션
        };
        return list;
    }
    // 필요한 추가 widget_type에 대한 case 추가...
    }

    return empty;
}

END_NS_IMGUI_EDITOR