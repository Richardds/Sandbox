#version 430 core

struct Sun {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Fog {
    float density;
    float gradient;
    vec3 color;
};

in vec3 fragmentPosition;
in vec2 textureUV;
in vec3 normal;
in vec3 toCameraVector;
in vec4 relativeToCameraPosition;

out vec4 fragmentColor;

uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;

uniform Sun sun;
uniform Fog fog;

void main()
{
    vec3 reflection = texture(reflectionSampler, textureUV).rgb;

    fragmentColor = vec4(reflection, 1.0f);
}
