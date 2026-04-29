cmake_minimum_required(VERSION 3.16)
project(litex)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

# Physics library — zero external dependencies
add_library(litex STATIC
    src/litex.cpp
    src/particle.cpp
)
target_include_directories(litex PUBLIC include)

# SDL3 layer — renderer + engine, depends on litex
add_library(litex-sdl STATIC
    src/renderer.cpp
    src/engine.cpp
)
target_include_directories(litex-sdl PUBLIC include)
target_link_libraries(litex-sdl PUBLIC litex SDL3::SDL3 SDL3_ttf::SDL3_ttf)

# Unit tests — only physics, no SDL
add_executable(tests tests/main.cpp)
target_link_libraries(tests PRIVATE litex)

# Demo — uses SDL layer
add_executable(demo demo/main.cpp)
target_link_libraries(demo PRIVATE litex-sdl)

add_custom_command(TARGET demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:demo>/assets
)
