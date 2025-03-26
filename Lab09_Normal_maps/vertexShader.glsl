#version 330 core

# define maxLights 10

// Inputs
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

// Outputs
out vec3 fragmentPosition;
out vec2 UV;
out vec3 tangentSpaceLightPosition[maxLights];
out vec3 tangentSpaceLightDirection[maxLights];

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

// Uniforms
uniform mat4 MVP;
uniform mat4 MV;
uniform Light lightSources[maxLights];

void main() {
    mat3 invMV = transpose(inverse(mat3(MV)));
    vec3 t = normalize(invMV * tangent);
    vec3 n = normalize(invMV * normal);
    t = normalize(t - dot(t, n) * n);
    vec3 b = cross(n, t);
    mat3 TBN = transpose(mat3(t, b, n));
    // Output vertex postion
    UV = uv;
    fragmentPosition = TBN * vec3(MV * vec4(position, 1.0f));
    for (int i = 0; i < maxLights; i++) {
        tangentSpaceLightPosition[i] = TBN * lightSources[i].position;
        tangentSpaceLightDirection[i] = TBN * lightSources[i].direction;
    }
}
