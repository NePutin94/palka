cmake_minimum_required(VERSION 3.19)
project(palka)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++20")

if (WIN32)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -mwindows -s")
    endif ()
ENDIF ()

IF (UNIX)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -s")
    endif ()
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF ()

include(FetchContent)

set(BUILD_UNIT_TESTS OFF)
set(BUILD_STATIC OFF)
set(BUILD_BENCHMARKS OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_DOCUMENTATION OFF)
FetchContent_Declare(
        rttr
        GIT_REPOSITORY https://github.com/rttrorg/rttr.git
        # GIT_TAG 7edbd580cfad509a3253c733e70144e36f02ecd4
)
set(BUILD_RTTR_DYNAMIC ON)
set(BUILD_UNIT_TESTS OFF)
set(BUILD_STATIC OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_DOCUMENTATION OFF)
FetchContent_MakeAvailable(rttr)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG "3.3.5"
)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(BUILD_SHARED_LIBS ON)
FetchContent_MakeAvailable(glfw)


set(FMT_DOC OFF)
set(FMT_TEST OFF)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        # GIT_TAG 7edbd580cfad509a3253c733e70144e36f02ecd4
)
FetchContent_MakeAvailable(fmt)


FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG "0.9.9.8"
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG "v3.8.1"
)
FetchContent_MakeAvailable(entt)

set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF)
FetchContent_Declare(
        tinygltf
        GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
)
FetchContent_MakeAvailable(tinygltf)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG "v5.1.3"
)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ZLIB ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)
set(ASSIMP_BUILD_FBX_IMPORTER ON)
FetchContent_MakeAvailable(assimp)

add_executable(palka "main.cpp")
add_subdirectory(glad)
add_subdirectory(imgui_glfw)
add_subdirectory(imgui)
add_subdirectory(stb)
add_subdirectory(palka_core)
target_link_libraries(palka PalkaCore)
if (WIN32)
    add_custom_command(TARGET palka POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:RTTR::Core>
            $<TARGET_FILE:fmt::fmt>
            $<TARGET_FILE:assimp::assimp>
            $<TARGET_FILE:tinygltf>
            $<TARGET_FILE:glfw>
            $<TARGET_FILE:PalkaCore>
            $<TARGET_FILE_DIR:palka>)
endif ()
#install(TARGETS PalkaCore DESTINATION ${CMAKE_BINARY_DIR})