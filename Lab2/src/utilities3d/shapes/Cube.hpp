#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "../VertexArray.hpp"
#include "Shape.hpp"

class Cube final : public Shape {
   public:
    Cube();
    Cube(const glm::f32& len);

    void setPosition(const glm::vec3& position) override;
    glm::vec3 getPosition() const override;

    void setColor(const sf::Color& color) override;
    /* @brief Change cube's colors
       @param colors: front, back, left, right, top, bottom
    */
    void setColor(const std::vector<sf::Color>& colors);

    void draw(sf::RenderTarget& window,
              const glm::mat4& transform = glm::mat4(1)) const override;

   private:
    static constexpr auto draw_type = sf::PrimitiveType::Quads;

    using Shape::__points;
};