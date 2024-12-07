add_library(scene5 src/Scene.hpp src/Scene.cpp)
target_link_libraries(scene5 PRIVATE sfml-graphics)

add_executable(lab5 src/main.cpp)
target_link_libraries(lab5 PUBLIC scene5 PRIVATE sfml-graphics OpenGL::GL)
