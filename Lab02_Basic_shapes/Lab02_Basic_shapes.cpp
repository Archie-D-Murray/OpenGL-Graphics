#include <cmath>
#include <iostream>

#include <glm/vec3.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/shader.hpp"

// Function prototypes
void keyboardInput(GLFWwindow *window);

const float TAU = 2 * M_PI;
const size_t TRIANGLE_COUNT = 8192;
const size_t TRIANGLE_VERTS = 3;
const size_t VEC3_LENGTH = 3;

int main(void) {
    // =========================================================================
    // Window creation - you shouldn't need to change this code
    // -------------------------------------------------------------------------
    // Initialise GLFW
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Lab02 Basic Shapes", NULL, NULL);
    
    if( window == NULL ){
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
    // -------------------------------------------------------------------------
    // End of window creation
    // =========================================================================
    //

    unsigned int shaderID =
        LoadShaders("vertexShader.glsl", "fragmentShader.glsl");

    float aspectRatio = 1024 / 768.0f;

    const float radius = 0.75f;
    static float vertices[TRIANGLE_COUNT * TRIANGLE_VERTS * VEC3_LENGTH] = { 0 };
    for (size_t i = 0; i < TRIANGLE_COUNT; i++) {
        float centreAngle = TAU * (float) i / (float) TRIANGLE_COUNT;
        vertices[i * TRIANGLE_VERTS * VEC3_LENGTH + 0 * TRIANGLE_VERTS + 0] = 0.0f;
        vertices[i * TRIANGLE_VERTS * VEC3_LENGTH + 0 * TRIANGLE_VERTS + 1] = 0.0f; // Centre
        vertices[i * TRIANGLE_VERTS * VEC3_LENGTH + 1 * TRIANGLE_VERTS + 0] = sinf(centreAngle - TAU / (float)(TRIANGLE_COUNT * 2)) * radius;
        vertices[i * TRIANGLE_VERTS * VEC3_LENGTH + 1 * TRIANGLE_VERTS + 1] = cosf(centreAngle - TAU / (float)(TRIANGLE_COUNT * 2)) * radius * aspectRatio; // Left
        vertices[i * TRIANGLE_VERTS * VEC3_LENGTH + 2 * TRIANGLE_VERTS + 0] = sinf(centreAngle + TAU / (float)(TRIANGLE_COUNT * 2)) * radius;
        vertices[i * TRIANGLE_VERTS * VEC3_LENGTH + 2 * TRIANGLE_VERTS + 1] = cosf(centreAngle + TAU / (float)(TRIANGLE_COUNT * 2)) * radius * aspectRatio; // Right
    }
    
    static float colours[TRIANGLE_COUNT * TRIANGLE_VERTS * VEC3_LENGTH] = { 0 };
    for (size_t i = 0; i < TRIANGLE_COUNT; i++) {
        for (size_t j = 0; j < TRIANGLE_VERTS; j++) {
            if (i % 2 == 0) {
                colours[i * TRIANGLE_VERTS * VEC3_LENGTH + j * TRIANGLE_VERTS + 0] = 1.0f;
                colours[i * TRIANGLE_VERTS * VEC3_LENGTH + j * TRIANGLE_VERTS + 1] = 0.0f;
                colours[i * TRIANGLE_VERTS * VEC3_LENGTH + j * TRIANGLE_VERTS + 2] = 0.0f;
                        
            } else {
                colours[i * TRIANGLE_VERTS * VEC3_LENGTH + j * TRIANGLE_VERTS + 0] = 0.0f;
                colours[i * TRIANGLE_VERTS * VEC3_LENGTH + j * TRIANGLE_VERTS + 1] = 1.0f;
                colours[i * TRIANGLE_VERTS * VEC3_LENGTH + j * TRIANGLE_VERTS + 2] = 0.0f;
            }
        }
    }

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int colourBuffer;
    glGenBuffers(1, &colourBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

    glUseProgram(shaderID);
	// Ensure we can capture keyboard inputs
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Get inputs
        keyboardInput(window);
        
        // Clear the window
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (TRIANGLE_VERTS * sizeof(float)));
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

       
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &colourBuffer);
    glDeleteProgram(shaderID);
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}

void keyboardInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
