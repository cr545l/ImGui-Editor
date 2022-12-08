fips_begin_sharedlib(editor cmdline)
    fips_files(editor/main.cpp)
    
    fips_files(editor/imgui_ex.h)
    fips_files(editor/imgui_ex.cpp)
    
    fips_files(editor/widget.h)
    fips_files(editor/widget.cpp)
    fips_files(editor/widget_draw_hierarchy.cpp)
    fips_files(editor/widget_draw_tool.cpp)
    
    fips_files(editor/widget/args_data.h)
    fips_files(editor/widget/delete.cpp)
    fips_files(editor/widget/deserialize.cpp)
    fips_files(editor/widget/draw.cpp)
    fips_files(editor/widget/enum_type.h)
    fips_files(editor/widget/fixed_type.cpp)
    fips_files(editor/widget/gen_code.cpp)
    fips_files(editor/widget/inspector.cpp)
    fips_files(editor/widget/new.cpp)
    fips_files(editor/widget/pretty_name.cpp)
    fips_files(editor/widget/serialize.cpp)
    fips_files(editor/widget/to_enum_type.cpp)
    
    fips_files(editor/widget_editor.h)
    fips_files(editor/widget_editor.cpp)
        
    fips_files(editor/history.h)
    fips_files(editor/history.cpp)
        
    fips_files(editor/command.h)
    fips_files(editor/command.cpp)
    
    fips_files(editor/selection.h)
    fips_files(editor/selection.cpp)
	
    fips_files(thirdparty/imgui/imgui_stdlib.cpp)
    
    include_directories(.)
    include_directories(thirdparty)

    fips_src(thirdparty/GL GROUP_FOLDERS)
    fips_deps(imgui glfw3)

    if (FIPS_WINDOWS)
        fips_libs(opengl32)
    endif()

    if (FIPS_LINUX)
        fips_libs(X11 Xrandr Xi Xinerama Xxf86vm Xcursor GL m dl)
    endif()

    if (FIPS_MACOS)
        fips_frameworks_osx(Cocoa CoreVideo OpenGL)
        fips_libs(m dl)
    endif()
fips_end_sharedlib()

#-------------------------------------------------------------------------------
#   gtest_begin(name)
#   Begin defining a unit test.
#
macro(gtest_begin2 name)
    set(options NO_TEMPLATE)
    set(oneValueArgs TEMPLATE)
    set(multiValueArgs)
    cmake_parse_arguments(_gt "${options}" "${oneValueArgs}" "" ${ARGN})

    if (_gt_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "gtest_begin(): called with invalid args '${_gt_UNPARSED_ARGUMENTS}'")
    endif()

    set(FipsAddFilesEnabled 1)
    fips_reset(${CurTargetName}Test)
    set(CurAppType "cmdline")
endmacro()

gtest_begin2(editor)
	fips_dir(tests)
	fips_files(
		test.cpp
		enum_test.h
		enum_test.cpp
	)
	fips_deps(editor)
gtest_end()

fips_begin_app(entry cmdline)
    fips_files(Entry/main.cpp)
    include_directories(.)
    include_directories(thirdparty)

    fips_src(GL GROUP_FOLDERS)
    fips_deps(imgui glfw3)

    if (FIPS_WINDOWS)
        fips_libs(opengl32)
    endif()

    if (FIPS_LINUX)
        fips_libs(X11 Xrandr Xi Xinerama Xxf86vm Xcursor GL m dl)
    endif()

    if (FIPS_MACOS)
        fips_frameworks_osx(Cocoa CoreVideo OpenGL)
        fips_libs(m dl)
    endif()
fips_end_app()

if (FIPS_MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT entry)
    set_target_properties(entry PROPERTIES COMPILE_FLAGS "/std:c++latest")
    set_target_properties(editor PROPERTIES COMPILE_FLAGS "/std:c++latest")
endif()

target_compile_features(entry PRIVATE cxx_std_17)
target_compile_features(editor PRIVATE cxx_std_17)
