#version 430 core

struct TextureSampler {
    sampler2D texture;
    bool enabled;
};

struct DirectionalLight {
    vec3 direction;
    vec3 diffuse;
    float intensity;
    float specular;
};

struct PointLight {
    vec3 position;
    vec3 attenuation;
    vec3 diffuse;
    float specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 diffuse;
    float specular;
};

struct Fog {
    bool enabled;
    float density;
    float gradient;
    vec3 color;
};

in vec4 fragmentPosition;
in vec2 textureCoords;
in vec3 normal;
in vec4 relativeToCameraPosition;
in vec4 position;
in mat3 fromTangentSpace;

out vec4 fragmentColor;

uniform vec3 viewPosition;

uniform TextureSampler normalSampler;
uniform TextureSampler distortionSampler;
uniform bool wavesEnabled;
uniform float distortionOffset;
uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;

uniform int directionalLightsCount;
uniform DirectionalLight directionalLights[3];

uniform int pointLightsCount;
uniform PointLight pointLights[10];

uniform bool flashLightEnabled;
uniform SpotLight flashLight;

uniform Fog fog;

const float distortionStrength = 0.005f;

const float waterTransparency = 0.95f;
const float waterSpecular = 0.125f;
const float waterShininess = 50.0f;

float diffuseFactor(vec3 lightDirection, vec3 normal)
{
    return max(dot(lightDirection, normal), 0.15f);
}

float specularFactor(float shininess, vec3 viewDirection, vec3 lightDirection, vec3 normal)
{
    vec3 reflectedLightDirection = reflect(-lightDirection, normal);
    return pow(max(dot(viewDirection, reflectedLightDirection), 0.0f), shininess);
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

    if (distortionSampler.enabled && wavesEnabled) {
        distortedTextureCoords = texture(distortionSampler.texture, vec2(textureCoords.x + distortionOffset, textureCoords.y)).rg * 0.25f;
        distortedTextureCoords = textureCoords + vec2(distortedTextureCoords.x, distortedTextureCoords.y + distortionOffset);
        distortion = (texture(distortionSampler.texture, distortedTextureCoords).rg * 2.0f - 1.0f) * distortionStrength;
    }

    vec3 normalMapping = unitNormal;
    if (normalSampler.enabled && wavesEnabled) {
        normalMapping = normalize(fromTangentSpace * vec3(texture(normalSampler.texture, distortedTextureCoords).rg * 2.0f - 1.0f, 1.0f));
    }

    vec2 reflectionTextureCoords = vec2(ndc.x, -ndc.y);
    vec2 refractionTextureCoords = ndc;

    reflectionTextureCoords += distortion;
    reflectionTextureCoords.x = clamp(reflectionTextureCoords.x, 0.0f, 1.0f);
    reflectionTextureCoords.y = clamp(reflectionTextureCoords.y, -1.0f, 0.0f);

    refractionTextureCoords += distortion;
    refractionTextureCoords = clamp(refractionTextureCoords, 0.0f, 1.0f);

    vec3 reflectionColor = texture(reflectionSampler, reflectionTextureCoords).rgb;
    vec3 refractionColor = texture(refractionSampler, refractionTextureCoords).rgb;

    // Calculate Fresnel effect
    float mixFactor = pow(dot(viewDirection, unitNormal), waterTransparency);

    // Calculate water color using reflection, refraction and fresnel effect
    vec3 waterDiffuse = mix(reflectionColor, refractionColor, mixFactor);

    // Apply slight bluish color
    waterDiffuse = mix(waterDiffuse, vec3(0.0f, 0.1f, 0.15f), 0.1f);

    // Calculate fragment color using Phong lighting model
    vec3 diffuse = vec3(0.0f);
    float specular = 0.0f;

    // Apply directional lights
    for (int index = 0; index < directionalLightsCount; index++) {
        vec3 direction = normalize(directionalLights[index].direction);
        // Do not use intensity on water. Entities reflected in the water are going to be dimmed by entity shader
        // which takes the directional light intensity into account.
        diffuse = directionalLights[index].diffuse * waterDiffuse * diffuseFactor(direction, normalMapping);
        specular = directionalLights[index].specular * waterSpecular * specularFactor(waterShininess, viewDirection, direction, normalMapping);
    }

    // Apply point lights
    for (int index = 0; index < pointLightsCount; index++) {
        vec3 direction = normalize(pointLights[index].position - fragmentPosition.xyz);
        float lightDistance = length(pointLights[index].position - fragmentPosition.xyz);
        float attenuation = pointLights[index].attenuation.x + (pointLights[index].attenuation.y * lightDistance) + (pointLights[index].attenuation.z * lightDistance * lightDistance);

        diffuse += (pointLights[index].diffuse * waterDiffuse * diffuseFactor(direction, normalMapping)) / attenuation;
        specular += (pointLights[index].specular * waterSpecular * specularFactor(waterShininess, viewDirection, direction, normalMapping)) / attenuation;
    }

    // Apply spot light if enabled
    if (flashLightEnabled) {
        vec3 direction = normalize(flashLight.position - fragmentPosition.xyz);
        float spot = dot(direction, normalize(-flashLight.direction));
        float transition = flashLight.cutOff - flashLight.outerCutOff;
        float intensity = clamp((spot - flashLight.outerCutOff) / transition, 0.0f, 1.0f);
        // Increase light in spot area
        if (spot > flashLight.outerCutOff) {
            diffuse += 0.5f * intensity * flashLight.diffuse * waterDiffuse * diffuseFactor(direction, normalMapping);
            specular += intensity * flashLight.specular * specularFactor(waterShininess, viewDirection, direction, normalMapping);
        }
    }

    fragmentColor = vec4(diffuse + specular, 1.0f); // Water + highlights
    fragmentColor = vec4(diffuse, 1.0f); // Water + highlights

    // Apply fog effect if enabled
    if (fog.enabled) {
        // Calculate fragment visibility
        float distanceToCamera = length(relativeToCameraPosition.xyz);
        float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fog.density, fog.gradient)), 0.0f, 1.0f);

        // Fade fragment color by visibility
        fragmentColor = vec4(mix(fog.color, waterDiffuse + specular, fragmentVisibility), 1.0f);
    }
}
