
add_subdirectory(engine)
include_directories(./engine/include)

include_directories(${sfml_SOURCE_DIR}/include)
include_directories(${assimp_SOURCE_DIR}/include)
add_executable(lab6 src/main.cpp)
target_link_libraries(lab6 computer-graphics-engine)
