#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureUV;

out vec3 fragmentPosition;
out vec2 textureUV;
out vec3 normal;
out vec3 toCameraVector;
out vec4 relativeToCameraPosition;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 viewInverse;
uniform mat4 worldTransformation;
uniform mat3 normalTransformation;

void main()
{
    // Calculate vertex world position
    fragmentPosition = (worldTransformation * vec4(vertexPosition, 1.0f)).xyz;
    
    // Pass texture coordinates
    textureUV = vertexTextureUV;

    normal = normalTransformation * vertexNormal;

    toCameraVector = viewInverse[3].xyz - fragmentPosition;
    relativeToCameraPosition = view * vec4(fragmentPosition, 1.0f);

    gl_Position = projection * relativeToCameraPosition;
}
