#pragma once
#include <cassert>
#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

static constexpr float DEG2RAD = M_PI / 180.0f;

class Quaternion {
public:
    float w, x, y, z;

    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion(float pitch, float yaw);

    glm::mat4 matrix();
    static Quaternion slerp(Quaternion from, Quaternion to, float t);
};

namespace Maths {


    float radians(float degrees);

    glm::mat4 scale(const glm::vec3 &scale);

    glm::mat4 rotate(glm::vec3 axis, float angle);

    glm::mat4 translate(const glm::vec3 &translation);

    glm::mat4 lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

    float yaw(glm::vec3 angles);
    float pitch(glm::vec3 angles);
    float roll(glm::vec3 angles);
}
