#version 330 core

in vec3 FragNormal;
in vec3 FragTangent;
in vec3 FragBitangent;

in vec3 FragPos;
in vec2 texCoord;

uniform vec3 lightPos;
uniform sampler2D ourTexture;
uniform sampler2D normalMap;
uniform bool NMEnabled;

out vec4 FragColor;

void main()
{
    mat3 TBN = mat3(FragTangent, FragBitangent, FragNormal);

    // Извлекаем нормаль из карты нормалей
    vec3 normal;
    if (NMEnabled) {
        normal = texture(normalMap, texCoord).rgb;
        normal = normalize(normal * 2.0 - 1.0); // Преобразуем из [0,1] в [-1,1]
        normal = normalize(TBN * normal);
    } else {
        normal = FragNormal;
    }

    // Освещение
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 viewDir = normalize(lightPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // 32 - блеск
    if (dot(lightDir, normal) < 0) {
        spec = 0;
    }

    vec3 diffuse = diff * texture(ourTexture, texCoord).rgb;
    vec3 specular = spec * vec3(0.5);
    // vec3 specular = vec3(0);

    // Итоговый цвет
    vec3 result = diffuse + specular;
    FragColor = vec4(result, 1.0);
}