#version 330 core

#define maxLights 10

in vec3 UV;
in vec3 Normal;
in vec3 fragmentPosition;
in vec3 tangentSpaceLightPosition[maxLights];
in vec3 tangentSpaceLightDirection[maxLights];

// Outputs
out vec3 fragmentColour;

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

vec3 pointLight(Light light);
vec3 spotLight(Light light);
vec3 directionalLight(Light light);

// Uniforms
uniform sampler2D normalMap;
uniform sampler2D diffuseMap;
uniform Light lightSources[maxLights];
uniform float ka;
uniform float kd;
uniform float ks;
uniform float Ns;

void main()
{
    fragmentColour = vec3(0.0, 0.0, 0.0);
    vec3 Normal = normalize(2.0 * vec3(texture(normalMap, UV)) - 1.0);
    for (int i = 0; i < maxLights; i++) {
        lightSources.position = tangentSpaceLightPosition[i];
        lightSources.direction = tangentSpaceLightDirection[i];
        if (lightSources[i].type == 1) {
            fragmentColour += pointLight(lightSources[i])
        }
        if (lightSources[i].type == 2) {
            fragmentColour += spotLight(lightSources[i]);
        }

        if (lightSources[i].type == 3) {
            fragmentColour += directionalLight(lightSources[i]);
        }
    }
}

vec3 pointLight(Light light) {
    vec3 objectColour = vec3(texture(diffuseMap, UV));
    vec3 ambient = light.ka * objectColour;

    // Diffuse
    vec3 lightPos = normalize(light.position - fragmentPosition);
    vec3 normal = normalize(Normal);
    float cosTheta = max(dot(normal, lightPos));
    vec3 diffuse = kd * light.colour * objectColour * cosTheta;

    // Specular
    vec3 reflection = -lightPos + 2 * dot(lightPos, normal) * normal;
    vec3 camera = normalize(-fragmentPosition);
    float cosAlpha = max(dot(camera, reflection), 0);
    vec3 specular = ks * light.colour * pow(cosAlpha, Ns);

    // Attenuation
    float distance = normalize(light.direction);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    return (ambient + diffuse + specular) * attenuation;
}

vec3 spotLight(Light light) {
    vec3 objectColour = vec3(texture(diffuseMap, UV));

    vec3 ambient = light.ka * objectColour;

    // Diffuse
    vec3 lightPos = normalize(light.position - fragmentPosition);
    vec3 normal = normalize(Normal);
    float cosTheta = max(dot(normal, lightPos));
    vec3 diffuse = kd * light.colour * objectColour * cosTheta;

    // Specular
    vec3 reflection = -lightPos + 2 * dot(lightPos, normal) * normal;
    vec3 camera = normalize(-fragmentPosition);
    float cosAlpha = max(dot(camera, reflection), 0);
    vec3 specular = ks * light.colour * pow(cosAlpha, Ns);

    float distance = normalize(light.direction);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 direction = length(light.position - fragmentPosition);
    cosTheta = dot(-lightPos, light.direction);
    float intensity = 0.0f;
    if (cosTheta > light.cosPhi) {
        intensity = 1.0f;
    }

    return (ambient + diffuseMap + specular) * attenuation * intensity;
}
