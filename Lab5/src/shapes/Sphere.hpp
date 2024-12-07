#pragma once
#include "Shape.hpp"

class Sphere final : public Shape {
   public:
    Sphere(glm::vec3 center, glm::vec3 color, float radius, float mirror, bool light)
        : Shape(center, mirror, light), _m_color(color), _m_radius(radius) {}

    Hit has_hit(const Ray& ray) override;

    inline glm::vec3 get_color() const {
        return _m_color;
    }

   private:
    float _m_radius;
    glm::vec3 _m_color;
};

inline Hit Sphere::has_hit(const Ray& ray) {
    Hit res;
    res.hit = false;

    // решаем уравнение
    // (t * D + (A - C))^2 = r^2
    // t - кусок луча
    // D - вектор направления луча
    // A - точка, откуда летит луч
    // C - центр сферы
    // r - радиус сферы

    float a = glm::dot(ray.get_direction(), ray.get_direction());
    float b = 2 * glm::dot(ray.get_direction(),
                           (ray.get_origin() - position));
    float c = glm::dot((ray.get_origin() - position),
                       (ray.get_origin() - position)) -
              _m_radius * _m_radius;
    
    float delta = b * b - 4 * a * c;
    if (delta > 0) {
        res.hit = true;
        float t1 = (-b - glm::sqrt(delta)) / 2.0f * a;
        float t2 = (-b + glm::sqrt(delta)) / 2.0f * a;

        float len1 = glm::length(ray.at(t1));
        float len2 = glm::length(ray.at(t2));
        if (len1 <= len2) {
            res.ray_length = len1;
            res.point = ray.at(t1);
        } else {
            res.ray_length = len2;
            res.point = ray.at(t2);
        }
        res.normal = glm::normalize(res.point - position);

        if (glm::dot(ray.get_direction(), (res.point - ray.get_origin())) <= 0) {
            // if the ray hit the sphere in the opposite direction
            res.hit = false;
        }
        if (glm::dot(ray.get_direction(), res.normal) > 0) {
            // if the ray hit the sphere in the inside
            res.hit = false;
        }
        res.color = _m_color;
        res.hit_shape = this;
    }
    return res;
}