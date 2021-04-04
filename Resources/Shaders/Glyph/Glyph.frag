#version 430 core

in vec2 textureCoords;

out vec4 fragmentColor;

uniform sampler2D glyphsMapSampler;

void main()
{
    vec4 characterColor = texture(glyphsMapSampler, textureCoords);
    
    fragmentColor = characterColor;
}
