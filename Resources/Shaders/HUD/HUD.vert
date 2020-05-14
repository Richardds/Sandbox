#version 430 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 vertexTexture;

out vec2 textureUV;

uniform float aspectRatio;
uniform vec2 screenPosition;

void main()
{
    // Pass texture coordinates
    textureUV = vertexTexture;

    vec2 position = screenPosition + vertexPosition;

    gl_Position = vec4(position, 0.0f, 1.0f);
}
