#include "TargetedCamera.h"
#include "../../Core/Debug.h"
#include "../../Math/Constants.h"
#include "../../Math/Utils.h"

Graphics::TargetedCamera::TargetedCamera(float distance) :
    _distance(distance)
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
    float offset = this->_distance / Math::SQRT_2;
    position.y += offset;
    position.z += offset;

    this->_position = position;
    this->_rotX = -45.0f;
}

void Graphics::TargetedCamera::Update(std::shared_ptr<HasPosition> target)
{
    _assert(target);

    this->LookAt(target->getPosition());
}
