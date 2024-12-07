#pragma once
#include <glm/glm.hpp>

class Ray {
    glm::vec3 origin;
    glm::vec3 direction;

   public:
    Ray() : origin(), direction() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction);

    glm::vec3 get_origin() const;
    glm::vec3 get_direction() const;

    glm::vec3 at(float t) const;
};

inline Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) {
    this->origin = glm::vec3(origin);
    this->direction = glm::vec3(direction);
}

inline glm::vec3 Ray::get_origin() const { return this->origin; }

inline glm::vec3 Ray::get_direction() const { return this->direction; }

inline glm::vec3 Ray::at(float t) const { return origin + direction * t; }
