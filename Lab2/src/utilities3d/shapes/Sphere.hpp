#pragma once
#include "Shape.hpp"

class Sphere final : public Shape {
   public:
    // Sphere();
    Sphere(const glm::float32 radius = 1.0, const int steps = 15,
           const int points = 30);

    void setPosition(const glm::vec3&) override;
    glm::vec3 getPosition() const override;
    void setColor(const sf::Color&) override;

    void transform(const glm::mat4& matrix) override;

    void draw(sf::RenderTarget&,
              const glm::mat4& = glm::mat4(1)) const override;

   private:
    static constexpr sf::PrimitiveType draw_type = sf::PrimitiveType::Triangles;
    using Shape::__points;
};