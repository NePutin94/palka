cmake_minimum_required(VERSION 3.19)

project(PalkaCore)

file(GLOB CORE_SRC RELATIVE "${CMAKE_SOURCE_DIR}/palka_core" "../palka_core/*.cpp")
file(GLOB GLAD_SRC RELATIVE "${CMAKE_SOURCE_DIR}/palka_core" "../glad/src/*.c")

set(HEADER_SOURCE Matrix.h ReflectionDebug.h Drawable.h)
set(RTTR_DIR "D:\\Link\\rttr_gcc\\cmake")
set(FREETYPE_DIR E:\\freetype-master\\ft_gcc\\lib\\cmake\\freetype)
set(CMAKE_PREFIX_PATH E:\\freetype-master\\ft_gcc D:\\Link\\glfw_gcc12 E:\\freeglut-3.2.1\\build\\lib\\cmake\\FreeGLUT)
set(GLEW_ROOT_DIR D:\\Link\\glew)
set(GLAD_INCLUDE "../glad/include")
message(STATUS ${CORE_SRC})
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(RTTR CONFIG REQUIRED Core)

add_library(PalkaCore SHARED ${CORE_SRC} ${HEADER_SOURCE})

target_link_libraries(PalkaCore PUBLIC mingw32 ${OPENGL_LIBRARIES} STB IMGUI_GLFW IMGUI GLAD glfw RTTR::Core imm32 ws2_32 dwmapi)
target_compile_definitions(PalkaCore PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD GL_GLEXT_PROTOTYPES=1)
target_include_directories(PalkaCore PUBLIC ${OPENGL_INCLUDE_DIRS} "../palka_core")

