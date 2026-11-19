cmake_minimum_required(VERSION 3.14)
project(raylib_editor LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Disable raylib's built-in examples and games
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

# Build raylib submodule (compiled as C)
add_subdirectory(external/raylib)

# Define your C++ editor executable
add_executable(editor
    src/buffer.cpp
    src/cursor.cpp
    src/main.cpp
)

# Enable strict compiler warnings for your C++ code
if(MSVC)
    target_compile_options(editor PRIVATE /W4)
else()
    target_compile_options(editor PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(editor PRIVATE raylib)

if(APPLE)
    target_link_libraries(editor PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()
