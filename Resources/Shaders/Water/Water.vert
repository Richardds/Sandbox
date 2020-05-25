#version 430 core

struct TBN {
    vec3 tangent;
    vec3 normal;
    vec3 bitangent;
};

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_Texture;
layout (location = 3) in vec3 a_Tangent;

out vec4 fragmentPosition;
out vec2 textureCoords;
out vec3 normal;
out vec4 relativeToCameraPosition;
out vec4 position;
out mat3 fromTangentSpace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 viewInverse;
uniform mat4 worldTransformation;
uniform mat3 normalTransformation;
uniform float textureTiling;

void main()
{
    // Calculate vertex world position
    fragmentPosition = worldTransformation * vec4(a_Position, 1.0f);

    // Pass interpolated texture coordinates
    textureCoords = a_Texture * textureTiling;
    
    // Calculate vertex world position
    fragmentPosition = worldTransformation * vec4(a_Position, 1.0f);

    // Calculate normal relative to vertex position
    normal = normalTransformation * a_Normal;

    // Calculate position relative to the camera
    relativeToCameraPosition = view * fragmentPosition;
    
    // Apply projection and pass position to fragment shader
    position = projection * relativeToCameraPosition;

    // Tangent basis matrix calculation
    TBN tbn;
    tbn.tangent = normalize((worldTransformation * vec4(a_Tangent, 0.0f)).xyz);
    tbn.normal = normalize((worldTransformation * vec4(a_Normal, 0.0f)).xyz);
    tbn.tangent = normalize(tbn.tangent - dot(tbn.tangent, tbn.normal) * tbn.normal);
    tbn.bitangent = normalize(cross(tbn.normal, tbn.tangent));
    fromTangentSpace = mat3(tbn.tangent, tbn.bitangent, tbn.normal);

    gl_Position = position;
}
