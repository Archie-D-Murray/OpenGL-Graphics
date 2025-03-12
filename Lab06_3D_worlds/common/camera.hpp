#pragma once

#include "glm/glm.hpp"

class Camera {
public:
    float fov = glm::radians(45.0f);
    float aspect = 1024.0f / 768.0f;
    float near = 0.2f;
    float far = 100.0f;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up = { 0.0f, 1.0f, 0.0f };

    glm::mat4 view;
    glm::mat4 projection;

    Camera(const glm::vec3 eye, const glm::vec3 target);
    void calculateMatrices();
};
