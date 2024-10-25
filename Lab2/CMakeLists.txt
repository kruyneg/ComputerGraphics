add_library(shapes 
            src/utilities3d/VertexArray.hpp
            src/utilities3d/shapes/Shape.hpp
            src/utilities3d/shapes/Cube.cpp
            src/utilities3d/shapes/Cube.hpp
            src/utilities3d/shapes/Sphere.hpp
            src/utilities3d/shapes/Sphere.cpp
            src/utilities3d/shapes/Pyramid.hpp
            src/utilities3d/shapes/Pyramid.cpp)
# target_include_directories(shapes PUBLIC /home/kruyneg/Programming/ComputerGraphics/build/_deps/glm-src/)
target_link_libraries(shapes PRIVATE sfml-graphics OpenGL::GL)

add_library(camera
            src/utilities3d/camera/Camera.hpp
            src/utilities3d/camera/Camera.cpp)
target_link_libraries(camera PRIVATE sfml-graphics OpenGL::GL)


add_executable(lab2
               src/main.cpp
               src/utilities3d/VertexArray.hpp
               src/utilities3d/VertexArray.hpp
               src/utilities3d/shapes/Cube.hpp)
target_link_libraries(lab2 PUBLIC shapes camera PRIVATE sfml-graphics OpenGL::GL OpenGL::GLU)
# target_include_directories(lab2 PUBLIC /home/kruyneg/Programming/ComputerGraphics/build/_deps/glm-src/)
