#include "Sphere.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Sphere::Sphere(const glm::float32 radius, const int steps, const int points) {
    std::vector<glm::vec3> sphere_cells;
    sphere_cells.reserve(2 + steps * points);

    sphere_cells.push_back({0, 0, 1});
    for (size_t h = 0; h < steps; ++h) {
        for (size_t k = 0; k < points; ++k) {
            auto phi = M_PI / (steps + 1) * (h + 1);
            auto height = glm::cos(phi) * radius;
            auto cur_rad = glm::sin(phi) * radius;
            auto cur_angle = 2.0 * M_PI / points * k;
            sphere_cells.push_back({cur_rad * glm::cos(cur_angle),
                                    cur_rad * glm::sin(cur_angle), height});
        }
    }
    sphere_cells.push_back({0, 0, -1});

    for (size_t i = 1; i < points; ++i) {
        __points.append(Vertex3(sphere_cells[i], sf::Color::Red));
        __points.append(Vertex3(sphere_cells[0], sf::Color::Green));
        __points.append(Vertex3(sphere_cells[i + 1], sf::Color::Blue));
    }
    __points.append(Vertex3(sphere_cells[points], sf::Color::Red));
    __points.append(Vertex3(sphere_cells[0], sf::Color::Green));
    __points.append(Vertex3(sphere_cells[1], sf::Color::Blue));


    for (size_t h = 1; h < steps; ++h) {
        for (size_t i = 1; i < points; ++i) {
            __points.append(
                Vertex3(sphere_cells[(h - 1) * points + i], sf::Color::Green));
            __points.append(Vertex3(sphere_cells[h * points + i], sf::Color::Red));
            __points.append(
                Vertex3(sphere_cells[(h - 1) * points + i + 1], sf::Color::Blue));

            __points.append(
                Vertex3(sphere_cells[h * points + i], sf::Color::Red));
            __points.append(
                Vertex3(sphere_cells[h * points + i + 1], sf::Color::Green));
            __points.append(
                Vertex3(sphere_cells[(h - 1) * points + i + 1], sf::Color::Blue));
        }
        __points.append(
            Vertex3(sphere_cells[(h - 1) * points + points], sf::Color::Yellow));
        __points.append(Vertex3(sphere_cells[h * points + points], sf::Color::Magenta));
        __points.append(
            Vertex3(sphere_cells[(h - 1) * points + 1], sf::Color::Cyan));

        __points.append(Vertex3(sphere_cells[h * points + points], sf::Color::Magenta));
        __points.append(Vertex3(sphere_cells[h * points + 1], sf::Color::Yellow));
        __points.append(
            Vertex3(sphere_cells[(h - 1) * points + 1], sf::Color::Cyan));
    }

    for (size_t i = sphere_cells.size() - 2; i > sphere_cells.size() - points - 1; --i) {
        __points.append(Vertex3(sphere_cells[i], sf::Color::Red));
        __points.append(Vertex3(sphere_cells.back(), sf::Color::Green));
        __points.append(Vertex3(sphere_cells[i - 1], sf::Color::Blue));
    }
    __points.append(Vertex3(sphere_cells[sphere_cells.size() - points - 1], sf::Color::Magenta));
    __points.append(Vertex3(sphere_cells.back(), sf::Color::Yellow));
    __points.append(Vertex3(sphere_cells[sphere_cells.size() - 2], sf::Color::Cyan));

    __points.setPrimitiveType(draw_type);
}

void Sphere::setPosition(const glm::vec3& position) {
    __points.transform(glm::translate(glm::mat4(1), position - getPosition()));
}
glm::vec3 Sphere::getPosition() const {
    return (__points[0].position +
            __points[__points.getVertexCount() - 1].position) /
           2.0f;
}

void Sphere::setColor(const sf::Color& color) {
    for (size_t i = 0; i < __points.getVertexCount(); ++i) {
        __points[i].color = color;
    }
}

void Sphere::draw(sf::RenderTarget& target, const glm::mat4& transform) const {
    __points.draw(target, transform);
}