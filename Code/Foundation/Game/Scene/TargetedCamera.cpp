// ----------------------------------------------------------------------------------------
//  \file       TargetedCamera.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/TargetedCamera.h"
#include "Math/Utils.h"

Graphics::TargetedCamera::TargetedCamera() :
    _distance(DEFAULT_DISTANCE)
{
    this->SetRotationX(30.0f);
    this->Spectate(Math::Vector3f(0.0f, 0.0f, 0.0f));
}

void Graphics::TargetedCamera::Spectate(const Math::Vector3f& target)
{
    const float radiansX = glm::radians(this->_rotationX);
    const float radiansY = glm::radians(this->_rotationY);

    this->_position.x = target.x - this->_distance * glm::cos(radiansX) * glm::sin(radiansY);
    this->_position.y = target.y + this->_distance * glm::sin(radiansX);
    this->_position.z = target.z + this->_distance * glm::cos(radiansX) * glm::cos(radiansY);
}
