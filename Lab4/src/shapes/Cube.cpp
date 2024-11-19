#include "Cube.hpp"

#include <GL/glew.h>

#include <GL/gl.h>

#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(const float &len) : VAO(0), VBO(0), EBO(0) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    const float lend2 = len / 2;

    float verteces[] = {
        // координаты // текстура // нормаль // тангент // битангент
        // Задняя грань (-Z)
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, // нижний левый
        lend2, -lend2, -lend2, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, // нижний правый
        lend2, lend2, -lend2, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, // верхний правый
        lend2, lend2, -lend2, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, // верхний правый
        -lend2, lend2, -lend2, 1.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, // верхний левый
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, // нижний левый

        // Передняя грань (+Z)
        -lend2, -lend2, lend2, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, // нижний левый
        lend2, -lend2, lend2, 1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, // нижний правый
        lend2, lend2, lend2, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, // верхний правый
        lend2, lend2, lend2, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, // верхний правый
        -lend2, lend2, lend2, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, // верхний левый
        -lend2, -lend2, lend2, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, // нижний левый

        // Левая грань (-X)
        -lend2, -lend2, -lend2, 0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, // задний нижний
        -lend2, lend2, -lend2, 0.0f, 1.0f, -1.0f, 0.0f,
        0.0f, // задний верхний
        -lend2, lend2, lend2, 1.0f, 1.0f, -1.0f, 0.0f,
        0.0f, // передний верхний
        -lend2, lend2, lend2, 1.0f, 1.0f, -1.0f, 0.0f,
        0.0f, // передний верхний
        -lend2, -lend2, lend2, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, // передний нижний
        -lend2, -lend2, -lend2, 0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, // задний нижний

        // Правая грань (+X)
        lend2, -lend2, -lend2, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, // задний нижний
        lend2, lend2, -lend2, 1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, // задний верхний
        lend2, lend2, lend2, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, // передний верхний
        lend2, lend2, lend2, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, // передний верхний
        lend2, -lend2, lend2, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, // передний нижний
        lend2, -lend2, -lend2, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, // задний нижний

        // Нижняя грань (-Y)
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, // задний левый
        lend2, -lend2, -lend2, 1.0f, 1.0f, 0.0f, -1.0f,
        0.0f, // задний правый
        lend2, -lend2, lend2, 0.0f, 1.0f, 0.0f, -1.0f,
        0.0f, // передний правый
        lend2, -lend2, lend2, 0.0f, 1.0f, 0.0f, -1.0f,
        0.0f, // передний правый
        -lend2, -lend2, lend2, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, // передний левый
        -lend2, -lend2, -lend2, 1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, // задний левый

        // Верхняя грань (+Y)
        -lend2, lend2, -lend2, 1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, // задний левый
        lend2, lend2, -lend2, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, // задний правый
        lend2, lend2, lend2, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, // передний правый
        lend2, lend2, lend2, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, // передний правый
        -lend2, lend2, lend2, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, // передний левый
        -lend2, lend2, -lend2, 1.0f, 1.0f, 0.0f, 1.0f,
        0.0f // задний левый
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verteces), &verteces, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"OpenGL Error: "} +
                                 std::to_string(error));
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::draw() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error(std::string{"OpenGL Error: "} +
                                 std::to_string(error));
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Cube::~Cube() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}