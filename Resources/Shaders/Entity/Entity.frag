#version 430 core

struct TextureSampler {
    sampler2D texture;
    bool enabled;
};

struct Light {
    vec3 position;
    vec3 attenuation;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Fog {
    float density;
    float gradient;
    vec3 color;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    float specular;
    float shininess;
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

void main()
{
    // Normalize vectors
    vec3 unitNormal = normalize(normal);
    vec3 unitToLightVector = normalize(toLightVector);
    vec3 unitToCameraVector = normalize(toCameraVector);

    // Map diffuse color
    vec3 materialDiffuse = material.diffuse;
    if (diffuseMapper.enabled) {
        materialDiffuse = texture(diffuseMapper.texture, textureUV).rgb;
        // Discard fragment when mapped to invisible
        if (materialDiffuse.r == 1.0f && materialDiffuse.b == 1.0f) {
            discard;
        }
    }

    // Map normal vector
    vec3 normalMapping = unitNormal;
    if (normalMapper.enabled) {
        normalMapping = normalize(fromTangentSpace * (2.0f * texture(normalMapper.texture, textureUV, -1.0f) - 1.0f).rgb);
    }

    // Map specular strength
    float materialSpecular = material.specular;
    if (specularMapper.enabled) {
        materialSpecular = texture(specularMapper.texture, textureUV).r;
    }

    float lightDistance = length(toLightVector);
    float lightAttenuationFactor = light.attenuation.x + (light.attenuation.y * lightDistance) + (light.attenuation.z * lightDistance * lightDistance);

    // Calculate fragment color using Phong lighting model
    vec3 ambient = light.ambient * material.ambient;

    float diff = max(dot(normalMapping, unitToLightVector), 0.2f);
    vec3 diffuse = light.diffuse * (diff * materialDiffuse);

    vec3 reflectedLightDirection = reflect(-unitToLightVector, normalMapping);
    float spec = pow(max(dot(unitToCameraVector, reflectedLightDirection), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * materialSpecular);

    vec3 phongModelColor = ambient + (diffuse / lightAttenuationFactor) + (specular / lightAttenuationFactor);

    // Calculate fragment visibility
    float distanceToCamera = length(relativeToCameraPosition.xyz);
    float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fog.density, fog.gradient)), 0.0f, 1.0f);

    // Fade fragment color by visibility
    vec3 fadedColor = mix(fog.color, phongModelColor, fragmentVisibility);

    //fragmentColor = vec4(fadedColor, 1.0f);
    fragmentColor = vec4(phongModelColor, 1.0f);
}
