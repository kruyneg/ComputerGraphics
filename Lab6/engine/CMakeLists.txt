include(FetchContent)

# # Fetch Assimp library
# FetchContent_Declare(
#     assimp
#     GIT_REPOSITORY https://github.com/assimp/assimp.git
#     GIT_TAG v5.2.5 # Specify the version/tag you want to use
# )
# set(ASSIMP_CXX_FLAGS "-Wno-dangling-reference" CACHE STRING "" FORCE)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ASSIMP_CXX_FLAGS}")
# FetchContent_MakeAvailable(assimp)

include_directories(${sfml_SOURCE_DIR}/include)
include_directories(${assimp_SOURCE_DIR}/include)

file(GLOB_RECURSE ENGINE_HEADERS 
    include/*.hpp
)

file(GLOB_RECURSE ENGINE_SOURCES 
    src/*.cpp
)

message("engine sources: ${ENGINE_SOURCES}")
message("engine headers: ${ENGINE_HEADERS}")

add_library(computer-graphics-engine STATIC 
    ${ENGINE_SOURCES} 
    ${ENGINE_HEADERS}
)

# Properly link Assimp include directories
target_link_libraries(computer-graphics-engine PRIVATE 
    sfml-graphics sfml-system sfml-window 
    OpenGL::GL GLEW::GLEW
    assimp
)
target_include_directories(computer-graphics-engine PRIVATE ${assimp_BINARY_DIR}/include)
target_include_directories(computer-graphics-engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
