#include "camera.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(const glm::vec3 position, const glm::vec3 target) :
    position(position),
    target(target)
{}

void Camera::calculateMatrices() {
    view = glm::lookAt(position, target, up);
    projection = glm::perspective(fov, aspect, near, far);
}
