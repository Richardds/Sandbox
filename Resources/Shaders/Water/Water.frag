#version 430 core

struct TextureSampler {
    sampler2D texture;
    bool enabled;
};

struct Sun {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Fog {
    float density;
    float gradient;
    vec3 color;
};

in vec2 textureUV;
in vec3 normal;
in vec3 toCameraVector;
in vec4 position;

out vec4 fragmentColor;

uniform TextureSampler distortionSampler;
uniform float distortionOffset;
uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;

uniform Sun sun;
uniform Fog fog;

const float distortionStrength = 0.02f;
const float waterReflectivity = 1.05f;

void main()
{
    // Normalize vectors
    vec3 unitNormal = normalize(normal);
    vec3 unitToCameraVector = normalize(toCameraVector);

    vec2 ndc = (position.xy / position.w) / 2.0f + 0.5f;

    vec2 distortion = vec2(0.0f, 0.0f);
    if (distortionSampler.enabled) {
        vec2 distortionTextureUV = ndc;
        vec2 distortion1 = (texture(distortionSampler.texture, vec2(textureUV.x + distortionOffset, textureUV.y)).rg * 2.0f - 1.0f) * distortionStrength;
        vec2 distortion2 = (texture(distortionSampler.texture, vec2(-textureUV.x + distortionOffset, textureUV.y + distortionOffset)).rg * 2.0f - 1.0f) * distortionStrength;
        distortion = distortion1 + distortion2;
    }

    vec2 reflectionTextureUV = vec2(ndc.x, -ndc.y);
    vec2 refractionTextureUV = ndc;

    reflectionTextureUV += distortion;
    reflectionTextureUV.x = clamp(reflectionTextureUV.x, 0.0f, 1.0f);
    reflectionTextureUV.y = clamp(reflectionTextureUV.y, -1.0f, 0.0f);

    refractionTextureUV += distortion;
    refractionTextureUV = clamp(refractionTextureUV, 0.001f, 0.999f);

    vec3 reflectionColor = texture(reflectionSampler, reflectionTextureUV).rgb;
    vec3 refractionColor = texture(refractionSampler, refractionTextureUV).rgb;

    float mixFactor = pow(dot(unitToCameraVector, unitNormal), waterReflectivity);
    vec4 waterColor = vec4(mix(reflectionColor, refractionColor, mixFactor), 1.0f);
    vec4 blueishWaterColor = mix(waterColor, vec4(0.0f, 0.1f, 0.3f, 1.0f), 0.1f);

    fragmentColor = blueishWaterColor;
}
