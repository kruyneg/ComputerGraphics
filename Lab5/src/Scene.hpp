#pragma once
#include <vector>

#include "camera/Camera.hpp"
#include "shapes/Shape.hpp"
#include <SFML/Graphics.hpp>

class Scene {
    const int MAX_DEPTH = 10;
    const int SAMPLES = 100;
   public:
    Scene(Camera cam, const std::vector<Shape*>& shapes)
        : _m_camera(cam), _m_shapes(shapes) {}

    float range() {
        return (float)std::rand() / (float)RAND_MAX;
    }
    void render(sf::Image&);
    glm::vec3 get_color(Ray&, Shape*, int);
   private:
    Camera _m_camera;
    std::vector<Shape*> _m_shapes;
};