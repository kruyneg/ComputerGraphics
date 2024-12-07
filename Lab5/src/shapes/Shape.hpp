#pragma once
#include <glm/glm.hpp>

#include "../ray.hpp"

class Shape;

struct Hit {
    bool hit;
    glm::vec3 point;
    glm::vec3 normal;
    float ray_length;
    glm::vec3 color;
    Shape* hit_shape;
};

class Shape {
   public:
    Shape(glm::vec3 pos, float mirror, bool light)
        : position(pos), mirror(mirror), light(light) {}
    virtual Hit has_hit(const Ray& ray) = 0;
    inline float get_mirror() const {
        return mirror;
    }
    inline bool is_light() const {
        return light;
    }
    inline glm::vec3 get_position() const {
        return position;
    }

   protected:
    glm::vec3 position;
    float mirror;
    bool light;
};