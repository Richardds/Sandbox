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
in vec2 textureCoords;
in vec3 normal;
in vec4 relativeToCameraPosition;
in mat3 fromTangentSpace;

out vec4 fragmentColor;

uniform vec3 viewPosition;

uniform TextureSampler diffuseSampler;
uniform TextureSampler normalSampler;
uniform TextureSampler specularSampler;

uniform Sun sun;
uniform int lightsCount;
uniform PointLight light[10];
uniform Fog fog;
uniform Material material;

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

void main()
{
    // Calculate view position
    vec3 viewDirection = normalize(viewPosition - fragmentPosition.xyz);

    // Normalize normal vector
    vec3 unitNormal = normalize(normal);

    // Map diffuse color
    vec3 materialDiffuse = material.color;
    if (diffuseSampler.enabled) {
        materialDiffuse = texture(diffuseSampler.texture, textureCoords).rgb;
        // Discard fragment when mapped to invisible
        if (materialDiffuse.r == 1.0f && materialDiffuse.b == 1.0f) {
            discard;
        }
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
    vec3 sunDirection = normalize(sun.direction);
    
    vec3 ambient = sun.ambient * materialDiffuse;
    vec3 diffuse = sun.diffuse * materialDiffuse * diffuseFactor(sunDirection, normalMapping);
    float specular = sun.specular * material.specular * specularFactor(material.shininess, viewDirection, sunDirection, normalMapping);

    for (int index = 0; index < lightsCount; index++) {
        vec3 lightDirection = normalize(light[index].position - fragmentPosition.xyz);
        float lightDistance = length(light[index].position - fragmentPosition.xyz);
        float attenuation = light[index].attenuation.x + (light[index].attenuation.y * lightDistance) + (light[index].attenuation.z * lightDistance * lightDistance);

        diffuse += (light[index].diffuse * materialDiffuse * diffuseFactor(lightDirection, normalMapping)) / attenuation;
        specular += (light[index].specular * material.specular * specularFactor(material.shininess, viewDirection, lightDirection, normalMapping)) / attenuation;
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
