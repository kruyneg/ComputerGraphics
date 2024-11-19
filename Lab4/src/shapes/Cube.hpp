#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

// Класс для отрисовки и передачи в шейдер вершин куба.
// Передаёт вершины следующим образом:
//  - 0 vec3 position
//  - 1 vec2 texture coord
//  - 2 vec3 normal
class Cube {
  public:
    Cube(const glm::f32 &len = 1.0f);
    ~Cube();
    void draw() const;

  private:
    uint VAO, VBO, EBO;
};