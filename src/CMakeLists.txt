fips_begin_sharedlib(editor cmdline)
    fips_files(Editor/EditorMain.cpp)

    fips_files(Editor/CrWindow.h)
    fips_files(Editor/Private/CrWindow.cpp)

    fips_files(Editor/CrWidget.h)
    fips_files(Editor/Private/CrWidget.cpp)

    fips_files(Editor/CrSelection.h)
    fips_files(Editor/Private/CrSelection.cpp)

    fips_files(Editor/CrHistory.h)
    fips_files(Editor/Private/CrHistory.cpp)

    fips_files(Editor/CrWidgetEditor.h)
    fips_files(Editor/Private/CrWidgetEditor.cpp)
    
    include_directories(.)
    include_directories(GL)
    include_directories(CR)
    include_directories(magic_enum)

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
fips_end_sharedlib()

fips_begin_app(entry cmdline)
    fips_files(Entry/main.cpp)
    include_directories(.)
    include_directories(GL)
    include_directories(CR)

    fips_src(GL GROUP_FOLDERS)
    fips_deps(editor imgui glfw3)

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