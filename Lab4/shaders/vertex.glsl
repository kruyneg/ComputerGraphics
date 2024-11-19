#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat4 matCamera;

out vec3 FragNormal;
out vec3 FragTangent;
out vec3 FragBitangent;

out vec3 FragPos;
out vec2 texCoord;

vec3 getTangent(in vec3 Normal) {
    if (Normal == vec3(0, 0, -1)) {
        return vec3(-1, 0, 0);
    } else if (Normal == vec3(0, 0, 1)) {
        return vec3(1, 0, 0);
    } else if (Normal == vec3(-1, 0, 0)) {
        return vec3(0, 0, 1);
    } else if (Normal == vec3(1, 0, 0)) {
        return vec3(0, 0, -1);
    } else if (Normal == vec3(0, 1, 0)) {
        return vec3(0, 0, -1);
    } else if (Normal == vec3(0, -1, 0)) {
        return vec3(-1, 0, 0);
    }
}

void main() {
    gl_Position = matCamera * vec4(aPos, 1.0);
    FragPos = aPos; // Позиция вершины в мировых координатах
    FragNormal = aNormal; // Корректируем нормаль
    FragTangent = getTangent(FragNormal);
    FragBitangent = cross(FragNormal, FragTangent);
    texCoord = aTexCoord;
}
