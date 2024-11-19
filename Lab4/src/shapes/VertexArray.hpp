#pragma once

#include <GL/glew.h>

#include <GL/gl.h>

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class Vertex3 {
  public:
    Vertex3() : position(0, 0, 0), color() {}

    Vertex3(const glm::vec3 &thePosition) : position(thePosition), color() {}

    Vertex3(const glm::vec3 &thePosition, const sf::Color &theColor)
        : position(thePosition),
          color((float)theColor.r / 255, (float)theColor.g / 255,
                (float)theColor.b / 255, (float)theColor.a / 255) {}

    Vertex3(const glm::vec3 &thePosition, const glm::vec4 &theColor)
        : position(thePosition), color(theColor) {}

    glm::vec3 position;
    glm::vec4 color;
};

// класс для отрисовки и передачи в шейдер массива вершин
class Vertex3Array : public std::vector<Vertex3> {
  public:
    Vertex3Array() : std::vector<Vertex3>(), __type() {}

    Vertex3Array(sf::PrimitiveType type, std::size_t vertexCount = 0)
        : __type(type), std::vector<Vertex3>(vertexCount) {}

    Vertex3Array(std::initializer_list<Vertex3> list)
        : std::vector<Vertex3>(list), __type() {}

    void setPrimitiveType(sf::PrimitiveType type) { __type = type; }

    sf::PrimitiveType getPrimitiveType() { return __type; }

    void draw() const {
        // target.setActive(true);

        static const GLenum modes[] = {
            GL_POINTS,         GL_LINES,        GL_LINE_STRIP, GL_TRIANGLES,
            GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS};
        GLenum mode = modes[__type];

        auto data =
            reinterpret_cast<const std::byte *>(std::vector<Vertex3>::data());

        uint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     std::vector<Vertex3>::size() * sizeof(Vertex3), data,
                     GL_STREAM_DRAW);

        uint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3),
                              nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3),
                              (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(VAO);
        glDrawArrays(mode, 0, std::vector<Vertex3>::size());
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

  private:
    sf::PrimitiveType __type;
};
