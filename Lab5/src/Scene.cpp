#include "Scene.hpp"

#include "shapes/Sphere.hpp"

glm::vec3 rand_vector() {
    return {((float)std::rand() / (float)RAND_MAX) * 2 - 1,
            ((float)std::rand() / (float)RAND_MAX) * 2 - 1,
            ((float)std::rand() / (float)RAND_MAX) * 2 - 1};
}

glm::vec3 random_on_hemisphere(const glm::vec3& normal) {
    glm::vec3 random_dir = glm::normalize(rand_vector());
    if (glm::dot(random_dir, normal) < 0) {
        random_dir = -random_dir;
    }
    return random_dir;
}

glm::vec3 Scene::get_color(Ray& ray, Shape* origin_shape, int depth) {
    if (depth == 0) {
        return {0, 0, 0};
    }

    Hit nearest_hit;
    nearest_hit.hit = false;
    bool first = true;
    for (Shape* shape : _m_shapes) {
        Hit has_hit = shape->has_hit(ray);
        if (has_hit.hit == false || has_hit.hit_shape == origin_shape) {
            continue;
        }
        if (first) {
            nearest_hit = has_hit;
            first = false;
        } else {
            if (has_hit.ray_length < nearest_hit.ray_length) {
                nearest_hit = has_hit;
            }
        }
    }

    if (nearest_hit.hit == false) {
        float y = 0.5 * (ray.get_direction().y + 1);
        return glm::vec3{255, 255, 255} * (1 - y) +
               glm::vec3{130, 178, 255} * y;
    }
    if (nearest_hit.hit_shape->is_light()) {
        return nearest_hit.color * 255.0f;
    } else {
        Shape* hit_shape = nearest_hit.hit_shape;
        glm::vec3 scatter_direction;
        if (hit_shape->get_mirror() != 0) {
            auto reflect_direction =
                ray.get_direction() -
                2.0f * nearest_hit.normal *
                    glm::dot(nearest_hit.normal, ray.get_direction());
            reflect_direction = glm::normalize(reflect_direction);

            float m = hit_shape->get_mirror();

            scatter_direction =
                m * reflect_direction +
                (1 - m) * random_on_hemisphere(nearest_hit.normal);
        } else {
            glm::vec3 r_vec = random_on_hemisphere(nearest_hit.normal);
            scatter_direction = nearest_hit.normal + r_vec;
        }
        scatter_direction = glm::normalize(scatter_direction);
        Ray scatter_ray(nearest_hit.point, scatter_direction);
        glm::vec3 color = get_color(scatter_ray, hit_shape, depth - 1);
        color *= nearest_hit.color;
        if (color.r != color.r) {
            color.r = 0;
        }
        if (color.g != color.g) {
            color.g = 0;
        }
        if (color.b != color.b) {
            color.b = 0;
        }
        return glm::clamp(color, 0.0f, 255.0f);
    }
}

void Scene::render(sf::Image& img) {
    std::srand(std::time(nullptr));
#pragma omp parallel for
    for (int i = 0; i < _m_camera.get_vp_height(); ++i) {
        for (int j = 0; j < _m_camera.get_vp_width(); ++j) {
            Ray ray;
            glm::vec3 color;
            ray = _m_camera.get_ray(j, i);
            color.r = 0;
            color.g = 0;
            color.b = 0;
            for (int s = 1; s <= SAMPLES; ++s) {
                color += get_color(ray, nullptr, MAX_DEPTH) / (float)SAMPLES;
            }
            img.setPixel(j, i, {color.r, color.g, color.b});
        }
    }
}