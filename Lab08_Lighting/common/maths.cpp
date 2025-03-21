#include "maths.hpp"
#include <glm/geometric.hpp>

float Maths::radians(float degrees) {
    return degrees * DEG2RAD;
}

glm::mat4 Maths::scale(const glm::vec3 &scale) {
    glm::mat4 scaleMat = glm::mat4(1.0f);
    scaleMat[0][0] = scale.x;
    scaleMat[1][1] = scale.y;
    scaleMat[2][2] = scale.z;
    return scaleMat;
}

glm::mat4 Maths::rotate(glm::vec3 axis, float angle) {
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

glm::mat4 Maths::translate(const glm::vec3 &translation) {
    glm::mat4 translateMat = glm::mat4(1.0f);
    translateMat[3][0] = translation.x;
    translateMat[3][1] = translation.y;
    translateMat[3][2] = translation.z;
    return translateMat;
}

float Maths::yaw(glm::vec3 angles) {
    return angles.x;
}

float Maths::pitch(glm::vec3 angles) {
    return angles.y;
}

float Maths::roll(glm::vec3 angles) {
    return angles.x;
}

glm::mat4 Maths::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::vec3 forward = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    glm::vec3 up = glm::cross(right, forward);
    glm::vec3 negativePosition = -1.0f * position;
    view[0][0] = right.x;
    view[0][1] = right.y;
    view[0][2] = right.z;
    view[0][3] = glm::dot(negativePosition, right);
    view[1][0] = up.x;
    view[1][1] = up.y;
    view[1][2] = up.z;
    view[1][3] = glm::dot(negativePosition, up);
    view[2][0] = -1.0f * forward.x;
    view[2][1] = -1.0f * forward.y;
    view[2][2] = -1.0f * forward.z;
    view[2][3] = glm::dot(negativePosition, forward);
    view[3][0] = 0.0f;
    view[3][1] = 0.0f;
    view[3][2] = 0.0f;
    view[3][3] = 1.0f;
    return view;
}
