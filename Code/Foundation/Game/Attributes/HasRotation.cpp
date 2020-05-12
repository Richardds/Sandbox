#include "../Attributes/HasRotation.h"

Graphics::HasRotation::HasRotation() :
    HasRotation(0.0f, 0.0f, 0.0f)
{
}

Graphics::HasRotation::HasRotation(float rotX, float rotY, float rotZ) :
    _rotX(rotX),
    _rotY(rotY),
    _rotZ(rotZ)
{
}
