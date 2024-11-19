#pragma once

#include <GL/glew.h>

#include <GL/gl.h>

#include <SFML/Graphics.hpp>

// Класс основанный на RenderWindow из SFML, поддерживающий работу с GLEW и
// 3D графикой
class Window3d : public sf::RenderWindow {
  public:
    Window3d(sf::VideoMode mode, const std::string &title,
             sf::Uint32 style = sf::Style::Default)
        : sf::RenderWindow(mode, title, style, sf::ContextSettings{24}) {
        auto status = glewInit();
        if (status != GLEW_OK) {
            throw std::runtime_error(
                reinterpret_cast<const char *>(glewGetErrorString(status)));
        }
        glewExperimental = GL_TRUE;
        glEnable(GL_DEPTH_TEST);
    }
    void clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    void clear(const sf::Color &color) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sf::RenderWindow::clear(color);
    }
};