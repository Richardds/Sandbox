#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTextureUV;

out vec2 textureUV;

uniform mat4 uiMatrix;

void main()
{
    // Pass texture coordinates
    textureUV = vertexTextureUV;

    vec4 screenPosition = uiMatrix * vec4(vertexPosition, 1.0f);

    // ...

    gl_Position = screenPosition;
}
