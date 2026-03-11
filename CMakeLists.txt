cmake_minimum_required(VERSION 3.16)
project(litex)

set(CMAKE_CXX_STANDARD 23)

add_library(litex STATIC
    src/litex.cpp
)

target_include_directories(litex PUBLIC include)

add_executable(tests tests/main.cpp)
target_link_libraries(tests litex)