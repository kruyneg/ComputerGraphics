add_executable(lab1 src/main.cpp)
target_link_libraries(lab1 PRIVATE sfml-graphics OpenGL::GL)

add_executable(zhz src/try_zhz.cpp)
target_link_libraries(zhz PRIVATE sfml-graphics OpenGL::GL)