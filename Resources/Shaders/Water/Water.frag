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
in vec2 textureCoords;
in vec3 normal;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;
in vec4 position;

out vec4 fragmentColor;

uniform vec3 viewPosition;

uniform TextureSampler normalSampler;
uniform TextureSampler distortionSampler;
uniform float distortionOffset;
uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;
uniform sampler2D depthSampler;

uniform Sun sun;
uniform Fog fog;

const float distortionStrength = 0.01f;

const float waterTransparency = 0.95f;
const float waterSpecular = 0.125f;
const float waterShininess = 50.5f;

const float minDiffuseFactor = 0.2f;

float diffuseFactor(vec3 lightDirection, vec3 normal)
{
    return max(dot(lightDirection, normal), minDiffuseFactor);
}

float specularFactor(float shininess, vec3 viewDirection, vec3 lightDirection, vec3 normal)
{
    vec3 reflectedLightDirection = reflect(lightDirection, normal);
    return pow(max(dot(viewDirection, reflectedLightDirection), 0.0f), shininess);
}

float deproject(float value, float nearPlane, float farPlane)
{
    return 2.0f * nearPlane * farPlane / (farPlane + nearPlane - (2.0f * value - 1.0f) * (farPlane - nearPlane));
}

void main()
{
    // Calculate view position
    vec3 viewDirection = normalize(viewPosition - fragmentPosition.xyz);

    // Normalize normal vector
    vec3 unitNormal = normalize(normal);

    // Normalized device coordinates
    vec2 ndc = (position.xy / position.w) / 2.0f + 0.5f;

    // Calculate texture distortion
    vec2 distortion = vec2(0.0f, 0.0f);
    vec2 distortedTextureCoords = textureCoords;

    if (distortionSampler.enabled) {
        distortedTextureCoords = texture(distortionSampler.texture, vec2(textureCoords.x + distortionOffset, textureCoords.y)).rg * 0.25f;
        distortedTextureCoords = textureCoords + vec2(distortedTextureCoords.x, distortedTextureCoords.y + distortionOffset);
        distortion = (texture(distortionSampler.texture, distortedTextureCoords).rg * 2.0f - 1.0f) * distortionStrength;
    }

    vec3 normalMapping = unitNormal;
    if (normalSampler.enabled) {
        normalMapping = texture(normalSampler.texture, distortedTextureCoords).rgb;
        normalMapping = normalize(fromTangentSpace * vec3(normalMapping.x * 2.0f - 1.0f, normalMapping.y, normalMapping.z * 2.0f - 1.0f));
    }

    vec2 reflectionTextureCoords = vec2(ndc.x, -ndc.y);
    vec2 refractionTextureCoords = ndc;

    reflectionTextureCoords += distortion;
    reflectionTextureCoords.x = clamp(reflectionTextureCoords.x, 0.0f, 1.0f);
    reflectionTextureCoords.y = clamp(reflectionTextureCoords.y, -1.0f, 0.0f);

    refractionTextureCoords += distortion;
    refractionTextureCoords = clamp(refractionTextureCoords, 0.0f, 1.0f);

    const float nearPlane = 0.01f;
    const float farPlane = 1000.f;

    float floorDistance = deproject(texture(depthSampler, refractionTextureCoords).r, nearPlane, farPlane);
    float waterDistance = deproject(gl_FragCoord.z, nearPlane, farPlane);
    float waterDepth = floorDistance - waterDistance;
    float waterAlpha = clamp(waterDepth * 1000.0f, 0.0f, 1.0f);

    vec3 reflectionColor = texture(reflectionSampler, reflectionTextureCoords).rgb;
    vec3 refractionColor = texture(refractionSampler, refractionTextureCoords).rgb;

    // Calculate Fresnel effect
    float mixFactor = pow(dot(viewDirection, unitNormal), waterTransparency);

    // Calculate water color using reflection, refraction and fresnel effect
    vec3 waterDiffuse = mix(reflectionColor, refractionColor, mixFactor);

    // Apply slight bluish color
    waterDiffuse = mix(waterDiffuse, vec3(0.0f, 0.1f, 0.2f), 0.1f);

    vec3 sunDirection = normalize(sun.direction);
    float specular = sun.specular * waterSpecular * specularFactor(waterShininess, viewDirection, sunDirection, normalMapping);

    // Calculate fragment visibility
    float distanceToCamera = length(relativeToCameraPosition.xyz);
    float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fog.density, fog.gradient)), 0.0f, 1.0f);

    // Fade fragment color by visibility
    vec3 fadedColor = mix(fog.color, waterDiffuse + specular, fragmentVisibility);

    //fragmentColor = vec4(normalMapping, 1.0f);            // Normal mapping
    fragmentColor = vec4(waterDiffuse + specular, 1.0f);  // Water + highlights
    //fragmentColor = vec4(fadedColor, 1.0f);                 // Water + highlights + Fog
    //fragmentColor = vec4(fadedColor, waterAlpha);         // Water + highlights + Fog + Transparency?
}
