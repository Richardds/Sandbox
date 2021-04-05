#version 430 core

in vec2 textureCoords;

out vec4 fragmentColor;

uniform sampler2D fontMapSampler;
uniform vec4 color;

void main()
{
    vec4 fontMask = texture(fontMapSampler, textureCoords);

    // Discard fragments outside the font mask
    if (fontMask.a < 0.005) {
        discard;
    }

    fragmentColor = vec4(color.rgb, fontMask.a);
}
