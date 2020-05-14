#version 430 core

struct TextureSampler {
    sampler2D texture;
    bool enabled;
};

struct Sun {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    float specular;
};

struct Fog {
    float density;
    float gradient;
    vec3 color;
};

in vec4 fragmentPosition;
in vec2 textureUV;
in vec3 normal;
in vec3 toCameraVector;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;
in vec4 position;

out vec4 fragmentColor;

uniform TextureSampler normalSampler;
uniform TextureSampler distortionSampler;
uniform float distortionOffset;
uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;

uniform Sun sun;
uniform Fog fog;

const float distortionStrength = 0.01f;

const float waterTransparency = 0.75f;
const float waterSpecular = 0.8f;
const float waterShininess = 12.0f;

void main()
{
    // Normalize vectors
    vec3 unitNormal = normalize(normal);
    vec3 unitToCameraVector = normalize(toCameraVector);

    // Normalized device coordinates
    vec2 ndc = (position.xy / position.w) / 2.0f + 0.5f;

    vec2 distortion = vec2(0.0f, 0.0f);
    vec2 distortedTextureUV = textureUV;

    if (distortionSampler.enabled) {
        distortedTextureUV = texture(distortionSampler.texture, vec2(textureUV.x + distortionOffset, textureUV.y)).rg * 0.25f;
        distortedTextureUV = textureUV + vec2(distortedTextureUV.x, distortedTextureUV.y + distortionOffset);

        distortion = (texture(distortionSampler.texture, distortedTextureUV).rg * 2.0f - 1.0f) * distortionStrength;
    }

    vec3 normalMapping = unitNormal;
    if (normalSampler.enabled) {
        normalMapping = texture(normalSampler.texture, distortedTextureUV).rgb;
        normalMapping = normalize(fromTangentSpace * vec3(normalMapping.x * 2.0f - 1.0f, normalMapping.y, normalMapping.z * 2.0f - 1.0f));
    }

    vec2 reflectionTextureUV = vec2(ndc.x, -ndc.y);
    vec2 refractionTextureUV = ndc;

    reflectionTextureUV += distortion;
    reflectionTextureUV.x = clamp(reflectionTextureUV.x, 0.0f, 1.0f);
    reflectionTextureUV.y = clamp(reflectionTextureUV.y, -1.0f, 0.0f);

    refractionTextureUV += distortion;
    refractionTextureUV = clamp(refractionTextureUV, 0.0f, 1.0f);

    vec3 reflectionColor = texture(reflectionSampler, reflectionTextureUV).rgb;
    vec3 refractionColor = texture(refractionSampler, refractionTextureUV).rgb;

    // Calculate Fresnel effect
    float mixFactor = pow(dot(unitToCameraVector, unitNormal), waterTransparency);
    // Calculate water color using reflection, refraction and fresnel effect
    vec3 waterDiffuse = mix(reflectionColor, refractionColor, mixFactor);
    // Apply slight bluish color
    waterDiffuse = mix(waterDiffuse, vec3(0.0f, 0.1f, 0.2f), 0.1f);

    vec3 unitSunDirection = normalize(-sun.direction);
    vec3 reflectDirection = reflect(-unitSunDirection, normalMapping);
    float reflectSpecular = pow(max(dot(unitToCameraVector, reflectDirection), 0.0f), waterShininess);
    vec3 waterHighlights = sun.diffuse * reflectSpecular * waterSpecular;

    //fragmentColor = vec4(normalMapping, 1.0f);                      // Normal mapping
    fragmentColor = vec4(waterDiffuse + waterHighlights, 1.0f);     // Water + highlights
}
