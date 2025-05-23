#pragma once
#include <cassert>
#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

static constexpr float DEG2RAD = M_PI / 180.0f;

namespace Maths {

    static float radians(float degrees) {
        return degrees * DEG2RAD;
    }

    static glm::mat4 scale(const glm::vec3 &scale) {
        glm::mat4 scaleMat = glm::mat4(1.0f);
        scaleMat[0][0] = scale.x;
        scaleMat[1][1] = scale.y;
        scaleMat[2][2] = scale.z;
        return scaleMat;
    }

    static glm::mat4 rotate(glm::vec3 axis, float angle) {
        axis = glm::normalize(axis);
        // glm::mat4 rotateMat = glm::identity<glm::mat4>();
        glm::mat4 rotateMat = glm::mat4(1.0f);
        float s = sin(angle);
        float c = cos(angle);
        float xx = axis.x * axis.x, yy = axis.y * axis.y, zz = axis.z * axis.z;
        float xy = axis.x * axis.y, xz = axis.x * axis.z, yz = axis.y * axis.z;
        float xs = axis.x * s,      ys = axis.y * s,      zs = axis.z * s;
        rotateMat[0][0] = xx * (1 - c) + c;
        rotateMat[0][1] = xy * (1 - c) + zs;
        rotateMat[0][2] = xz * (1 - c) - ys;
        rotateMat[1][0] = xy * (1 - c) - zs;
        rotateMat[1][1] = yy * (1 - c) + c;
        rotateMat[1][2] = yz * (1 - c) + xs; 
        rotateMat[2][0] = xz * (1 - c) + ys;
        rotateMat[2][1] = yz * (1 - c) - xs;
        rotateMat[2][2] = zz * (1 - c) + c;
        return rotateMat;
    }

    static glm::mat4 translate(const glm::vec3 &translation) {
        glm::mat4 translateMat = glm::mat4(1.0f);
        translateMat[3][0] = translation.x;
        translateMat[3][1] = translation.y;
        translateMat[3][2] = translation.z;
        return translateMat;
    }
}
