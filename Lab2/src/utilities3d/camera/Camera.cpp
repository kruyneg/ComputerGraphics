#include "Camera.hpp"

#include <GL/gl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const CameraSettings CameraSettings::Default = {1.0, 20.0, glm::radians(45.0)};

Camera::Camera()
    : __position{1, 1, 1},
      __target_point{0, 0, 0},
      __angle{glm::radians(45.0)},
      __near{1},
      __far{20} {}

Camera::Camera(const glm::vec3& position, const glm::vec3& targetPoint,
               CameraSettings settings)
    : __position{position},
      __target_point{targetPoint},
      __angle{settings.angle},
      __near{settings.near},
      __far{settings.far} {}

void Camera::setPosition(const glm::vec3& position) { __position = position; }

glm::vec3 Camera::getPosition() const { return __position; }

void Camera::setTarget(const glm::vec3& position) { __target_point = position; }

glm::vec3 Camera::getTarget() const { return __target_point; }

void Camera::changeSettings(CameraSettings settings) {
    __angle = settings.angle;
    __near = settings.near;
    __far = settings.far;
}

void Camera::put(sf::RenderTarget& window) {
    // window.setActive(true);

    glm::mat4 lookat =
        glm::lookAt(__position, __target_point, glm::vec3{0, 0, 1});
    glm::mat4 projection = glm::perspective(
        __angle, static_cast<glm::float32>(window.getSize().x) / window.getSize().y,
        __near, __far);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(lookat));
}