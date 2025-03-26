#pragma once
#include <cassert>
#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

static constexpr float DEG2RAD = M_PI / 180.0f;

namespace Maths {

    float radians(float degrees);

    glm::mat4 scale(const glm::vec3 &scale);

    glm::mat4 rotate(float angle, glm::vec3 axis);

    glm::mat4 translate(const glm::vec3 &translation);

    glm::mat4 lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

    float yaw(glm::vec3 angles);
    float pitch(glm::vec3 angles);
    float roll(glm::vec3 angles);
}
