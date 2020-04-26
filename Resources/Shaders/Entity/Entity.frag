#version 430 core

struct TextureSampler {
    sampler2D texture;
    bool enabled;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 attenuation;
    vec3 diffuse;
    vec3 specular;
};

struct Fog {
    float density;
    float gradient;
    vec3 color;
};

struct Material {
    vec3 diffuse;
    vec3 specular;
    float reflectivity;
};

in vec3 fragmentPosition;
in vec2 textureUV;
in vec3 normal;
in vec3 toCameraVector;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;

out vec4 fragmentColor;

uniform TextureSampler diffuseSampler;
uniform TextureSampler normalSampler;
uniform TextureSampler specularSampler;
uniform TextureSampler materialSampler;

uniform int lightsCount;
uniform DirectionalLight sun;
uniform PointLight light[10];
uniform Fog fog;
uniform Material material;

void main()
{
    // Normalize vectors
    vec3 unitNormal = normalize(normal);
    vec3 unitToCameraVector = normalize(toCameraVector);

    // Map diffuse color
    vec3 materialDiffuse = material.diffuse;
    if (diffuseSampler.enabled) {
        materialDiffuse = texture(diffuseSampler.texture, textureUV).rgb;
        // Discard fragment when mapped to invisible
        if (materialDiffuse.r == 1.0f && materialDiffuse.b == 1.0f) {
            discard;
        }
    }

    // Map normal vector
    vec3 normalMapping = unitNormal;
    if (normalSampler.enabled) {
        normalMapping = normalize(fromTangentSpace * (2.0f * texture(normalSampler.texture, textureUV, -1.0f) - 1.0f).rgb);
    }

    // Map specular strength
    vec3 materialSpecular = material.specular;
    if (specularSampler.enabled) {
        materialSpecular = texture(specularSampler.texture, textureUV).rgb;
    }

    // Calculate fragment color using Phong lighting model
    vec3 unitSunDirection = normalize(-sun.direction);
    vec3 ambient = sun.ambient * materialDiffuse;
    vec3 diffuse = sun.diffuse * (max(dot(normalMapping, unitSunDirection), 0.0f) * materialDiffuse);
    vec3 specular = sun.specular * (pow(max(dot(unitToCameraVector, reflect(-unitSunDirection, normalMapping)), 0.0f), material.reflectivity) * materialSpecular);

    for (int index = 0; index < lightsCount; index++) {
        vec3 lightDirection = light[index].position - fragmentPosition;
        vec3 unitLightDirection = normalize(lightDirection);

        float lightDistance = length(lightDirection);
        float lightAttenuationFactor = light[index].attenuation.x + (light[index].attenuation.y * lightDistance) + (light[index].attenuation.z * lightDistance * lightDistance);

        float diff = max(dot(normalMapping, unitLightDirection), 0.2f);
        diffuse += (light[index].diffuse * (diff * materialDiffuse)) / lightAttenuationFactor;

        vec3 reflectedLightDirection = reflect(-unitLightDirection, normalMapping);
        float spec = pow(max(dot(unitToCameraVector, reflectedLightDirection), 0.0f), material.reflectivity) / lightAttenuationFactor;
        specular += light[index].specular * (spec * materialSpecular);
    }

    vec3 phongModelColor = ambient + diffuse + specular;

    // Calculate fragment visibility
    float distanceToCamera = length(relativeToCameraPosition.xyz);
    float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fog.density, fog.gradient)), 0.0f, 1.0f);

    // Fade fragment color by visibility
    vec3 fadedColor = mix(fog.color, phongModelColor, fragmentVisibility);

    fragmentColor = vec4(phongModelColor, 1.0f);
    //fragmentColor = vec4(fadedColor, 1.0f);
}
