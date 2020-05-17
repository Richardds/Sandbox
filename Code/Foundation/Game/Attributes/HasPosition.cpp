#include "../Attributes/HasPosition.h"

Graphics::HasPosition::HasPosition() :
	_position()
{
}

Graphics::HasPosition::HasPosition(const Math::Vector3f& position) :
	_position(position)
{
}
