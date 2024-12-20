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

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.4.3 # Specify the version/tag you want to use
)
# Убедимся, что Assimp собирается корректно
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
set(ASSIMP_CXX_FLAGS "-Wno-dangling-reference" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ASSIMP_CXX_FLAGS}")

set(FETCHCONTENT_QUIET OFF)

FetchContent_MakeAvailable(sfml)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(assimp)

include_directories(${glm_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(Lab1)
add_subdirectory(Lab2)
add_subdirectory(Lab4)
add_subdirectory(Lab5)
add_subdirectory(Lab6)