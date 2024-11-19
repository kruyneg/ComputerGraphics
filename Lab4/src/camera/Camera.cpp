#include "Camera.hpp"

#include <GL/glew.h>

#include <GL/gl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const CameraSettings CameraSettings::Default = {0.01, 20.0, glm::radians(45.0)};

Camera::Camera()
    : __position{1, 1, 1}, __target_point{0, 0, 0}, __angle{glm::radians(45.0)},
      __near{0.01}, __far{20} {}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &targetPoint,
               CameraSettings settings)
    : __position{position}, __target_point{targetPoint},
      __angle{settings.angle}, __near{settings.near}, __far{settings.far} {}

void Camera::setPosition(const glm::vec3 &position) { __position = position; }

glm::vec3 Camera::getPosition() const { return __position; }

void Camera::setTarget(const glm::vec3 &position) { __target_point = position; }

glm::vec3 Camera::getTarget() const { return __target_point; }

void Camera::changeSettings(CameraSettings settings) {
    __angle = settings.angle;
    __near = settings.near;
    __far = settings.far;
}

glm::mat4 Camera::getMatrix(const sf::RenderTarget &window) const {
    glm::mat4 view =
        glm::lookAt(__position, __target_point, glm::vec3{0, 1, 0});
    glm::mat4 projection = glm::perspective(
        __angle,
        static_cast<glm::float32>(window.getSize().x) / window.getSize().y,
        __near, __far);

    return projection * view;
}

void Camera::put(const sf::RenderTarget &window, Shader &program) {
    auto matrix = getMatrix(window);
    glUniformMatrix4fv(glGetUniformLocation(program.ID, "matCamera"), 1,
                       GL_FALSE, glm::value_ptr(matrix));
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"OpenGL Error: "} + std::to_string(error));
    }
}