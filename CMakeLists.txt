cmake_minimum_required(VERSION 3.19)
project(palka)
set(CMAKE_CXX_STANDARD 17)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "-O0 -g")
else()
    set(CMAKE_CXX_FLAGS "-O3 -mwindows -DNDEBUG -s")
endif()

file(GLOB_RECURSE IMGUI2_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./imgui/*.cpp")
file(GLOB_RECURSE IMGUI2_HEADER RELATIVE ${CMAKE_SOURCE_DIR} "./imgui/*.h")
#file(GLOB_RECURSE GLAD_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./glad/src/*.c")
#file(GLOB_RECURSE CORE_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./palka_core/*.cpp")
#file(GLOB_RECURSE ENTITIES_SRC RELATIVE ${CMAKE_SOURCE_DIR} "./palka_entities/*.cpp")
#set(HEADER_SOURCE palka_core/Matrix.h palka_core/ReflectionDebug.h palka_core/Drawable.h)

if (WIN32)
    #set(GLAD_INCLUDE "./glad/include")
    set(RTTR_DIR "D:\\Link\\rttr_gcc\\cmake")
    set(CMAKE_MODULE_PATH "E:\\ClionProject\\palka\\cmake")
#    set(SDLIMAGEDIR D:\\Link\\sdlimage_gcc10)
#    set(SDL2_DIR D:\\Link\\SDL_GCC\\cmake)
#    set(SDLTTFDIR E:\\SDL_ttf-main\\build)
    set(FREETYPE_DIR E:\\freetype-master\\ft_gcc\\lib\\cmake\\freetype)
    set(CMAKE_PREFIX_PATH E:\\freetype-master\\ft_gcc D:\\Link\\glfw_gcc12 E:\\freeglut-3.2.1\\build\\lib\\cmake\\FreeGLUT) #E:\\freetype-master\\ft_gcc)
    set(GLEW_ROOT_DIR D:\\Link\\glew)
endif (WIN32)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(RTTR CONFIG REQUIRED Core)
#find_package(FreeGLUT REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(SDL_image REQUIRED)



#GLAD_INCLUDE GLEW_INCLUDE_DIR ${SDL2_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS}
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR})
include_directories("./imgui")

#${CORE_SRC} ${HEADER_SOURCE} ${ENTITIES_SRC} ${GLAD_SRC} ${CORE_SRC} ${HEADER_SOURCE}
add_executable(palka palka_core/main.cpp palka_core/Shader.cpp palka_core/VertexData.cpp palka_core/Color.cpp palka_core/RenderContext.cpp palka_core/Vec2.cpp palka_core/EventManager.cpp palka_core/ConsoleLog.cpp palka_core/Viewport.cpp palka_core/ReflectionDebug.h palka_core/Viewport.cpp stb_image.h stb_image_resize.h stb_image_write.h palka_core/Texture.cpp ${ENTITIES_SRC} ${IMGUI2_SRC} ${IMGUI2_HEADER})
#GLEW_LIBRARY GLUT_LIBRARY ${SDLTTF_LIBRARY} SDL2::SDL2main SDL2::SDL2 ${SDL_IMAGE_LIBRARIES}
target_link_libraries(palka mingw32 Freetype::Freetype ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} glfw RTTR::Core imm32 ws2_32 dwmapi)

target_compile_definitions(palka PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW GL_GLEXT_PROTOTYPES=1)
