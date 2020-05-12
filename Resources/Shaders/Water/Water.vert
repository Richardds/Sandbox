#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureUV;

out vec4 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 viewInverse;
uniform mat4 worldTransformation;
uniform mat3 normalTransformation;

void main()
{
    // Calculate vertex world position
    vec4 fragmentPosition = worldTransformation * vec4(vertexPosition, 1.0f);
    // Calculate position relative to the camera
    vec4 relativeToCameraPosition = view * fragmentPosition;
    // Apply projection
    position = projection * relativeToCameraPosition;
    
    gl_Position = position;
}
