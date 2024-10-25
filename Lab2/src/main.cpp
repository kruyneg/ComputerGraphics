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

void setSceneColor(std::vector<Shape*>& scene, const sf::Color& color) {
    for (int i = 0; i < scene.size(); ++i) {
        scene[i]->setColor(color);
    }
}

void drawScene(std::vector<Shape*>& scene, sf::RenderWindow& window) {
    for (int i = 0; i < scene.size(); ++i) {
        scene[i]->draw(window, glm::mat4(1));
    }
}

// Переменная для управления скоростью поворота
constexpr float speed = 1e-2;

int main() {
    // Начальные значения для углов камеры
    float theta = glm::radians(90.0);  // Угол поворота вокруг Z
    float phi = glm::radians(90.0);  // Угол наклона вверх/вниз
    float radius = 5.0f;  // Расстояние камеры до фигуры

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

    // Создание камеры
    Camera cam;
    cam.setPosition({radius * sin(theta) * cos(phi), radius * sin(phi),
                     radius * cos(theta) * cos(phi)});

    // Создание сетки и поверхности
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

    // Основные фигуры
    Cube cube;
    cube.setPosition({-3, -3, 0});
    cube.setColor({sf::Color::Red, sf::Color::Blue, sf::Color::Cyan,
                   sf::Color::Green, sf::Color::Magenta, sf::Color::Yellow});
    Sphere sphere;
    Pyramid pyr;
    pyr.setPosition({3, 3, 0});

    // Сцена с фигурами
    std::vector<Shape*> scene(3);
    scene[0] = &cube;
    scene[1] = &sphere;
    scene[2] = &pyr;

    // setSceneColor(sf::Color::Green);
    size_t target_ind = 0;
    glm::vec3 target = scene[target_ind]->getPosition();
    // scene[target_ind]->setColor(sf::Color::Red);

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
                    radius -= 10 * speed;
                } else if (event.mouseWheelScroll.delta < 0) {
                    radius += 10 * speed;
                }
                // Ограничим минимальный радиус
                if (radius < 1.0f) radius = 1.0f;
            }
        }
        if (window.hasFocus() &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // Изменение координат камеры
        {
            int mouseX = sf::Mouse::getPosition(window).x;
            int mouseY = sf::Mouse::getPosition(window).y;

            int deltaX = mouseX - winCenter.x;
            int deltaY = mouseY - winCenter.y;

            sf::Mouse::setPosition(winCenter, window);

            theta += deltaX * speed;
            phi += deltaY * speed;
        }

        glm::mat4 transform(1);
        if (window.hasFocus()) {
            // Перемещение
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                float dx = 10 * speed;
                transform = glm::translate(transform, {dx, 0, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                float dx = -10 * speed;
                transform = glm::translate(transform, {dx, 0, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                float dy = 10 * speed;
                transform = glm::translate(transform, {0, dy, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                float dy = -10 * speed;
                transform = glm::translate(transform, {0, dy, 0});
            }
            // Поворот
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                float alpha = speed;
                transform = glm::rotate(transform, alpha, {1, 0, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                float alpha = -speed;
                transform = glm::rotate(transform, alpha, {1, 0, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                float beta = speed;
                transform = glm::rotate(transform, beta, {0, 1, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                float beta = -speed;
                transform = glm::rotate(transform, beta, {0, 1, 0});
            }
            // Масштабирование
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                float delta = 1.1;
                transform = glm::scale(transform, glm::vec3(delta));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                float delta = 0.9;
                transform = glm::scale(transform, glm::vec3(delta));
            }
            // Управление камерой
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                radius -= speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                radius += speed;
            }
            // Изменение активного объекта
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                // setSceneColor(scene, sf::Color::Green);
                target_ind = 0;
                target = scene[target_ind]->getPosition();
                // scene[target_ind]->setColor(sf::Color::Red);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                // setSceneColor(scene, sf::Color::Green);
                target_ind = 1;
                target = scene[target_ind]->getPosition();
                // scene[target_ind]->setColor(sf::Color::Red);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                // setSceneColor(scene, sf::Color::Green);
                target_ind = 2;
                target = scene[target_ind]->getPosition();
                // scene[target_ind]->setColor(sf::Color::Red);
            }
        }
        target = scene[target_ind]->getPosition();
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
                                           radius * cos(theta) * cos(phi),
                                           radius * sin(phi)});
        cam.setTarget(target);
        cam.put(window);

        // Применение трансформации
        scene[target_ind]->transform(transform);

        floor.draw(window);
        cells.draw(window);
        drawScene(scene, window);

        // Обновляем окно
        window.display();
    }

    return 0;
}
