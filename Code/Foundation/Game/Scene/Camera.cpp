// ----------------------------------------------------------------------------------------
//  \file       Camera.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Game/Scene/Camera.h"
#include "Math/MathUtils.h"
#include "Math/Quaternion.h"

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
        sin(glm::radians(this->_rotation.y)) * cos(glm::radians(this->_rotation.x)),
        -sin(glm::radians(this->_rotation.x)),
        -cos(glm::radians(this->_rotation.y)) * cos(glm::radians(this->_rotation.x))
    );
}

void Graphics::Camera::LookAt(const Math::Vector3f& target)
{
    const Math::Vector3f direction = normalize(target - this->_position);
    const Math::Quaternion q = quatLookAt(direction, Math::Vector3f(0.0f, 1.0f, 0.0f));
    this->_rotation = -degrees(glm::eulerAngles(q));
}
