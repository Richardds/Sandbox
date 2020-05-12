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

in vec4 position;

out vec4 fragmentColor;

uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;

uniform Sun sun;
uniform Fog fog;

void main()
{
    vec2 ndc = (position.xy / position.w) / 2.0f + 0.5f;
    vec2 reflectionTextureUV = vec2(ndc.x, -ndc.y);
    vec2 refractionTextureUV = ndc;

    vec3 reflectionColor = texture(reflectionSampler, reflectionTextureUV).rgb;
    vec3 refractionColor = texture(refractionSampler, refractionTextureUV).rgb;

    fragmentColor = vec4(mix(reflectionColor, refractionColor, 0.5f), 1.0f);
}
