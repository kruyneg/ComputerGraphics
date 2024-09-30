cmake_minimum_required(VERSION 3.10)

project(ComputerGraphics)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# FetchContent_Declare(
#     glfw
#     GIT_REPOSITORY https://github.com/glfw/glfw.git
#     GIT_TAG        3.4
# )

# FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/sfml/sfml.git
    GIT_TAG        2.6.1
)

FetchContent_MakeAvailable(sfml)

# костыль
include_directories(build/_deps/sfml-src/include/)

find_package(OpenGL REQUIRED)

add_subdirectory(Lab1)