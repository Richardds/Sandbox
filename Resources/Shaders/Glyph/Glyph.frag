#version 430 core

in vec2 textureCoords;

out vec4 fragmentColor;

uniform sampler2D glyphsMapSampler;

void main()
{
    vec4 glyphColor = texture(glyphsMapSampler, textureCoords * vec2(1.0f, -1.0f)); // TODO: Why is this flipped on y-axis?

    fragmentColor = glyphColor;
}
