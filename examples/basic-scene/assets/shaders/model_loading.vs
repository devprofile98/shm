#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;
out mat3 TBN;
out vec3 testTan;

layout(std140) uniform VPMatrices {
    mat4 projection;
    mat4 view;
    mat4 lightSpaceMatrix;
};

uniform mat4 model;

void main() {

    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
    TBN = mat3(T, B, N);

    FragPos = vec3(model * vec4(aPos, 1.0));
    testTan = normalize(aBitangent);
    Normal = transpose(inverse(mat3(model))) * aNormal;
    TexCoords = aTexCoords;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
