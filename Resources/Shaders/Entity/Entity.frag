#version 430 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float reflectivity;
};

uniform sampler2D diffuseMapSampler;
uniform sampler2D normalMapSampler;

uniform bool hasDiffuseMap;
uniform bool hasNormalMap;

in vec2 textureUV;
in vec3 normal;
in vec3 toLightVector;
in vec3 toCameraVector;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;

out vec4 fragmentColor;

uniform vec3 lightColor;
uniform Material material;

const vec3 defaultDiffuseMapping = vec3(0.85f, 0.85f, 0.85f);

// Fog constants
const float fogDensity = 0.045f;
const float fogGradient = 2.5f;
const vec3 fogColor = vec3(0.25f, 0.25f, 0.25f);

// Light constants
const float ambientLightStrength = 0.1f;
const float shineStrength = 15.0f;
const float specularLightStrength  = 0.75f;

void main()
{
    // Normalize vectors
    vec3 unitNormal = normalize(normal);
    vec3 unitToLightVector = normalize(toLightVector);
    vec3 unitToCameraVector = normalize(toCameraVector);

    // Map diffuse color if it exists
    vec4 diffuseMapping = vec4(defaultDiffuseMapping, 1.0f);
    if (hasDiffuseMap) {
        diffuseMapping = texture(diffuseMapSampler, textureUV);
    }

    // Map normal vector if ot exists
    vec3 normalMapping = unitNormal;
    if (hasNormalMap) {
        normalMapping = normalize(fromTangentSpace * (2.0f * texture(normalMapSampler, textureUV, -1.0f) - 1.0f).xyz);
    }

    // Calculate fragment color using Phong lighting model
    vec3 ambient = ambientLightStrength * lightColor;
    vec3 diffuse = max(dot(normalMapping, unitToLightVector), 0.2f) * lightColor;
    vec3 reflectedLightDirection = reflect(-unitToLightVector, normalMapping);
    vec3 specular = pow(max(dot(reflectedLightDirection, unitToCameraVector), 0.0), shineStrength) * specularLightStrength * lightColor;
    vec4 phongModelColor = vec4(ambient + diffuse + specular, 1.0f) * diffuseMapping;

    // Calculate fragment visibility
    float distanceToCamera = length(relativeToCameraPosition.xyz);
    float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fogDensity, fogGradient)), 0.0f, 1.0f);

    // Combine Phong and visibility
    fragmentColor = mix(vec4(fogColor, 1.0f), phongModelColor, fragmentVisibility);
}
