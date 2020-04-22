#include "Light.h"
#include "../../Math/Utils.h"

Graphics::Light::Light() :
    HasPosition(),
    _color(1.0f, 1.0f, 1.0f)
{
}

Graphics::Light::Light(Math::Vector3f position) :
    HasPosition(position),
    _color(1.0f, 1.0f, 1.0f)
{
}

Graphics::Light::Light(Math::Vector3f position, Math::Vector3f color) :
    HasPosition(position),
    _color(color)
{
}

Graphics::Light::~Light()
{
}

void Graphics::Light::SetColor(const Math::Vector3f& color)
{
    this->_color = color;
}
