#include "Actor.h"
#include "../../Math/Utils.h"

Graphics::Actor::Actor() :
	_movingSpeed(5.0f)
{
}

void Graphics::Actor::Move(const float distance)
{
	this->IncreasePosition(Math::Vector3f(
		std::sinf(glm::radians(this->_rotationY)) * distance,
		0.0f,
		std::cosf(glm::radians(this->_rotationY)) * distance
	));
}

void Graphics::Actor::Update(const float delta)
{
	this->Move(this->_movingSpeed * delta);
}

void Graphics::Actor::LookAt(const Math::Vector2f target)
{
	this->_rotationY = Math::LookAt(
		Math::Vector2f(this->_position.x, this->_position.z),
		target
	);
}

float Graphics::Actor::DistanceTo(const Math::Vector2f target) const
{
	return distance(Math::Vector2f(this->_position.x, this->_position.z), target);
}
