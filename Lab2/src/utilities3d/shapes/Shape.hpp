#pragma once

#include <glm/glm.hpp>

#include "../VertexArray.hpp"

class Shape {
   public:
    virtual void setPosition(const glm::vec3&) = 0;
    virtual glm::vec3 getPosition() const = 0;
    virtual void setColor(const sf::Color&) = 0;
    virtual void draw(sf::RenderTarget&, const glm::mat4&) const = 0;

   protected:
    Vertex3Array __points;
};