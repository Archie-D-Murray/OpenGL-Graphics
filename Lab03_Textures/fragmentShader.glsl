#version 330 core

in vec2 UV;
uniform sampler2D textureMap;
out vec4 colour;

void main()
{
    colour = texture(textureMap, vec2(UV.x, UV.y));
}
