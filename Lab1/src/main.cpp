#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>

sf::Vector2f randPoint(const sf::Window& win) {
    auto now = std::chrono::high_resolution_clock::now();
    std::mt19937 random_generator(now.time_since_epoch().count());
    float pos = random_generator() % win.getSize().x;
    if (pos > win.getSize().x) {
        std::cout << "panic!\n";
        exit(-1);
    }
    return (random_generator() % 2)
               ? sf::Vector2f{(random_generator() % 2) ? (win.getSize().x - 300)
                                                       : 0,
                              random_generator() % (win.getSize().y - 100)}
               : sf::Vector2f{
                     random_generator() % (win.getSize().x - 300),
                     (random_generator() % 2) ? (win.getSize().y - 100) : 0};
}

/// @brief          Интерполяция между точками
/// @param start    начальная точка
/// @param end      конечная точка
/// @param coeff    коэффициент интерполяции (процент пройденного пути)
/// @return         текущее положение
sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end,
                  float coeff) {
    return start * (1 - coeff) + end * coeff;
}

void processEvents(sf::Window& win) {
    sf::Event event;
    while (win.pollEvent(event)) {
        if (event.type == sf::Event::EventType::Closed ||
            (event.type == sf::Event::EventType::KeyPressed &&
             event.key.code == sf::Keyboard::Escape)) {

            win.close();
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Running Hexagon",
                            sf::Style::Fullscreen);

    sf::CircleShape hexagon(50, 6);
    hexagon.setOutlineThickness(5);
    hexagon.setOutlineColor(sf::Color::White);
    hexagon.setFillColor(sf::Color::Red);

    sf::Vector2f startPosition{static_cast<sf::Vector2f>(window.getSize()) /
                               2.0f};
    sf::Vector2f endPosition = randPoint(window);

    float t;                // коэффициент интерполяции.
    bool direction = true;  // направление движения (в начало или в новую точку)

    sf::Transform matrix;  // матрица трансформаций

    sf::Clock clock;
    float moveTime =
        3;  // время за которое фигура переместится между точками в секундах
    while (window.isOpen()) {

        std::cout << "\r                \r" << endPosition.x << ' '
                  << endPosition.y << std::flush;
        t = 0;
        while (window.isOpen() && t < 1) {
            processEvents(window);

            auto interval = clock.restart();
            t += interval.asSeconds() / moveTime;
            if (t > 1) {
                t = 1;
            }

            auto curPosition = lerp(startPosition, endPosition, t);

            matrix = sf::Transform::Identity;
            matrix.translate(curPosition);
            if (direction)
                matrix.scale(sf::Vector2f{1 + 2 * t, 1});
            else
                matrix.scale(sf::Vector2f{1 + 2 * (1 - t), 1});

            window.clear();
            window.draw(hexagon, matrix);
            window.display();
        }
        t = 0;
        std::swap(startPosition, endPosition);
        if (!direction) {
            endPosition = randPoint(window);
        }
        direction = !direction;
    }
    std::cout << std::endl;
}