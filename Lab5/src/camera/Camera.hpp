#pragma once
#include <glm/glm.hpp>
#include <stdexcept>

#include "../ray.hpp"

class Camera {
   public:
    Camera(int vp_height, int vp_width, const glm::vec3& position,
           const glm::vec3& target_pos)
        : _m_height(vp_height),
          _m_width(vp_width),
          _m_position(position),
          _m_target(target_pos) {}

    Ray get_ray(int x, int y) const;
    inline int get_vp_height() const {
        return _m_height;
    }
    inline int get_vp_width() const {
        return _m_width;
    }

   private:
    int _m_height;
    int _m_width;
    glm::vec3 _m_position;
    glm::vec3 _m_target;
};

inline Ray Camera::get_ray(int x, int y) const {
    if (x < 0 || x >= _m_width || y < 0 || y >= _m_height) {
        throw std::out_of_range("point out of display");
    }

    float vp_height = 2;
    float vp_width = vp_height * _m_width / _m_height;

    glm::vec3 dir = _m_position + glm::normalize(_m_target - _m_position)
        // _m_target + glm::vec3{_m_width / 2 - (x + 1) / _m_width,
        //                       _m_height / 2 - (y + 1) / _m_height, 0};
        /* _m_target */ + glm::vec3(vp_width / 2.0f - static_cast<float>(x + 1) / _m_width * vp_width,
                                vp_height / 2.0f - static_cast<float>(y + 1) / _m_height * vp_height, 0);
    return Ray(_m_position, glm::normalize(dir));
}