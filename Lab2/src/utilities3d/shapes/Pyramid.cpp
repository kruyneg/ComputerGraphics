#include "Pyramid.hpp"

#include <glm/gtc/matrix_transform.hpp>

Pyramid::Pyramid() {
    __points = {
        Vertex3({-1, -1, -1}, sf::Color::Red),
        Vertex3({0, 0, 1}, sf::Color::Red),
        Vertex3({-1, 1, -1}, sf::Color::Red),
        Vertex3({0, 0, 1}, sf::Color::Magenta),
        Vertex3({1, 1, -1}, sf::Color::Magenta),
        Vertex3({0, 0, 1}, sf::Color::Blue),
        Vertex3({1, -1, -1}, sf::Color::Blue),
        Vertex3({0, 0, 1}, sf::Color::Cyan),
        Vertex3({-1, -1, -1}, sf::Color::Cyan),

        Vertex3({-1, -1, -1}, sf::Color::White),
        Vertex3({1, -1, -1}, sf::Color::White),
        Vertex3({-1, 1, -1}, sf::Color::White),
        Vertex3({1, 1, -1}, sf::Color::White),

    };
    __points.setPrimitiveType(draw_type);
}

void Pyramid::setPosition(const glm::vec3& position) {
    __points.transform(glm::translate(glm::mat4(1), position - getPosition()));
}
glm::vec3 Pyramid::getPosition() const {
    auto floor = (__points[0].position + __points[2].position +
                  __points[4].position + __points[6].position) /
                 4.0f;
    auto top = __points[1].position;

    return (top + floor) / 2.0f;
}

void Pyramid::setColor(const sf::Color& color) {
    for (size_t i = 0; i < __points.getVertexCount(); ++i) {
        __points[i].color = color;
    }
}

void Pyramid::transform(const glm::mat4& matrix) {
    auto pos = getPosition();
    this->setPosition({0, 0, 0});
    __points.transform(matrix);
    this->setPosition(glm::translate(glm::mat4(1), glm::vec3(matrix[3])) *
                      glm::vec4(pos, 1));
}

void Pyramid::draw(sf::RenderTarget& target, const glm::mat4& transform) const {
    __points.draw(target, transform);
}