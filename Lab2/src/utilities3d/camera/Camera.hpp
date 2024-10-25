#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

struct CameraSettings {
    static const CameraSettings Default;

    glm::float32 near;
    glm::float32 far;
    glm::float32 angle;
};

class Camera {
   public:
    Camera();
    Camera(const glm::vec3& position, const glm::vec3& targetPoint,
           CameraSettings = CameraSettings::Default);

    void setPosition(const glm::vec3& position);
    glm::vec3 getPosition() const;
    void setTarget(const glm::vec3& position);
    glm::vec3 getTarget() const;

    void changeSettings(CameraSettings);

    void put(sf::RenderTarget&);

   private:
    glm::vec3 __position;
    glm::vec3 __target_point;
    glm::float32 __angle;
    glm::float32 __near;
    glm::float32 __far;
};