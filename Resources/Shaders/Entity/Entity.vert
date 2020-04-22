#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureUV;

out vec2 textureUV;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out vec4 relativeToCameraPosition;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewMatrixInverse;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

uniform vec3 lightPosition;

void main()
{
    // Pass texture coordinates
    textureUV = vertexTextureUV;

    vec4 vertexWorldPosition = modelMatrix * vec4(vertexPosition, 1.0f);
    
    relativeToCameraPosition = viewMatrix * vertexWorldPosition;

    surfaceNormal = normalMatrix * vertexNormal;
    toLightVector = lightPosition - vertexWorldPosition.xyz;
    toCameraVector = viewMatrixInverse[3].xyz - vertexWorldPosition.xyz;

    gl_Position = projectionMatrix * relativeToCameraPosition;
}
