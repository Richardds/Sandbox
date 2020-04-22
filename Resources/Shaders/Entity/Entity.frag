#version 430 core

layout (location = 2) in vec2 vertexTexture;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float reflectivity;
};

uniform sampler2D textureSampler;

in vec2 textureUV;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in vec4 relativeToCameraPosition;

out vec4 fragmentColor;

uniform vec3 lightColor;
uniform Material material;

const vec3 defaultColor = vec3(0.25f, 0.25f, 0.25f);

const float density = 0.045f;
const float gradient = 2.5f;

const float ambientLightStrength = 0.1f;
const float shineStrength = 15.0f;
const float specularLightStrength  = 0.75f;

void main()
{
    vec3 unitSurfaceNormal = normalize(surfaceNormal);
    vec3 unitToLightVector = normalize(toLightVector);
    vec3 unitToCameraVector = normalize(toCameraVector);

    vec3 ambient = ambientLightStrength * lightColor;

    vec3 diffuse = max(dot(unitSurfaceNormal, unitToLightVector), 0.2f) * lightColor;

    vec3 reflectedLightDirection = reflect(-unitToLightVector, unitSurfaceNormal);
    vec3 specular = pow(max(dot(reflectedLightDirection, unitToCameraVector), 0.0), shineStrength) * specularLightStrength * lightColor;

    vec4 textureColor = texture(textureSampler, textureUV);

    vec4 phongModelColor = vec4(ambient + diffuse + specular, 1.0f) * textureColor;

    float distance = length(relativeToCameraPosition.xyz);
    float visibility = clamp(exp(-pow(distance * density, gradient)), 0.0f, 1.0f);
    vec4 distanceColor = vec4(0.0f, visibility, 0.0f, 1.0f);
    
    //fragmentColor = distanceColor;
    fragmentColor = mix(vec4(defaultColor, 1.0f), phongModelColor, visibility);
}
