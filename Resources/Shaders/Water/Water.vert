#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureUV;

out vec2 textureUV;
out vec3 normal;
out vec3 toCameraVector;
out vec4 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 viewInverse;
uniform mat4 worldTransformation;
uniform mat3 normalTransformation;

void main()
{
    // Pass texture coordinates
    textureUV = vertexTextureUV * 4.0f;
    
    // Calculate vertex world position
    vec4 fragmentPosition = worldTransformation * vec4(vertexPosition, 1.0f);
    // Calculate position relative to the camera
    vec4 relativeToCameraPosition = view * fragmentPosition;
    // Apply projection
    position = projection * relativeToCameraPosition;

    normal = normalTransformation * vertexNormal;

    // Calculate viewing vector
    toCameraVector = viewInverse[3].xyz - fragmentPosition.xyz;

    gl_Position = position;
}
