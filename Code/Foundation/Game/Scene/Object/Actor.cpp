// ----------------------------------------------------------------------------------------
//  \file       Actor.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Object/Actor.h"
#include "Math/MathUtils.h"

Graphics::Actor::Actor() :
    _movingSpeed(2.0f),
    _turningSpeed(100.0f)
{
}

void Graphics::Actor::Move(const float distance)
{
    const float rotationRadians = glm::radians(this->_rotation.y);
    this->IncreasePosition(Math::Vector3f(
        glm::sin(rotationRadians) * distance,
        0.0f,
        glm::cos(rotationRadians) * distance
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
    this->IncreaseRotationY(-1.0f * this->_turningSpeed * delta);
}

void Graphics::Actor::LookAt(const Math::Vector2f& target)
{
    this->_rotation.y = Math::LookAt(
        Math::Vector2f(this->_position.x, this->_position.z),
        target
    );
}

float Graphics::Actor::LookAtDiff(const Math::Vector2f& target) const
{
    return Math::LookAtDiff(
        Math::Vector2f(this->_position.x, this->_position.z),
        this->_rotation.y,
        target
    );
}

float Graphics::Actor::DistanceTo(const Math::Vector2f& target) const
{
    return Math::DistanceTo(Math::Vector2f(this->_position.x, this->_position.z), target);
}
