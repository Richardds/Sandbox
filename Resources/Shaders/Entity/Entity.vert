#version 430 core

struct ClippingPlane {
    vec4 plane;
    bool enabled;
};

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureUV;
layout (location = 3) in vec3 vertexTangent;

out vec4 fragmentPosition;
out vec2 textureUV;
out vec3 normal;
out vec3 toCameraVector;
out vec4 relativeToCameraPosition;
out mat3 fromTangentSpace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 viewInverse;
uniform mat4 worldTransformation;
uniform mat3 normalTransformation;
uniform ClippingPlane clippingPlane;

struct TBN {
    vec3 tangent;
    vec3 normal;
    vec3 bitangent;
} tbn;

void main()
{
    // Pass texture coordinates
    textureUV = vertexTextureUV;

    // Calculate vertex world position
    fragmentPosition = worldTransformation * vec4(vertexPosition, 1.0f);
    
    if (clippingPlane.enabled) {
        gl_ClipDistance[0] = dot(fragmentPosition, clippingPlane.plane);
    }

    normal = normalTransformation * vertexNormal;

    relativeToCameraPosition = view * fragmentPosition;

    // Calculate viewing vector
    toCameraVector = viewInverse[3].xyz - fragmentPosition.xyz;

    // Tangent basis matrix calculation
    tbn.tangent = normalize(vec3(worldTransformation * vec4(vertexTangent, 0.0f)));
    tbn.normal = normalize(vec3(worldTransformation * vec4(vertexNormal, 0.0f)));
    tbn.bitangent = normalize(cross(vertexTangent, tbn.normal));
    tbn.tangent = normalize(tbn.tangent - dot(tbn.tangent, tbn.normal) * tbn.normal);
    fromTangentSpace = mat3(tbn.tangent, tbn.bitangent, tbn.normal);

    // Apply projection
    gl_Position = projection * relativeToCameraPosition;
}
