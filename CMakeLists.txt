#
# project: imgui-editor
#
cmake_minimum_required(VERSION 2.8)
project(imgui-editor)
if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MD> #---------|
        $<$<CONFIG:Debug>:/MDd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MD> #--|
    )
endif()
# include the fips main cmake file
get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

set (CMAKE_CXX_STANDARD 17)
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

# include_directories(src)
fips_setup()
    add_definitions(-DDEPLOY_PATH="${FIPS_PROJECT_DEPLOY_DIR}")
    fips_add_subdirectory(src)
fips_finish()