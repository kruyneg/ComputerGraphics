#pragma once

#include <GL/glew.h>

#include "../texture/Texture.hpp"
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <string>

class Shader {
  public:
    // ID программы в OpenGL
    unsigned int ID;

    // конструктор, считывающий шейдеры из файлов и компилирующий их
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();
    // активация шейдера
    void use();
    // установка текстуры в uniform шейдера (шейдер должен быть активен)
    void setTexture(const std::string &name, const Texture &tex) const;
    // установка переменной в uniform шейдера (шейдер должен быть активен)
    template <class T> void set(const std::string &name, T uniform) const {
        if constexpr (std::is_floating_point<T>()) {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), uniform);
        } else {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)uniform);
        }
    }
    // установка переменной в uniform шейдера (шейдер должен быть активен)
    template <int N, class T>
    void set(const std::string &name,
             const glm::vec<N, T, glm::packed_highp> &uniform) const {
        if constexpr (N == 4) {
            if constexpr (std::is_floating_point<T>()) {
                glUniform4f(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z, uniform.w);
            } else {
                glUniform4i(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z, uniform.w);
            }
        } else if constexpr (N == 3) {
            if constexpr (std::is_floating_point<T>()) {
                glUniform3f(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z);
            } else {
                glUniform3i(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y, uniform.z);
            }
        } else {
            if constexpr (std::is_floating_point<T>()) {
                glUniform2f(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y);
            } else {
                glUniform2i(glGetUniformLocation(ID, name.c_str()), uniform.x,
                            uniform.y);
            }
        }
    }
};