#include "Precompiled.h"
#include "Game/Scene/Actor.h"
#include "Math/Utils.h"

Graphics::Actor::Actor() :
	_movingSpeed(5.0f),
	_turningSpeed(180.0f)
{
}

void Graphics::Actor::Move(const float distance)
{
	this->IncreasePosition(Math::Vector3f(
		glm::sin(glm::radians(this->_rotationY)) * distance,
		0.0f,
		glm::cos(glm::radians(this->_rotationY)) * distance
	));
}

void Graphics::Actor::GoForward(const float delta)
{
	this->Move(this->_movingSpeed * delta);
}

void Graphics::Actor::TurnLeft(const float delta)
{
	this->IncreaseRotationY(this->_turningSpeed * delta);
}

void Graphics::Actor::TurnRight(const float delta)
{
	this->IncreaseRotationY(-1 * this->_turningSpeed * delta);
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
