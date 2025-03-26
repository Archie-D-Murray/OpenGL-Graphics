#version 330 core

#define maxLights 10

struct Light {
    vec3 position;
    vec3 colour;
    vec3 direction;
    float constant;
    float linear;
    float quadratic;
    float cosPhi;
    int type;
};

// Inputs
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec3 fragmentPosition;
out vec3 UV;
out vec3 Normal;
out vec3 tangentSpaceLightPosition[maxLights];
out vec3 tangentSpaceLightDirection[maxLights];

// Uniforms
uniform mat4 MVP;
uniform mat4 MV;
uniform float ka;
uniform float kd;
uniform float ks;
uniform float Ns;
uniform Light lightSources[maxLights];

void main()
{
    mat3 invMV = transpose(inverse(mat3(MV)));
    vec3 t = normalize(invMV * tangent);
    vec3 b = normalize(invMV * bitangent);
    vec3 n = normalize(invMV * normal);
    mat3 TBN = transpose(mat3(t, b, n));
    // Output vertex postion
    gl_Position = MVP * vec4(position, 1.0);
    UV = uv;
    fragmentPosition = vTBN * vec3(MV * vec4(position, 1.0f));
    for (int i = 0; i < maxLights; i++) {
        tangentSpaceLightPosition[i] = TBN * lightSources[i].position;
        tangentSpaceLightDirection[i] = TBN * lightSources[i].direction;
    }
    Normal = mat3(transpose(inverse(MV)) * normal);
}
