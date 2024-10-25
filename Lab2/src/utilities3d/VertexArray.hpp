#pragma once

#include <GL/gl.h>

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class Vertex3 {
   public:
    Vertex3() : position(0, 0, 0), color() {}

    Vertex3(const glm::vec3& thePosition) : position(thePosition), color() {}

    Vertex3(const glm::vec3& thePosition, const sf::Color& theColor)
        : position(thePosition), color(theColor) {}

    glm::vec3 position;
    sf::Color color;
};

class Vertex3Array {
   public:
    Vertex3Array() : __vertices(), __type() {}

    Vertex3Array(sf::PrimitiveType type, std::size_t vertexCount = 0)
        : __type(type), __vertices(vertexCount) {}

    Vertex3Array(std::initializer_list<Vertex3> list)
        : __vertices(list), __type() {}

    std::size_t getVertexCount() const { return __vertices.size(); }

    Vertex3& operator[](std::size_t index) { return __vertices[index]; }

    const Vertex3& operator[](std::size_t index) const {
        return __vertices[index];
    }

    void clear() { __vertices.clear(); }

    void resize(std::size_t vertexCount) { __vertices.resize(vertexCount); }

    void append(const Vertex3& vertex) { __vertices.push_back(vertex); }

    void setPrimitiveType(sf::PrimitiveType type) { __type = type; }

    sf::PrimitiveType getPrimitiveType() { return __type; }

    void transform(const glm::mat4& matrix) {
        for (auto& v : __vertices) {
            glm::vec4 new_vec(v.position, 1.0f);
            new_vec = matrix * new_vec;
            v.position = glm::vec3(new_vec);
        }
    }

    void draw(sf::RenderTarget& target,
              const glm::mat4& transform = glm::mat4(1)) const {
        target.setActive(true);
        auto copy_vertices = __vertices;

        static const GLenum modes[] = {
            GL_POINTS,         GL_LINES,        GL_LINE_STRIP, GL_TRIANGLES,
            GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS};
        GLenum mode = modes[__type];

        for (auto& v : copy_vertices) {
            glm::vec4 new_vec(v.position, 1.0f);
            v.position = glm::vec3(transform * new_vec);
        }
        auto data = reinterpret_cast<const std::byte*>(copy_vertices.data());

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, sizeof(Vertex3), data);
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3), data + 12);

        glDrawArrays(mode, 0, __vertices.size());

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

   private:
    std::vector<Vertex3> __vertices;
    sf::PrimitiveType __type;
};
