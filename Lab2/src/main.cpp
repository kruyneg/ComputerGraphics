#include <GL/gl.h>
#include <GL/glu.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utilities3d/VertexArray.hpp"
#include "utilities3d/camera/Camera.hpp"
#include "utilities3d/shapes/Cube.hpp"
#include "utilities3d/shapes/Pyramid.hpp"
#include "utilities3d/shapes/Sphere.hpp"

void draw_scene(std::vector<Shape*>& scene, sf::RenderWindow& window) {
    for (int i = 0; i < scene.size(); ++i) {
        scene[i]->draw(window, glm::mat4(1));
    }
}

// Начальные значения для углов камеры
float theta = glm::radians(90.0);  // Угол поворота вокруг Z
float phi = glm::radians(90.0);  // Угол наклона вверх/вниз
float radius = 5.0f;  // Расстояние камеры до фигуры

// Переменная для управления скоростью поворота
float angleSpeed = 1e-2;

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "3D Scene",
                            sf::Style::Default, sf::ContextSettings(24));

    window.setVerticalSyncEnabled(true);

    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);
    sf::Vector2i winCenter = {window.getSize().x / 2, window.getSize().y / 2};
    bool isMousePressed = false;
    sf::Mouse::setPosition(winCenter, window);

    // Инициализация OpenGL
    glEnable(GL_DEPTH_TEST);

    Camera cam;
    cam.setPosition({radius * sin(theta) * cos(phi), radius * sin(phi),
                     radius * cos(theta) * cos(phi)});

    Vertex3Array cells(sf::PrimitiveType::Lines);
    for (int64_t i = -99; i < 100; ++i) {
        cells.append(Vertex3({i, -100, -0.99}, sf::Color::Black));
        cells.append(Vertex3({i, 100, -0.99}, sf::Color::Black));
    }
    for (int64_t i = -99; i < 100; ++i) {
        cells.append(Vertex3({-100, i, -0.99}, sf::Color::Black));
        cells.append(Vertex3({100, i, -0.99}, sf::Color::Black));
    }

    Vertex3Array floor{Vertex3({-100, -100, -1}, sf::Color{150, 150, 150}),
                       Vertex3({-100, 100, -1}, sf::Color{150, 150, 150}),
                       Vertex3({100, 100, -1}, sf::Color{150, 150, 150}),
                       Vertex3({100, -100, -1}, sf::Color{150, 150, 150})};
    floor.setPrimitiveType(sf::PrimitiveType::Quads);

    Cube cube;
    cube.setPosition({-3, -3, 0});
    Sphere sphere;
    Pyramid pyr;
    pyr.setPosition({3, 3, -1});
    // cube.setPosition({-3, 3, 0});

    std::vector<Shape*> scene(3);
    scene[0] = &cube;
    scene[1] = &sphere;
    scene[2] = &pyr;

    for (int i = 0; i < scene.size(); ++i) {
        scene[i]->setColor(sf::Color::Green);
    }

    size_t target_ind = 0;
    glm::vec3 target = scene[target_ind]->getPosition();
    scene[target_ind]->setColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                isMousePressed = true;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                isMousePressed = false;
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    radius -=
                        10 * angleSpeed;
                } else if (event.mouseWheelScroll.delta < 0) {
                    radius +=
                        10 * angleSpeed;
                }
                // Ограничим минимальный радиус
                if (radius < 1.0f) radius = 1.0f;
            }
        }
        if (window.hasFocus() &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;

        int deltaX = mouseX - winCenter.x;
        int deltaY = mouseY - winCenter.y;

        sf::Mouse::setPosition(winCenter, window);

        theta += deltaX * angleSpeed;
        phi += deltaY * angleSpeed;


        // Управление камерой по WASD
        if (window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                phi += angleSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                phi -= angleSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                theta += angleSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                theta -= angleSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                radius -= angleSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                radius += angleSpeed;
            }
            // Изменение активного объекта
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                for (int i = 0; i < scene.size(); ++i) {
                    scene[i]->setColor(sf::Color::Green);
                }

                target_ind = 0;
                target = scene[target_ind]->getPosition();
                scene[target_ind]->setColor(sf::Color::Red);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                for (int i = 0; i < scene.size(); ++i) {
                    scene[i]->setColor(sf::Color::Green);
                }

                target_ind = 1;
                target = scene[target_ind]->getPosition();
                scene[target_ind]->setColor(sf::Color::Red);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                for (int i = 0; i < scene.size(); ++i) {
                    scene[i]->setColor(sf::Color::Green);
                }

                target_ind = 2;
                target = scene[target_ind]->getPosition();
                scene[target_ind]->setColor(sf::Color::Red);
            }
        }
        // Ограничиваем угол наклона камеры
        if (phi > M_PI_2) {
            phi = M_PI_2 - 1e-6;
        }
        if (phi < -M_PI_2) {
            phi = -M_PI_2 - 1e-6;
        }

        // Очистка экрана
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.clear(sf::Color{200, 200, 200});

        cam.setPosition(target + glm::vec3{radius * sin(theta) * cos(phi),
                         radius * cos(theta) * cos(phi), radius * sin(phi)});
        cam.setTarget(target);
        cam.put(window);

        Vertex3Array floor{Vertex3({-100, -100, -1}, sf::Color{150, 150, 150}),
                           Vertex3({-100, 100, -1}, sf::Color{150, 150, 150}),
                           Vertex3({100, 100, -1}, sf::Color{150, 150, 150}),
                           Vertex3({100, -100, -1}, sf::Color{150, 150, 150})};
        floor.setPrimitiveType(sf::PrimitiveType::Quads);

        floor.draw(window);
        cells.draw(window);
        draw_scene(scene, window);

        // Обновляем окно
        window.display();
    }

    return 0;
}
