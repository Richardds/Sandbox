#version 430 core

in vec3 position;

out vec4 fragmentColor;

uniform samplerCube skyboxSampler;
uniform float darkeningFactor;

void main()
{
    vec3 skyboxColor = texture(skyboxSampler, position).rgb;

    vec3 darkenSkyboxColor = skyboxColor * darkeningFactor;

    fragmentColor = vec4(darkenSkyboxColor, 1.0f);
}
