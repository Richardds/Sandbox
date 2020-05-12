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
