#pragma once

#include <glm/glm.hpp>
#include <string>
#include "maths.hpp"
#include "model.hpp"

class Object {
public:
  glm::vec3 position;
  glm::vec3 scale;
  Quaternion rotation;
  std::string name = "Object";
  Model* model = nullptr;

  glm::mat4 modelMat();
  void draw(uint32_t shaderID);
};
