cmake_minimum_required(VERSION 3.19)
project(IMGUI_GLFW)

file(GLOB IMGUI_GLFW_SRC RELATIVE "${CMAKE_SOURCE_DIR}/imgui_glfw" "*.cpp")

if (WIN32)
    set(CMAKE_PREFIX_PATH E:\\Link\\glfw_gcc12)
endif (WIN32)

find_package(glfw3 REQUIRED)
add_library(IMGUI_GLFW OBJECT ${IMGUI_GLFW_SRC})
target_link_libraries(IMGUI_GLFW PRIVATE glfw IMGUI ${CMAKE_DL_LIBS})
target_include_directories(IMGUI_GLFW PUBLIC ".")
