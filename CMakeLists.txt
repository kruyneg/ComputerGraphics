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

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)

set(FETCHCONTENT_QUIET OFF)

FetchContent_MakeAvailable(sfml)
FetchContent_MakeAvailable(glm)

include_directories(${glm_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(Lab1)
add_subdirectory(Lab2)
add_subdirectory(Lab4)
