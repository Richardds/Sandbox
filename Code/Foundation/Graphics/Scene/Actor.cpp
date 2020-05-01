#include <cmath>

#include "Actor.h"
#include "../../Math/Utils.h"
#include "../../Core/Debug.h"

Graphics::Actor::Actor() :
    Actor(Math::Vector3f(0.0f, 0.0f, 0.0f), 0.0f)
{
}

Graphics::Actor::Actor(Math::Vector3f position, float rotY) :
    Entity(position, 0.0f, rotY, 0.0f),
    _movingSpeed(5.0f)
{
}

Graphics::Actor::~Actor()
{
}

void Graphics::Actor::Move(float distance)
{
    this->increasePosition(
        std::sinf(glm::radians(this->_rotY)) * distance,
        0.0f,
        std::cosf(glm::radians(this->_rotY)) * distance
    );
}

void Graphics::Actor::Update(float delta)
{
    this->Move(this->_movingSpeed * delta);
}

void Graphics::Actor::LookAt(Math::Vector2f target)
{
    this->_rotY = Math::LookAt(
        Math::Vector2f(this->_position.x, this->_position.z),
        target
    );
}

float Graphics::Actor::DistanceTo(Math::Vector2f target) const
{
    return glm::distance(Math::Vector2f(this->_position.x, this->_position.z), target);
}
