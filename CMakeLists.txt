cmake_minimum_required(VERSION 3.10)

project(ComputerGraphics)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
    GIT_SHALLOW    TRUE
)

set(FETCHCONTENT_QUIET OFF)

FetchContent_MakeAvailable(sfml)

find_package(OpenGL REQUIRED)

add_subdirectory(Lab1)