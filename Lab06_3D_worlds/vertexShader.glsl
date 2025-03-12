#version 330 core

// Inputs
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

uniform mat4 MVP;

// Outputs
out vec2 UV;

void main()
{
    // Output vertex position
    gl_Position = MVP * vec4(position, 1.0);

    // Output texture co-ordinates
    UV = uv;
}
