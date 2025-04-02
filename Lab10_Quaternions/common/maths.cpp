#include "maths.hpp"
#include <glm/geometric.hpp>

Quaternion::Quaternion() {}
Quaternion::Quaternion(float w, float x, float y, float z) :
    w(w), x(x), y(y), z(z)
{}
Quaternion::Quaternion(float pitch, float yaw) {
    float cosPitch = cosf(0.5f * pitch);
    float sinPitch = sinf(0.5f * pitch);
    float cosYaw = cosf(0.5f * yaw);
    float sinYaw = sinf(0.5f * yaw);

    this->w = cosPitch * cosYaw;
    this->x = sinPitch * cosYaw;
    this->y = cosPitch * sinYaw;
    this->z = sinPitch * sinYaw;
}

glm::mat4 Quaternion::matrix() {
    float s = 2.0f / (w * w + x * x + y * y + z * z);
    float xs = x * s,  ys = y * s,  zs = z * s;
    float xx = x * xs, xy = x * ys, xz = x * zs;
    float yy = y * ys, yz = y * zs, zz = z * zs;
    float xw = w * xs, yw = w * ys, zw = w * zs;

    glm::mat4 rotate = glm::mat4(1.0f);
    rotate[0][0] = 1.0f - (yy + zz);
    rotate[0][1] = xy + zw;
    rotate[0][2] = xz - yw;
    rotate[1][0] = xy - zw;
    rotate[1][1] = 1.0f - (xx + zz);
    rotate[1][2] = yz + xw;
    rotate[2][0] = xz + yw;
    rotate[2][1] = yz - xw;
    rotate[2][2] = 1.0f - (xx + yy);
    return rotate;
}

Quaternion Quaternion::slerp(Quaternion from, Quaternion to, float t) {
    float cosTheta = from.w * to.w + from.x * to.x + from.y * to.y + from.z * to.z;

    if (cosTheta > 0.9999f) {
        return to;
    }

    if (cosTheta < 0) {
        to = Quaternion(-to.w, -to.x, -to.y, -to.z);
        cosTheta *= -1.0f;
    }

    Quaternion rotation = Quaternion();

    float theta = acosf(cosTheta);
    float a = sinf((1.0f - t) * theta) / sinf(theta);
    float b = sin(t * theta) / sin(theta);

    rotation.w = a * from.w + b * to.w;
    rotation.x = a * from.x + b * to.x;
    rotation.y = a * from.y + b * to.y;
    rotation.z = a * from.z + b * to.z;

    return rotation;
}

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
    float c = cosf(0.5f * angle);
    float s = sinf(0.5f * angle);
    Quaternion rotation = Quaternion(c, s * axis.x, s * axis.y, s * axis.z);
    return rotation.matrix();
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
