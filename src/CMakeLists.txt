fips_begin_sharedlib(editor cmdline)

    fips_dir(editor)
    fips_files(
        main.cpp
        extension.h
        extension.cpp
        widget.h
        widget.cpp
        history.h
        history.cpp
        command.h
        command.cpp
        selection.h
        selection.cpp
        imgui_editor.h
        imgui_editor.cpp
    )
	
    fips_dir(editor/widget)
    fips_files(
        args_data.h
        delete.cpp
        serialize.cpp
        draw.cpp
        enum_type.h
        fixed_type.cpp
        gen_code.cpp
        inspector.cpp
        new.cpp
        pretty_name.cpp
        to_enum_type.cpp
    )
    fips_dir(editor/window)
    fips_files(
        start_page.cpp
        hierarchy.cpp
        inspector.cpp
        tool.cpp
        history.cpp
    )    
    
    fips_dir(thirdparty/imgui)
    fips_files(imgui_stdlib.cpp)

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

if (FIPS_MSVC)
    target_compile_options(editor PUBLIC "/Zc:__cplusplus")
    set_target_properties(editor PROPERTIES COMPILE_FLAGS "/std:c++20")	
endif()

fips_begin_app(entry cmdline)    
    fipsutil_copy(entry-res.yml)

    fips_files(
        entry/main.cpp
    )
    include_directories(.)
    include_directories(thirdparty)

    fips_src(thirdparty/GL GROUP_FOLDERS)
    fips_deps(editor)

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
    set_target_properties(entry PROPERTIES COMPILE_FLAGS "/std:c++20")
endif()

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