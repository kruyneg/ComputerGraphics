#include <GL/glew.h>

#include <GL/gl.h>

#include "Window3d.hpp"
#include "camera/Camera.hpp"
#include "shader/Shader.hpp"
#include "shapes/Cube.hpp"
#include <SFML/Graphics.hpp>
#include <format>
#include <iostream>

const std::string shader_dir =
    "/home/kruyneg/Programming/ComputerGraphics/Lab4/shaders/";

const std::string tex_path =
    "/home/kruyneg/Изображения/50-free-textures-4+normalmaps/192.JPG";
const std::string nm_path =
    "/home/kruyneg/Изображения/50-free-textures-4+normalmaps/192_norm.JPG";

auto vertex_shader_path = shader_dir + "vertex.glsl";
auto fragment_shader_path = shader_dir + "fragment.glsl";

int main() {
    Window3d window(sf::VideoMode::getDesktopMode(), "Simple Triangle");
    window.setVerticalSyncEnabled(true);
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(window.getSize()) / 2,
                           window);

    Shader program(vertex_shader_path, fragment_shader_path);
    Shader bulb_prog(shader_dir + "bulb_vertex.glsl",
                     shader_dir + "bulb_fragment.glsl");

    Cube cube;
    Cube bulb(0.1);
    Camera cam;
    float radius = 2;
    float theta = 0, phi = 0;

    sf::Image img, nm;
    img.loadFromFile(tex_path);
    nm.loadFromFile(nm_path);
    nm.flipVertically();
    img.flipVertically();

    Texture texture(img, 0), normap(nm, 1);

    program.use();
    program.setTexture("ourTexture", texture);
    program.setTexture("normalMap", normap);

    bool normalMapEnabled = false, isAltPressed = false;
    glm::vec3 bulbPos = {0, 0, 0};
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    radius -= 0.1;
                } else if (event.mouseWheelScroll.delta < 0) {
                    radius += 0.1;
                }
                // Ограничим минимальный радиус
                if (radius < 0.7)
                    radius = 0.7f;
            }
        }
        if (window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                bulbPos.z -= 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                bulbPos.z += 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                bulbPos.x -= 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                bulbPos.x += 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                bulbPos.y += 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                bulbPos.y -= 0.05;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
                if (!isAltPressed) {
                    normalMapEnabled = !normalMapEnabled;
                    isAltPressed = true;
                }
            } else {
                isAltPressed = false;
            }
        }
        {
            int mouseX = sf::Mouse::getPosition(window).x;
            int mouseY = sf::Mouse::getPosition(window).y;

            int deltaX = mouseX - (float)window.getSize().x / 2;
            int deltaY = mouseY - (float)window.getSize().y / 2;

            sf::Mouse::setPosition(
                static_cast<sf::Vector2i>(window.getSize()) / 2, window);

            theta -= deltaX * 0.01;
            phi += deltaY * 0.01;
        }

        // Ограничим угол поворота камеры
        if (phi > M_PI_2) {
            phi = M_PI_2 - 1e-6;
        }
        if (phi < -M_PI_2) {
            phi = -M_PI_2 - 1e-6;
        }

        cam.setPosition(glm::vec3{radius * sin(theta) * cos(phi),
                                  radius * sin(phi),
                                  radius * cos(theta) * cos(phi)});
        cam.setTarget({0, 0, 0});

        window.clear();

        program.use();
        program.set("lightPos", bulbPos);
        program.set("NMEnabled", normalMapEnabled);
        cam.put(window, program);
        cube.draw();

        bulb_prog.use();
        bulb_prog.set("bulbPos", bulbPos);
        cam.put(window, bulb_prog);
        bulb.draw();

        window.display();
    }
}
