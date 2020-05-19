#version 430 core

in vec3 textureCoords;

out vec4 fragmentColor;

uniform samplerCube cubeSampler;

void main()
{
    fragmentColor = texture(cubeSampler, textureCoords);
}
