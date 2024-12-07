#pragma once
#include <SFML/Graphics.hpp>

#include "Shape.hpp"

class Plane final : public Shape {
   public:
    Plane(glm::vec3 center, glm::vec3 u, glm::vec3 v, glm::vec2 size,
          float mirror, const sf::Image& tex)
        : Shape(center, mirror, false), u(u), v(v), _m_size(size / 2.0f), _m_texture(tex) {}

    Hit has_hit(const Ray& ray) override;

   private:
    glm::vec3 get_tex_color(glm::vec3 point);

    glm::vec2 _m_size;
    sf::Image _m_texture;
    glm::vec3 u, v;
};

inline Hit Plane::has_hit(const Ray& ray) {
    Hit res;
    res.hit_shape = this;
    res.hit = false;
    const float EPSILON = 1e-6;

    // Нормаль прямоугольника
    glm::vec3 normal = -glm::cross(u, v);
    res.normal = normal;
    float denom = glm::dot(normal, ray.get_direction());

    // Проверка на параллельность
    if (fabs(denom) < EPSILON) {
        return res;
    }

    // Найти t для пересечения с плоскостью
    float t = glm::dot(normal, position - ray.get_origin()) / denom;

    // Если пересечение за началом луча
    if (t < 0) {
        return res;
    }

    // Найти точку пересечения
    res.point = ray.get_origin() + t * ray.get_direction();

    // Проверить, лежит ли точка внутри прямоугольника
    glm::vec3 hit_vec = res.point - position;

    // Проекции на стороны
    float u_proj = glm::dot(hit_vec, u) / glm::dot(u, u);
    float v_proj = glm::dot(hit_vec, v) / glm::dot(v, v);

    if (u_proj >= -_m_size.x && u_proj <= _m_size.x && v_proj >= -_m_size.y &&
        v_proj <= _m_size.y) {
        res.hit = true;
        res.ray_length = glm::length(res.point - ray.get_origin());
        res.color = get_tex_color(res.point);
        return res;
    }

    return res;
}

inline glm::vec3 Plane::get_tex_color(glm::vec3 point) {
    glm::vec3 hit_vec = point - position;

    float u_coord = glm::dot(hit_vec, u) / glm::dot(u, u);
    float v_coord = glm::dot(hit_vec, v) / glm::dot(v, v);

    // Нормализовать координаты в диапазон [0, 1]
    float u_norm = (u_coord + _m_size.x) / (2.0f * _m_size.x);
    float v_norm = (v_coord + _m_size.y) / (2.0f * _m_size.y);

    // Преобразовать в пиксельные координаты
    unsigned int tex_width = _m_texture.getSize().x;
    unsigned int tex_height = _m_texture.getSize().y;

    unsigned int tex_x = static_cast<unsigned int>(u_norm * tex_width);
    unsigned int tex_y = static_cast<unsigned int>(v_norm * tex_height);

    // Получить цвет пикселя из текстуры
    auto res = _m_texture.getPixel(tex_x, tex_y);
    return {static_cast<float>(res.r) / 255, static_cast<float>(res.g) / 255,
            static_cast<float>(res.b) / 255};
}