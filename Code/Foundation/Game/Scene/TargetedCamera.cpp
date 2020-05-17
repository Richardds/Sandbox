#include "TargetedCamera.h"
#include "../../Math/Utils.h"

Graphics::TargetedCamera::TargetedCamera(float distance) :
    _distance(distance)
{
    this->setRotationX(45.0f);
    this->Spectate(Math::Vector3f(0.0f, 0.0f, 0.0f));
}

Graphics::TargetedCamera::~TargetedCamera()
{
}

void Graphics::TargetedCamera::Spectate(Math::Vector3f target)
{
    const float radiansX = glm::radians(this->_rotX);
    const float radiansY = glm::radians(this->_rotY);
    
    float offsetX = std::sinf(radiansY) * this->_distance;
    float offsetY = std::sinf(radiansX) * this->_distance;
    float offsetZ = std::cosf(radiansX) * this->_distance;
    
    this->_position.x = target.x - offsetX;
    this->_position.y = target.y + offsetY;
    this->_position.z = target.z + offsetZ;
}
