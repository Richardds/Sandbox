#include "DirectionalLight.h"

Graphics::DirectionalLight::DirectionalLight() :
    _direction(Math::Vector3f(0.0f, -1.0f, 0.0f)),
    _color(Math::Vector3f(1.0f, 1.0f, 1.0f))
{
}

Graphics::DirectionalLight::~DirectionalLight()
{
}
