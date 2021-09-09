cmake_minimum_required(VERSION 3.19)
project(palka)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++20")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -mwindows -DNDEBUG -s")
endif()

add_executable(palka "main.cpp")
add_subdirectory(palka_core)
target_link_libraries(palka PalkaCore)


