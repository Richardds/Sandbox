#version 430 core

in vec2 textureCoords;

out vec4 fragmentColor;

uniform sampler2D fontMapSampler;
uniform vec4 fontColor;
uniform vec4 outlineColor;
uniform float smoothnessModifier;

const float fontWidth = 0.5f;
const float fontEdge = 0.1f;

const float outlineWidth = 0.75f;
const float outlineEdge = 0.075f;

float smoothFontEdge = fontEdge * smoothnessModifier;
float smoothOutlineEdge = outlineEdge * smoothnessModifier;

void main()
{
    float distance = 1.0f - texture(fontMapSampler, textureCoords).r;
    float fontAlpha = 1.0f - smoothstep(fontWidth, fontWidth + smoothFontEdge, distance);
    float edgeAlpha = 1.0f - smoothstep(outlineWidth, outlineWidth + smoothOutlineEdge, distance);

    float alpha = fontAlpha + (1.0f - fontAlpha) * edgeAlpha;
    vec4 color = mix(outlineColor, fontColor, fontAlpha / alpha);

    // Do not draw invisible fragments
    // Also enables characters overlapping
    if (alpha < 0.005f) {
        discard;
    }

    fragmentColor = vec4(color.rgb, alpha);
}
