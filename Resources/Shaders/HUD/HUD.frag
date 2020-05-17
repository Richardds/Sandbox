#version 430 core

in vec2 textureUV;

out vec4 fragmentColor;

uniform sampler2D mapSampler;

void main()
{
    vec3 mapColor = texture(mapSampler, vec2(textureUV.x, textureUV.y)).rgb;

    fragmentColor = vec4(mapColor, 1.0f);
}
