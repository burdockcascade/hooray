cmake_minimum_required(VERSION 3.28)
project(hooray LANGUAGES CXX)

# Require C++23 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include the FetchContent module
include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "" FORCE)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.2
)
add_compile_definitions(SUPPORT_FILEFORMAT_JPG)

FetchContent_MakeAvailable(raylib)

add_library(hooray STATIC
        src/scenerunner.cpp
        src/scenegraph.cpp
)

target_include_directories(hooray PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(hooray PUBLIC raylib)

add_subdirectory(examples)
