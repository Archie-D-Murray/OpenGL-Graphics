#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstdio>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common/camera.hpp"
#include "common/light.hpp"
#include "common/maths.hpp"
#include "common/model.hpp"
#include "common/object.hpp"
#include "common/shader.hpp"
#include "common/texture.hpp"

glm::vec2 mouseDelta;
glm::vec2 movementInput;

float lastFrame = 0.0f;
float deltaTime = 0.0f;

const float width = 1260.0f;
const float height = 720.0f;
const float cameraSpeed = 0.0075f;

// Function prototypes
void keyboardInput(GLFWwindow *window);
void mouseInput(GLFWwindow *window);

Camera camera = Camera({0.0f, 4.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

int main(void) {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  GLFWwindow *window;
  window = glfwCreateWindow(width, height, "Lab10 Quaternions", NULL, NULL);

  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  // Use back face culling
  glEnable(GL_CULL_FACE);

  // Ensure we can capture keyboard inputs
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Capture mouse inputs
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwPollEvents();
  glfwSetCursorPos(window, width * 0.5f, height * 0.5f);

  uint32_t shaderID =
      LoadShaders("./vertexShader.glsl", "./fragmentShader.glsl");
  uint32_t mvpID = glGetUniformLocation(shaderID, "MVP");
  uint32_t mvID = glGetUniformLocation(shaderID, "MV");

  Light lights;

  lights.addDirectionalLight(glm::vec3 {1, -1, 0}, glm::vec3 {1.0f, 1.0f, 0.0f});
  lights.addPointLight(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.1f, 0.02f);                  // attenuation

  std::vector<Object> objects;

  Model teapot = Model("../assets/teapot.obj");
  teapot.addTexture("../assets/blue.bmp", "diffuse");
  teapot.addTexture("../assets/diamond_normal.png", "normal");
  teapot.ka = 0.2f;
  teapot.kd = 0.7f;
  teapot.ks = 1.0f;
  teapot.Ns = 20.0f;

  fprintf(stdout, "Loaded models\n");

  objects.push_back(
    Object{
      .position = glm::vec3 {0, 1, 0},
      .scale = glm::vec3 {1, 1, 1},
      .rotation = Quaternion(),
      .model = &teapot,
  });

  fprintf(stdout, "Added object\n");

  while (!glfwWindowShouldClose(window)) {
    float time = glfwGetTime();
    deltaTime = time - lastFrame;
    lastFrame = time;

    mouseInput(window);
    keyboardInput(window);

    camera.pitch += mouseDelta.x * cameraSpeed * deltaTime;
    camera.yaw += mouseDelta.y * cameraSpeed * deltaTime;

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.quaternionCamera(deltaTime);
    glUseProgram(shaderID);

    lights.toShader(shaderID, camera.view);

    for (Object &object : objects) {
      glm::mat4 model = object.modelMat();

      glm::mat4 mv = camera.view * model;
      glm::mat4 mvp = camera.projection * mv;

      glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mvp));
      glUniformMatrix4fv(mvID, 1, GL_FALSE, glm::value_ptr(mv));

      object.draw(shaderID);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  teapot.deleteBuffers();
  glDeleteProgram(shaderID);
  glfwTerminate();
}

void keyboardInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  movementInput = glm::vec2{0};
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    movementInput.y += 1;

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    movementInput.y -= 1;

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    movementInput.x -= 1;

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    movementInput.x += 1;
}

void mouseInput(GLFWwindow *window) {

  double x = 0, y = 0;
  glfwGetCursorPos(window, &x, &y);
  glfwSetCursorPos(window, width * 0.5f, height * 0.5f);

  mouseDelta = glm::vec2 { float(x - width * 0.5f), float(width * 0.5f - y) };
  fprintf(stdout, "Updated mousePos\n");
}
