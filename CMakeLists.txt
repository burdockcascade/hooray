cmake_minimum_required(VERSION 3.28)
project(hooray LANGUAGES CXX)

# Require C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include the FetchContent module
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

add_library(hooray STATIC
        src/application.cpp
        src/color.cpp
)

target_include_directories(hooray PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(hooray PUBLIC cxx_std_23)
target_link_libraries(hooray PUBLIC raylib)

add_subdirectory(examples)
