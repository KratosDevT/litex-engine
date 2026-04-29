cmake_minimum_required(VERSION 3.16)
project(litex)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_library(litex STATIC
    src/litex.cpp
    src/particle.cpp
    src/renderer.cpp
)

target_include_directories(litex PUBLIC include)
target_link_libraries(litex PUBLIC SDL3::SDL3 SDL3_ttf::SDL3_ttf)

add_executable(tests tests/main.cpp)
target_link_libraries(tests PRIVATE litex)