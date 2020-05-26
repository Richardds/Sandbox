// ----------------------------------------------------------------------------------------
//  \file       Camera.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Camera.h"
#include "Math/Utils.h"

Graphics::Camera::Camera() :
    Camera(70.0f)
{
}

Graphics::Camera::Camera(const float fieldOfView) :
    _fieldOfView(fieldOfView)
{
}

Math::Vector3f Graphics::Camera::GetDirection() const
{
    return Math::Vector3f(
        sin(glm::radians(this->_rotationY)) * cos(glm::radians(this->_rotationX)),
        -sin(glm::radians(this->_rotationX)),
        -cos(glm::radians(this->_rotationY)) * cos(glm::radians(this->_rotationX))
    );
}

void Graphics::Camera::LookAt(const Math::Vector3f& target)
{
    // TODO
}
