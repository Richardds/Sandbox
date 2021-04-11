// ----------------------------------------------------------------------------------------
//  \file       Actor.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
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
    this->IncreaseRotationY(-1.0f * this->_turningSpeed * delta);
}

void Graphics::Actor::LookAt(const Math::Vector2f& target)
{
    this->_rotationY = Math::LookAt(
        Math::Vector2f(this->_position.x, this->_position.z),
        target
    );
}

float Graphics::Actor::LookAtDiff(const Math::Vector2f& target) const
{
    return Math::LookAtDiff(
        Math::Vector2f(this->_position.x, this->_position.z),
        this->_rotationY,
        target
    );
}

float Graphics::Actor::DistanceTo(const Math::Vector2f& target) const
{
    return Math::DistanceTo(Math::Vector2f(this->_position.x, this->_position.z), target);
}
