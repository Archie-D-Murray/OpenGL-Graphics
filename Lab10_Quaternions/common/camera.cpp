#include "camera.hpp"
#include "maths.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>
#include <iostream>

Camera::Camera(const glm::vec3 position, const glm::vec3 target) :
    position(position),
    target(target),
    orientation(pitch, yaw)
{}

void Camera::calculateMatrices() {
    view = glm::lookAt(position, target, worldUp);
    projection = glm::perspective(fov, aspect, near, far);
}

void Camera::calculateCameraVectors() {
    forward = glm::vec3(cosf(yaw) * cosf(pitch), sinf(pitch), sinf(yaw) * cosf(pitch));
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::cross(right, forward);
}

void Camera::quaternionCamera(float dt) {
    Quaternion rotation = Quaternion(-pitch, yaw);
    orientation = Quaternion::slerp(orientation, rotation, dt * 12.0f);
    view = orientation.matrix() * Maths::translate(-position);
    projection = glm::perspective(fov, aspect, near, far);

    right   =  glm::vec3(view[0][0], view[1][0], view[2][0]);
    up      =  glm::vec3(view[0][1], view[1][1], view[2][1]);
    forward = -glm::vec3(view[0][2], view[1][2], view[2][2]);
    target = position + forward;
}
