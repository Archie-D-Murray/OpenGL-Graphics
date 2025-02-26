#include <cstdint>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/shader.hpp"
#include "common/texture.hpp"

// Function prototypes
void keyboardInput(GLFWwindow *window);

int main( void )
{
    // =========================================================================
    // Window creation - you shouldn't need to change this code
    // -------------------------------------------------------------------------
    // Initialise GLFW
    if( !glfwInit() )
    {
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
    window = glfwCreateWindow(1024, 768, "Lab03 Textures", NULL, NULL);
    
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
    
    // Ensure we can capture keyboard inputs
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    const static float vertices[] = {
	 -0.5f, -0.5f, 0.0f,  // 0       3 -- 2
          0.5f, -0.5f, 0.0f,  // 1       |  / |  
          0.5f,  0.5f, 0.0f,  // 2       | /  |
         -0.5f,  0.5f, 0.0f   // 3       0 -- 1    
    };
    
    const static float uv[] = {
	0.40f, 0.35f,
	0.55f, 0.35f,
	0.55f, 0.60f,
	0.40f, 0.60f,
    };

    const static uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3,
    };
  
    const char* path = "../assets/mario.png";
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* data = stbi_load(path, &width, &height, &nChannels, 0);
    if (data) {
	std::cout << "Successfully loaded " << path << "\n";
    } else {
	std::cout << "Could not load " << path << "\n";
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLint textureWrapMode = GL_REPEAT;
    GLint textureFilterMinMode = GL_NEAREST;
    GLint textureFilterMagMode = GL_NEAREST_MIPMAP_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterMinMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilterMagMode);
    
    // Create the Vertex Array Object (VAO)
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create Vertex Buffer Object (VBO)
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
    
    // Compile shader program
    GLuint shaderID;
    shaderID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
    
    // Use the shader program
    glUseProgram(shaderID);
    
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Get inputs
        keyboardInput(window);
        
        // Clear the window
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Send the VBO to the shaders
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint32_t), GL_UNSIGNED_INT, NULL);
        glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
        
	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
    }
    
    // Cleanup
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    stbi_image_free(data);
    return 0;
}

void keyboardInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
