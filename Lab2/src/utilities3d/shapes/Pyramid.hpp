#pragma once
#include "Shape.hpp"

class Pyramid final : public Shape {
   public:
    Pyramid();

    void setPosition(const glm::vec3&) override;
    glm::vec3 getPosition() const override;
    void setColor(const sf::Color&) override;

    void draw(sf::RenderTarget&,
              const glm::mat4& = glm::mat4(1)) const override;

   private:
    static constexpr sf::PrimitiveType draw_type = sf::PrimitiveType::TrianglesStrip;
    using Shape::__points;
};