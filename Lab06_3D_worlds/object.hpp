#pragma once

#include <glm/ext/vector_float3.hpp>
#include <string>

struct Object {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotationAxis;
    float angle;

    std::string name;
};
