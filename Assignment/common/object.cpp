#include "object.hpp"

glm::mat4 Object::modelMat() {
  return Maths::translate(position) * rotation.matrix() * Maths::scale(scale);
}
void Object::draw(uint32_t shaderID) {
  if (model) {
    model->draw(shaderID);
  }
}
