#include "camera.hpp"
#include "maths.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>
#include <iostream>

Camera::Camera(const glm::vec3 position, const glm::vec3 target) :
    position(position),
    target(target)
{}

void Camera::calculateMatrices() {
    view = glm::lookAt(position, target, worldUp);
    projection = glm::perspective(fov, aspect, near, far);
}

void Camera::calculateCameraVectors() {
    forward = glm::vec3(cosf(yaw) * cosf(pitch), sinf(pitch), sinf(yaw) * cosf(pitch));
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::cross(right, forward);
    target = position + forward;
}
