#include "Cube.hpp"

#include <glm/gtc/matrix_transform.hpp>

Cube::Cube() {
    __points = {
        // Front face
        Vertex3({-1.0, -1.0, 1.0}, sf::Color::White),
        Vertex3({1.0, -1.0, 1.0}, sf::Color::White),
        Vertex3({1.0, 1.0, 1.0}, sf::Color::White),
        Vertex3({-1.0, 1.0, 1.0}, sf::Color::White),

        // Back face
        Vertex3({-1.0, -1.0, -1.0}, sf::Color::White),
        Vertex3({-1.0, 1.0, -1.0}, sf::Color::White),
        Vertex3({1.0, 1.0, -1.0}, sf::Color::White),
        Vertex3({1.0, -1.0, -1.0}, sf::Color::White),

        // Left face
        Vertex3({-1.0, -1.0, -1.0}, sf::Color::White),
        Vertex3({-1.0, -1.0, 1.0}, sf::Color::White),
        Vertex3({-1.0, 1.0, 1.0}, sf::Color::White),
        Vertex3({-1.0, 1.0, -1.0}, sf::Color::White),

        // Right face
        Vertex3({1.0, -1.0, -1.0}, sf::Color::White),
        Vertex3({1.0, 1.0, -1.0}, sf::Color::White),
        Vertex3({1.0, 1.0, 1.0}, sf::Color::White),
        Vertex3({1.0, -1.0, 1.0}, sf::Color::White),

        // Top face
        Vertex3({-1.0, 1.0, -1.0}, sf::Color::White),
        Vertex3({-1.0, 1.0, 1.0}, sf::Color::White),
        Vertex3({1.0, 1.0, 1.0}, sf::Color::White),
        Vertex3({1.0, 1.0, -1.0}, sf::Color::White),

        // Bottom face
        Vertex3({-1.0, -1.0, -1.0}, sf::Color::White),
        Vertex3({1.0, -1.0, -1.0}, sf::Color::White),
        Vertex3({1.0, -1.0, 1.0}, sf::Color::White),
        Vertex3({-1.0, -1.0, 1.0}, sf::Color::White),
    };
    Shape::__points.setPrimitiveType(draw_type);
}

Cube::Cube(const glm::f32& len) : Cube() {
    Shape::__points.transform(
        glm::scale(glm::mat4(1), glm::vec3{len, len, len} / 2.0f));
}

void Cube::setPosition(const glm::vec3& position) {
    auto delta = position - getPosition();
    Shape::__points.transform(
        glm::translate(glm::mat4(1), position - getPosition()));
}
glm::vec3 Cube::getPosition() const {
    return (__points[2].position + __points[4].position) / 2.0f;
}

void Cube::setColor(const sf::Color& color) {
    for (std::size_t i = 0; i < Shape::__points.getVertexCount(); ++i) {
        Shape::__points[i].color = color;
    }
}
void Cube::setColor(const std::vector<sf::Color>& colors) {
    assert(colors.size() == 6);
    for (std::size_t i = 0, col = 0; i < Shape::__points.getVertexCount();
         ++i) {
        if (i > 0 && i % 4 == 0) {
            ++col;
        }
        Shape::__points[i].color = colors[col];
    }
}

void Cube::transform(const glm::mat4& matrix) {
    auto pos = getPosition();
    this->setPosition({0, 0, 0});
    __points.transform(matrix);
    this->setPosition(glm::translate(glm::mat4(1), glm::vec3(matrix[3])) *
                      glm::vec4(pos, 1));
}

void Cube::draw(sf::RenderTarget& window, const glm::mat4& transform) const {
    return Shape::__points.draw(window, transform);
}