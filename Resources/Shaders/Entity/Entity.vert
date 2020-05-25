#version 430 core

struct TBN {
    vec3 tangent;
    vec3 normal;
    vec3 bitangent;
};

struct ClippingPlane {
    vec4 plane;
    bool enabled;
};

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_Texture;
layout (location = 3) in vec3 a_Tangent;

out vec4 fragmentPosition;
out vec2 textureCoords;
out vec3 normal;
out vec4 relativeToCameraPosition;
out mat3 fromTangentSpace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 viewInverse;
uniform mat4 worldTransformation;
uniform mat3 normalTransformation;
uniform ClippingPlane clippingPlane;
uniform float deformationFactor;

// TODO
vec3 twist(vec3 position, float factor)
{
	float sFactor = sin(factor);
	float cFactor = cos(factor);

	vec3 twistedPosition = position;
	twistedPosition.x = position.x * cFactor - position.z * sFactor;
	twistedPosition.z = position.x * sFactor + position.z * cFactor;

	return twistedPosition;
}

void main()
{
    vec3 vertexPosition = a_Position;

    // Apply twist deformation
    if (deformationFactor != 0.0f) {
        vertexPosition = twist(a_Position, deformationFactor);
    }

    // Calculate vertex world position
    fragmentPosition = worldTransformation * vec4(vertexPosition, 1.0f);

    // Apply culling if enabled
    if (clippingPlane.enabled) {
        gl_ClipDistance[0] = dot(fragmentPosition, clippingPlane.plane);
    }

    // Pass interpolated texture coordinates
    textureCoords = a_Texture;
    
    // Calculate normal relative to vertex position
    normal = normalTransformation * a_Normal;

    // Calculate position relative to the camera
    relativeToCameraPosition = view * fragmentPosition;

    // Tangent basis matrix calculation
    TBN tbn;
    tbn.tangent = normalize((worldTransformation * vec4(a_Tangent, 0.0f)).xyz);
    tbn.normal = normalize((worldTransformation * vec4(a_Normal, 0.0f)).xyz);
    tbn.tangent = normalize(tbn.tangent - dot(tbn.tangent, tbn.normal) * tbn.normal);
    tbn.bitangent = normalize(cross(tbn.normal, tbn.tangent));
    fromTangentSpace = mat3(tbn.tangent, tbn.bitangent, tbn.normal);

    // Apply projection
    gl_Position = projection * relativeToCameraPosition;
}
