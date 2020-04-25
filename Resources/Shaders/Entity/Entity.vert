#version 430 core

struct Light {
    vec3 position;
    vec3 attenuation;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureUV;
layout (location = 3) in vec3 vertexTangent;

out vec2 textureUV;
out vec3 normal;
out vec3 toLightVector;
out vec3 toCameraVector;
out vec4 relativeToCameraPosition;
out mat3 fromTangentSpace;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewMatrixInverse;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

uniform Light light;

struct TBN {
    vec3 tangent;
    vec3 normal;
    vec3 bitangent;
} tbn;

void main()
{
    // Pass texture coordinates
    textureUV = vertexTextureUV;

    vec4 vertexWorldPosition = modelMatrix * vec4(vertexPosition, 1.0f);
    
    toLightVector = light.position - vertexWorldPosition.xyz;
    toCameraVector = viewMatrixInverse[3].xyz - vertexWorldPosition.xyz;
    relativeToCameraPosition = viewMatrix * vertexWorldPosition;

    normal = normalMatrix * vertexNormal;

    // Tangent basis matrix calculation
    tbn.tangent = normalize(vec3(modelMatrix * vec4(vertexTangent, 0.0f)));
    tbn.normal = normalize(vec3(modelMatrix * vec4(vertexNormal, 0.0f)));
    tbn.bitangent = normalize(cross(vertexTangent, tbn.normal));
    tbn.tangent = normalize(tbn.tangent - dot(tbn.tangent, tbn.normal) * tbn.normal);
    fromTangentSpace = mat3(tbn.tangent, tbn.bitangent, tbn.normal);

    gl_Position = projectionMatrix * relativeToCameraPosition;
}
