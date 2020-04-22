#include <cmath>

#include "../Attributes/HasPosition.h"
#include "../../Core/Debug.h"

Graphics::HasPosition::HasPosition() :
    _position()
{
}

Graphics::HasPosition::HasPosition(Math::Vector3f position) :
    _position(position)
{
}

float Graphics::HasPosition::getPositionX() const
{
    return this->_position.x;
}

void Graphics::HasPosition::setPositionX(float x)
{
    this->_position.x = x;
}

float Graphics::HasPosition::getPositionY() const
{
    return this->_position.y;
}

void Graphics::HasPosition::setPositionY(float y)
{
    this->_position.y = y;
}

float Graphics::HasPosition::getPositionZ() const
{
    return this->_position.z;
}

void Graphics::HasPosition::setPositionZ(float z)
{
    this->_position.z = z;
}

void Graphics::HasPosition::increasePosition(float x, float y, float z)
{
    this->_position.x += x;
    this->_position.y += y;
    this->_position.z += z;
}

void Graphics::HasPosition::increasePosition(Math::Vector3f modifier)
{
    this->_position += modifier;
}
