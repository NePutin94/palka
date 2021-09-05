cmake_minimum_required(VERSION 3.19)
project(palka)
set(CMAKE_CXX_STANDARD 17)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "-O0 -g")
else()
    set(CMAKE_CXX_FLAGS "-O3 -mwindows -DNDEBUG -s")
endif()

file(GLOB_RECURSE IMGUI2_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./imgui/*.cpp")
#file(GLOB_RECURSE GLAD_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./glad/src/*.c")
file(GLOB_RECURSE CORE_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./palka_core/*.cpp")
file(GLOB_RECURSE ENTITIES_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./palka_entities/*.cpp")
set(HEADER_SOURCE palka_core/Matrix.h palka_core/ReflectionDebug.h palka_core/Drawable.h)

if (WIN32)
    #set(GLAD_INCLUDE "./glad/include")
    set(RTTR_DIR "D:\\Link\\rttr_gcc\\cmake")
    set(CMAKE_MODULE_PATH "E:\\ClionProject\\palka\\cmake")
    set(SDLIMAGEDIR D:\\Link\\sdlimage_gcc10)
    set(SDL2_DIR D:\\Link\\SDL_GCC\\cmake)
    set(SDLTTFDIR E:\\SDL_ttf-main\\build)
    set(FREETYPE_DIR E:\\freetype-master\\ft_gcc\\lib\\cmake\\freetype)
    set(CMAKE_PREFIX_PATH E:\\freetype-master\\ft_gcc D:\\Link\\glfw_gcc12) #E:\\freetype-master\\ft_gcc)
    set(GLEW_ROOT_DIR D:\\Link\\glew)
endif (WIN32)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)
find_package(RTTR CONFIG REQUIRED Core)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL_image REQUIRED)
#GLAD_INCLUDE GLEW_INCLUDE_DIR
include_directories(${SDL2_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS})
include_directories("./imgui")

#${CORE_SRC} ${HEADER_SOURCE} ${ENTITIES_SRC} ${GLAD_SRC}
add_executable(palka ${CORE_SRC} ${HEADER_SOURCE} ${ENTITIES_SRC} ${IMGUI2_SRC})
#GLEW_LIBRARY GLUT_LIBRARY
target_link_libraries(palka mingw32 ${SDLTTF_LIBRARY} Freetype::Freetype SDL2::SDL2main SDL2::SDL2 ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} glfw ${SDL_IMAGE_LIBRARIES} RTTR::Core imm32)

target_compile_definitions(palka PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW GL_GLEXT_PROTOTYPES=1)
