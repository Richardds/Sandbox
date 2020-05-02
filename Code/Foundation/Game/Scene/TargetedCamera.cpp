#include "TargetedCamera.h"
#include "../../Core/Debug.h"
#include "../../Math/Constants.h"
#include "../../Math/Utils.h"

Graphics::TargetedCamera::TargetedCamera(float distance) :
    _distance(distance),
    _angle(45.0f)
{
    this->LookAt(Math::Vector3f(0.0f, 0.0f, 0.0f));
}

Graphics::TargetedCamera::~TargetedCamera()
{
}

void Graphics::TargetedCamera::IncreaseDistance(float distance)
{
    this->_distance += distance;
}

void Graphics::TargetedCamera::LookAt(Math::Vector3f position)
{
    const float radians = glm::radians(this->_angle);
    position.y += std::sinf(radians) * this->_distance;
    position.z += std::cosf(radians) * this->_distance;

    this->_position = position;
    this->_rotX = -this->_angle;
}

void Graphics::TargetedCamera::Update(std::shared_ptr<HasPosition> target)
{
    _assert(target);

    this->LookAt(target->getPosition());
}
