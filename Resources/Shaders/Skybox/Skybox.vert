#version 430 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Texture;

out vec3 textureCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    // Pass interpolated texture coordinates
    textureCoords = a_Texture;

    gl_Position = projection * view * vec4(a_Position, 1.0f);
}
