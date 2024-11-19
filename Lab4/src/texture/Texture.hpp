#pragma once

#include <GL/glew.h>

#include <GL/gl.h>

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

// текстура, которую можно передать в шейдер
class Texture {
  public:
    // ID текстуры в OpenGL
    uint ID;

    // создание текстуры из изображения и указание её индекса
    Texture(const sf::Image &image, const uint index = 0);
    ~Texture();

    uint getIndex() const;
    void setIndex(const uint& index);

    glm::uvec2 getSize() const;

  private:
    uint _m_index;
    glm::uvec2 _m_size;
};