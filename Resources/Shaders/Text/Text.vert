#version 430 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_Texture;

out vec2 textureCoords;

uniform mat3 transformation;

void main()
{
    vec2 vertexPosition = a_Position;

    // Calculate transformed position
    vec3 transformedPosition = transformation * vec3(vertexPosition, 1.0f);

    // Pass interpolated texture coordinates
    textureCoords = a_Texture;

    gl_Position = vec4(transformedPosition.xy, 0.0f, 1.0f);
}
