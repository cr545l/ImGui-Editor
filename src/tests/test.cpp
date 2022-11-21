#include "Precompiled.h"

#include <gtest/gtest.h>
#include <magic_enum.hpp>

#include "Editor/widget.h"

using namespace imgui_editor;

TEST(widget, args_nullptr_check) 
{
    magic_enum::enum_for_each<widget_type>([&](widget_type t) {
            auto w = new_widget(t);
            std::string name = std::string(magic_enum::enum_name(t));
            EXPECT_NE(nullptr, w->args)<< name << " IS NULLPTR";
            delete_widget(w);
            EXPECT_EQ(nullptr, w->args)<< name << " IS NOT NULLPTR";
            delete w;
        });
}