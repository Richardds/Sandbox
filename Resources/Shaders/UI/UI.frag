#version 430 core

uniform sampler2D textureSampler;

in vec2 textureUV;

out vec4 fragmentColor;

void main()
{
    vec4 textureColor = texture(textureSampler, textureUV);

    fragmentColor = textureColor;
}
