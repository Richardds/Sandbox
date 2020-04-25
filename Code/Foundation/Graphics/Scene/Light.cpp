#include "Light.h"
#include "../../Math/Utils.h"

Graphics::Light::Light() :
    HasPosition(),
    _color(1.0f, 1.0f, 1.0f),
    _attenuation(1.0f, 0.0f, 0.0f)
{
}

Graphics::Light::Light(Math::Vector3f position) :
    HasPosition(position),
    _color(1.0f, 1.0f, 1.0f),
    _attenuation(1.0f, 0.0f, 0.0f)
{
}

Graphics::Light::Light(Math::Vector3f position, Math::Vector3f color) :
    HasPosition(position),
    _color(color),
    _attenuation(1.0f, 0.0f, 0.0f)
{
}

Graphics::Light::Light(Math::Vector3f position, Math::Vector3f color, Math::Vector3f attenuation) :
    HasPosition(position),
    _color(color),
    _attenuation(attenuation)
{
}

Graphics::Light::~Light()
{
}

