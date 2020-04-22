#include "../Attributes/HasRotation.h"

Graphics::HasRotation::HasRotation() :
    _rotX(0.0f),
    _rotY(0.0f),
    _rotZ(0.0f)
{
}

Graphics::HasRotation::HasRotation(float rotX, float rotY, float rotZ) :
    _rotX(rotX),
    _rotY(rotY),
    _rotZ(rotZ)
{
}

void Graphics::HasRotation::increaseRotation(float rotX, float rotY, float rotZ)
{
    this->_rotX += rotX;
    this->_rotY += rotY;
    this->_rotZ += rotZ;
}
