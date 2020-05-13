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

struct PointLight {
    vec3 position;
    vec3 attenuation;
    vec3 ambient;
    vec3 diffuse;
    float specular;
};

struct Fog {
    float density;
    float gradient;
    vec3 color;
};

struct Material {
    vec3 color;
    float specular;
    float shininess;
};

in vec4 fragmentPosition;
in vec2 textureUV;
in vec3 normal;
in vec3 toCameraVector;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;

out vec4 fragmentColor;

uniform TextureSampler diffuseSampler;
uniform TextureSampler normalSampler;
uniform TextureSampler specularSampler;

uniform Sun sun;
uniform int lightsCount;
uniform PointLight light[10];
uniform Fog fog;
uniform Material material;

void main()
{
    // Normalize vectors
    vec3 unitNormal = normalize(normal);
    vec3 unitToCameraVector = normalize(toCameraVector);

    // Map diffuse color
    vec3 materialDiffuse = material.color;
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
        normalMapping = normalize(fromTangentSpace * (texture(normalSampler.texture, textureUV).rgb * 2.0f - 1.0f));
    }

    // Map specular strength
    float materialSpecular = material.specular;
    if (specularSampler.enabled) {
        materialSpecular = texture(specularSampler.texture, textureUV).r;
    }

    // Calculate fragment color using Phong lighting model
    vec3 unitSunDirection = normalize(-sun.direction);
    
    vec3 ambient = sun.ambient * materialDiffuse;

    float dynamicDiffuse = max(dot(normalMapping, unitSunDirection), 0.2f);
    vec3 diffuse = sun.diffuse * dynamicDiffuse * materialDiffuse;

    vec3 reflectDirection = reflect(-unitSunDirection, normalMapping);
    float reflectSpecular = pow(max(dot(unitToCameraVector, reflectDirection), 0.0f), material.shininess);
    float specular = sun.specular * reflectSpecular * materialSpecular;

    for (int index = 0; index < lightsCount; index++) {
        vec3 lightDirection = light[index].position - fragmentPosition.xyz;
        vec3 unitLightDirection = normalize(lightDirection);

        float lightDistance = length(lightDirection);
        float lightAttenuationFactor = light[index].attenuation.x + (light[index].attenuation.y * lightDistance) + (light[index].attenuation.z * lightDistance * lightDistance);

        dynamicDiffuse = max(dot(normalMapping, unitLightDirection), 0.2f);
        diffuse += (light[index].diffuse * dynamicDiffuse * materialDiffuse) / lightAttenuationFactor;

        reflectDirection = reflect(-unitLightDirection, normalMapping);
        reflectSpecular = pow(max(dot(unitToCameraVector, reflectDirection), 0.0f), material.shininess);
        specular += (light[index].specular * reflectSpecular * materialSpecular) / lightAttenuationFactor;
    }

    vec3 phongModelColor = ambient + diffuse + specular;

    // Calculate fragment visibility
    float distanceToCamera = length(relativeToCameraPosition.xyz);
    float fragmentVisibility = clamp(exp(-pow(distanceToCamera * fog.density, fog.gradient)), 0.0f, 1.0f);

    // Fade fragment color by visibility
    vec3 fadedColor = mix(fog.color, phongModelColor, fragmentVisibility);

    //fragmentColor = vec4(vec3(gl_FragCoord.z), 1.0f);   // Depth mapping
    //fragmentColor = vec4(normalMapping, 1.0f);          // Normal mapping
    //fragmentColor = vec4(phongModelColor, 1.0f);        // Phong
    fragmentColor = vec4(fadedColor, 1.0f);             // Phong + Fog
}
