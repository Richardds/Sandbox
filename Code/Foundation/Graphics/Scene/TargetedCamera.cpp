#include "TargetedCamera.h"
#include "../../Core/Debug.h"
#include "../../Math/Constants.h"
#include "../../Math/Utils.h"

Graphics::TargetedCamera::TargetedCamera(float distance) :
    _distance(distance)
{
}

Graphics::TargetedCamera::~TargetedCamera()
{
}

void Graphics::TargetedCamera::IncreaseDistance(float distance)
{
    this->_distance += distance;
}

void Graphics::TargetedCamera::Update(std::shared_ptr<Entity> target)
{
    _assert(target);

    float offset = this->_distance / Math::SQRT_2;

    Math::Vector3f position = target->getPosition();
    position.y += offset;
    position.z += offset;

    this->_position = position;
    this->_rotX = -45.0f;
}
