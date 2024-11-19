add_library(shapes4 src/shapes/Cube.cpp)
target_link_libraries(shapes4 sfml-graphics OpenGL::GL GLEW::GLEW)

add_library(camera4 src/camera/Camera.cpp)
target_link_libraries(camera4 sfml-graphics OpenGL::GL GLEW::GLEW)

add_library(textures4 src/texture/Texture.cpp)
target_link_libraries(textures4 sfml-graphics OpenGL::GL GLEW::GLEW)

add_library(shaders4 src/shader/Shader.cpp)
target_link_libraries(shaders4 textures4 sfml-graphics OpenGL::GL GLEW::GLEW)

add_executable(lab4 src/main.cpp)
target_link_libraries(lab4 PUBLIC shapes4 camera4 shaders4 PRIVATE sfml-graphics OpenGL::GL GLEW::GLEW)
