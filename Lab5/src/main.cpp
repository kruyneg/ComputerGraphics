#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "camera/Camera.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Plane.hpp"

constexpr float Scale = 5;

int main() {
    const float Radius = Scale / 3;
    Camera cam(400, 400.f / 9 * 16, {0, 0, 0.0001}, {0, -Scale / 2.0f + Radius, Scale});

    sf::Image img, tex_floor, tex_wall, tex_roof;
    img.create(400.f / 9 * 16, 400);
    tex_roof.create(2 * Scale, 2 * Scale, {200, 0, 0});
    tex_floor.loadFromFile("/home/kruyneg/Изображения/road_asphalt_seamless_texture_6636.jpg");
    tex_wall.loadFromFile("/home/kruyneg/Изображения/50-free-textures-4+normalmaps/154.JPG");
    Plane roof({0, Scale / 2.0f, Scale}, {0, 0, 1}, {1, 0, 0}, {2.0f * Scale, 2.0f * Scale}, 0, tex_roof);
    Plane floor({0, -Scale / 2, Scale}, {1, 0, 0}, {0, 0, 1}, {2.0f * Scale, 2.0f * Scale * 3}, 0.1, tex_floor);
    Plane wall1({-Scale, 0, 2.0f * Scale}, {0, 0, 1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);
    // Plane wall2({0, 0, 2.0f * Scale}, {1, 0, 0}, {0, 1, 0}, {2.0f * Scale, Scale}, 1, tex_wall);
    Plane wall2({-Scale, 0, 0}, {0, 0, 1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);
    Plane wall3({Scale, 0, 2.0f * Scale}, {0, 0, -1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);
    // Plane wall4({0, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {2.0f * Scale, Scale}, 1, tex_wall);
    Plane wall4({Scale, 0, 0}, {0, 0, -1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);

    Sphere sphere({0, -Scale / 2.0f + Radius, Scale}, {0.9, 0.9, 0.9}, Radius, 1.0f, false);
    std::vector<Shape*> shapes_ptr;
    // shapes_ptr.push_back(&roof);
    shapes_ptr.push_back(&floor);
    shapes_ptr.push_back(&wall1);
    shapes_ptr.push_back(&wall2);
    shapes_ptr.push_back(&wall3);
    shapes_ptr.push_back(&wall4);
    shapes_ptr.push_back(&sphere);

    Scene scene(cam, shapes_ptr);

    scene.render(img);
    img.saveToFile(
        "/home/kruyneg/Programming/ComputerGraphics/Lab5/result/output.png");
}