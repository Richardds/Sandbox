#version 430 core

struct TextureSampler {
    sampler2D texture;
    bool enabled;
};

struct Light {
    vec3 position;
    vec3 color;
};

struct Fog {
    float density;
    float gradient;
    vec3 color;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float reflectivity;
};

in vec2 textureUV;
in vec3 normal;
in vec3 toLightVector;
in vec3 toCameraVector;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;

out vec4 fragmentColor;

uniform TextureSampler diffuseMapper;
uniform TextureSampler normalMapper;
uniform TextureSampler specularMapper;
uniform TextureSampler materialMapper;

uniform Light light;
uniform Fog fog;
uniform Material material;

const vec3 defaultDiffuseMapping = vec3(0.85f, 0.85f, 0.85f);
const float defaultSpecularMapping = 0.5f;

// Light constants
const float ambientStrength = 0.1f;
const float shineStrength = 15.0f;

void main()
{
    // Normalize vectors
    vec3 unitNormal = normalize(normal);
    vec3 unitToLightVector = normalize(toLightVector);
    vec3 unitToCameraVector = normalize(toCameraVector);

    // Map diffuse color
    vec4 diffuseMapping = vec4(defaultDiffuseMapping, 1.0f);
    if (diffuseMapper.enabled) {
        diffuseMapping = texture(diffuseMapper.texture, textureUV);
        // Discard fragment when mapped to invisible
        if (diffuseMapping.r == 1.0f && diffuseMapping.b == 1.0f) {
            discard;
        }
    }

    // Map normal vector
    vec3 normalMapping = unitNormal;
    if (normalMapper.enabled) {
        normalMapping = normalize(fromTangentSpace * (2.0f * texture(normalMapper.texture, textureUV, -1.0f) - 1.0f).rgb);
    }

    // Map specular strength
    float specularMapping = defaultSpecularMapping;
    if (specularMapper.enabled) {
        specularMapping = texture(specularMapper.texture, textureUV).r;
    }

    // Calculate fragment color using Phong lighting model
    vec3 ambient = ambientStrength * light.color;
    vec3 diffuse = max(dot(normalMapping, unitToLightVector), 0.2f) * light.color;
    vec3 reflectedLightDirection = reflect(-unitToLightVector, normalMapping);
    vec3 specular = pow(max(dot(reflectedLightDirection, unitToCameraVector), 0.2f), shineStrength) * specularMapping * light.color;
    vec4 phongModelColor = vec4(ambient + diffuse + specular, 1.0f) * diffuseMapping;

    // Calculate fragment visibility
    float distanceToCamera = length(relativeToCameraPosition.xyz);
    float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fog.density, fog.gradient)), 0.0f, 1.0f);

    // Combine Phong and visibility
    fragmentColor = mix(vec4(fog.color, 1.0f), phongModelColor, fragmentVisibility);
}
