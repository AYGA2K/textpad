cmake_minimum_required(VERSION 3.15)
project(textpad LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt REQUIRED)

add_executable(textpad src/main.cpp)
target_link_libraries(textpad PRIVATE fmt::fmt)

target_compile_options(textpad PRIVATE $<$<CONFIG:Release>:-g>)
target_link_options(textpad PRIVATE $<$<CONFIG:Release>:-g>)
