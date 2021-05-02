#version 430 core

struct TextureSampler {
    sampler2D texture;
    bool enabled;
};

struct TextureCubeSampler {
    samplerCube texture;
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

struct Material {
    vec3 color;
    float reflectivity;
    float specular;
    float shininess;
};

in vec4 fragmentPosition;
in vec2 textureCoords;
in vec3 normal;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;

out vec4 fragmentColor;

uniform vec3 viewPosition;

uniform TextureSampler diffuseSampler;
uniform TextureSampler normalSampler;
uniform TextureSampler specularSampler;

uniform TextureCubeSampler skyboxSampler;

uniform int directionalLightsCount;
uniform DirectionalLight directionalLights[3];

uniform int pointLightsCount;
uniform PointLight pointLights[10];

uniform bool flashLightEnabled;
uniform SpotLight flashLight;

uniform Fog fog;
uniform Material material;

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

    // Map diffuse color
    vec3 materialDiffuse = material.color;
    if (diffuseSampler.enabled) {
        vec4 textureDiffuseSample = texture(diffuseSampler.texture, textureCoords);
        // Discard fragment when mapped to invisible
        if (textureDiffuseSample.a < 0.8f) {
            discard;
        }
        materialDiffuse = textureDiffuseSample.rgb;
    }

    // Map normal vector
    vec3 normalMapping = unitNormal;
    if (normalSampler.enabled) {
        normalMapping = normalize(fromTangentSpace * (texture(normalSampler.texture, textureCoords).rgb * 2.0f - 1.0f));
    }

    // Map specular strength
    float materialSpecular = material.specular;
    if (specularSampler.enabled) {
        materialSpecular = texture(specularSampler.texture, textureCoords).r;
    }

    // Calculate fragment color using Phong lighting model
    vec3 diffuse = vec3(0.0f);
    float specular = 0.0f;

    // Apply directional lights
    for (int index = 0; index < directionalLightsCount; index++) {
        vec3 direction = normalize(directionalLights[index].direction);
        diffuse = directionalLights[index].diffuse * directionalLights[index].intensity * materialDiffuse * diffuseFactor(direction, normalMapping);
        specular = directionalLights[index].specular * materialSpecular * specularFactor(material.shininess, viewDirection, direction, normalMapping);
    }

    // Apply point lights
    for (int index = 0; index < pointLightsCount; index++) {
        vec3 direction = normalize(pointLights[index].position - fragmentPosition.xyz);
        float lightDistance = length(pointLights[index].position - fragmentPosition.xyz);
        float attenuation = pointLights[index].attenuation.x + (pointLights[index].attenuation.y * lightDistance) + (pointLights[index].attenuation.z * lightDistance * lightDistance);

        diffuse += (pointLights[index].diffuse * materialDiffuse * diffuseFactor(direction, normalMapping)) / attenuation;
        specular += (pointLights[index].specular * materialSpecular * specularFactor(material.shininess, viewDirection, direction, normalMapping)) / attenuation;
    }

    // Apply spot light if enabled
    if (flashLightEnabled) {
        vec3 direction = normalize(flashLight.position - fragmentPosition.xyz);
        float spot = dot(direction, normalize(-flashLight.direction));
        float transition = flashLight.cutOff - flashLight.outerCutOff;
        float intensity = clamp((spot - flashLight.outerCutOff) / transition, 0.0f, 1.0f);
        // Increase light in spot area
        if (spot > flashLight.outerCutOff) {
            diffuse += intensity * flashLight.diffuse * materialDiffuse * diffuseFactor(direction, normalMapping);
            specular += intensity * flashLight.specular * materialSpecular * specularFactor(material.shininess, viewDirection, direction, normalMapping);
        }
    }

    vec3 phongModelColor = diffuse + specular;

    fragmentColor = vec4(phongModelColor, 1.0f); // Phong lighting

    // Apply skybox reflectivity effect
    if (skyboxSampler.enabled && material.reflectivity > 0.0f) {
        vec3 reflectedCoordinate = reflect(-viewDirection, unitNormal);
        vec3 reflectedColor = texture(skyboxSampler.texture, reflectedCoordinate).rgb;
        fragmentColor = mix(fragmentColor, vec4(reflectedColor, 1.0f), material.reflectivity);
    }

    // Apply fog effect if enabled
    if (fog.enabled) {
        // Calculate fragment visibility
        float distanceToCamera = length(relativeToCameraPosition.xyz);
        float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fog.density, fog.gradient)), 0.0f, 1.0f);

        // Fade fragment color by visibility
        fragmentColor = vec4(mix(fog.color, phongModelColor, fragmentVisibility), 1.0f);
    }

    //fragmentColor = vec4(normalMapping, 1.0f);        // Debug normal mapping
}
