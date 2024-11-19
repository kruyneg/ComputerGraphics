#version 330
layout(location = 0) in vec3 aPos;

uniform mat4 matCamera;
uniform vec3 bulbPos;

mat4 translate(mat4 matrix, vec3 translation)
{
    mat4 result = matrix; // Единичная матрица
    result[3][0] = translation.x; // Перенос по X
    result[3][1] = translation.y; // Перенос по Y
    result[3][2] = translation.z; // Перенос по Z
    return result;
}

void main() {
    gl_Position = matCamera * translate(mat4(1), bulbPos) * vec4(aPos, 1);
}