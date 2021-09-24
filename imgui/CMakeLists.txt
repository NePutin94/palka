cmake_minimum_required(VERSION 3.19)
project(IMGUI)

file(GLOB IMGUI_SRC RELATIVE "${CMAKE_SOURCE_DIR}/palka_core/imgui" "*.cpp")
#file(GLOB_RECURSE IMGUI_HEADER RELATIVE "${CMAKE_SOURCE_DIR}/imgui" "../imgui/*.h")

add_library(IMGUI STATIC ${IMGUI_SRC})
target_compile_definitions(IMGUI PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_include_directories(IMGUI PUBLIC ".")
