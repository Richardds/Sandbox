#version 430 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_Texture;

out vec2 textureCoords;

uniform vec2 screenResolution;

void main()
{
    // Pass interpolated texture coordinates
    textureCoords = a_Texture;

    gl_Position = vec4(a_Position, 0.0f, 1.0f);
}
