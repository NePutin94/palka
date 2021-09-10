cmake_minimum_required(VERSION 3.19)

project(PalkaCore)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} CACHE STRING "" )

#file(GLOB_RECURSE SOURCE_FILES RELATIVE "${CMAKE_SOURCE_DIR}/palka_core" "../palka_core/*.cpp")
#file(GLOB_RECURSE HEADER_FILES RELATIVE "${CMAKE_SOURCE_DIR}/palka_core" "../palka_core/*.h")

file(GLOB_RECURSE IMGUI2_SRC RELATIVE "${CMAKE_SOURCE_DIR}/palka_core" "../imgui/*.cpp")
file(GLOB_RECURSE IMGUI2_HEADER RELATIVE "${CMAKE_SOURCE_DIR}/palka_core" "../imgui/*.h")
file(GLOB_RECURSE CORE_SRC RELATIVE "${CMAKE_SOURCE_DIR}/palka_core" "../palka_core/*.cpp")
set(HEADER_SOURCE Matrix.h ReflectionDebug.h Drawable.h)
set(RTTR_DIR "D:\\Link\\rttr_gcc\\cmake")
set(CMAKE_MODULE_PATH "E:\\ClionProject\\palka\\cmake")
set(FREETYPE_DIR E:\\freetype-master\\ft_gcc\\lib\\cmake\\freetype)
set(CMAKE_PREFIX_PATH E:\\freetype-master\\ft_gcc D:\\Link\\glfw_gcc12 E:\\freeglut-3.2.1\\build\\lib\\cmake\\FreeGLUT)
set(GLEW_ROOT_DIR D:\\Link\\glew)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(Freetype REQUIRED)
find_package(RTTR CONFIG REQUIRED Core)

#GLAD_INCLUDE GLEW_INCLUDE_DIR ${SDL2_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS}

#${CORE_SRC} ${HEADER_SOURCE} ${ENTITIES_SRC} ${GLAD_SRC} ${CORE_SRC} ${HEADER_SOURCE}
#add_executable(PalkaCore ${CORE_SRC} ${HEADER_SOURCE} ${IMGUI2_SRC} ${IMGUI2_HEADER})
#GLEW_LIBRARY GLUT_LIBRARY ${SDLTTF_LIBRARY} SDL2::SDL2main SDL2::SDL2 ${SDL_IMAGE_LIBRARIES}
add_library(PalkaCore SHARED ${CORE_SRC} ${IMGUI2_SRC} ${HEADER_SOURCE})
#set_target_properties(PalkaCore PROPERTIES
#        IMPORTED_LOCATION "${CMAKE_BINARY_DIR}"
#        )
#Freetype::Freetype

target_link_libraries(PalkaCore PUBLIC mingw32 ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} glfw RTTR::Core imm32 ws2_32 dwmapi)
target_compile_definitions(PalkaCore PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW GL_GLEXT_PROTOTYPES=1)
target_include_directories(PalkaCore PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR})
target_include_directories(PalkaCore PUBLIC "../imgui")


