#version 430 core

in vec3 textureCoords;

out vec4 fragmentColor;

uniform samplerCube cubeSampler;
uniform float darkeningFactor;

void main()
{
    vec3 skyboxColor = texture(cubeSampler, textureCoords).rgb;

    vec3 darkenSkyboxColor = skyboxColor * darkeningFactor;

    fragmentColor = vec4(darkenSkyboxColor, 1.0f);
}
