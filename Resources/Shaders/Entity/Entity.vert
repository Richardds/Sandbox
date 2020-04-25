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

out vec3 fragmentPosition;
out vec2 textureUV;
out vec3 normal;
out vec3 toCameraVector;
out vec4 relativeToCameraPosition;
out mat3 fromTangentSpace;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewMatrixInverse;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

struct TBN {
    vec3 tangent;
    vec3 normal;
    vec3 bitangent;
} tbn;

void main()
{
    // Calculate vertex world position
    fragmentPosition = (modelMatrix * vec4(vertexPosition, 1.0f)).xyz;
    
    // Pass texture coordinates
    textureUV = vertexTextureUV;

    normal = normalMatrix * vertexNormal;

    toCameraVector = viewMatrixInverse[3].xyz - fragmentPosition;
    relativeToCameraPosition = viewMatrix * vec4(fragmentPosition, 1.0f);

    // Tangent basis matrix calculation
    tbn.tangent = normalize(vec3(modelMatrix * vec4(vertexTangent, 0.0f)));
    tbn.normal = normalize(vec3(modelMatrix * vec4(vertexNormal, 0.0f)));
    tbn.bitangent = normalize(cross(vertexTangent, tbn.normal));
    tbn.tangent = normalize(tbn.tangent - dot(tbn.tangent, tbn.normal) * tbn.normal);
    fromTangentSpace = mat3(tbn.tangent, tbn.bitangent, tbn.normal);

    gl_Position = projectionMatrix * relativeToCameraPosition;
}
