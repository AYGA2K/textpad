cmake_minimum_required(VERSION 3.20)
project(textpad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

fetchcontent_declare(
raylib
GIT_REPOSITORY https://github.com/raysan5/raylib.git
GIT_TAG master
GIT_SHALLOW TRUE
)
fetchcontent_makeavailable(raylib)

fetchcontent_declare(
raygui
GIT_REPOSITORY https://github.com/raysan5/raygui.git
GIT_TAG master
GIT_SHALLOW TRUE
)
fetchcontent_makeavailable(raygui)

add_executable(textpad src/main.cpp src/explorer.cpp src/editor.cpp)

target_include_directories(textpad PRIVATE ${raygui_SOURCE_DIR}/src)
target_link_libraries(textpad PRIVATE raylib)
set_source_files_properties(src/main.cpp PROPERTIES COMPILE_DEFINITIONS RAYGUI_IMPLEMENTATION)
target_compile_options(textpad PRIVATE -Wall -Wextra -Wpedantic)
