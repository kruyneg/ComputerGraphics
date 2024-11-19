#pragma once

#include "../shader/Shader.hpp"
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

struct CameraSettings {
    static const CameraSettings Default;

    glm::float32 near;  // near flat
    glm::float32 far;   // far flat
    glm::float32 angle; // angle of view
};

class Camera {
  public:
    Camera();
    // конструктор камеры с позицией камеры и позицией цели
    Camera(const glm::vec3 &position, const glm::vec3 &targetPoint,
           CameraSettings = CameraSettings::Default);

    void setPosition(const glm::vec3 &position);
    glm::vec3 getPosition() const;
    void setTarget(const glm::vec3 &position);
    glm::vec3 getTarget() const;

    void changeSettings(CameraSettings);

    // получение матрицы камеры для использования в вычислениях
    // matrix = projection * view
    glm::mat4 getMatrix(const sf::RenderTarget &window) const;

    // set uniform "matCamera"
    // for using of this in shaders
    void put(const sf::RenderTarget &, Shader &program);

  private:
    glm::vec3 __position;
    glm::vec3 __target_point;
    glm::float32 __angle;
    glm::float32 __near;
    glm::float32 __far;
};