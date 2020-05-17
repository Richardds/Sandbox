#include "TargetedCamera.h"
#include "../../Math/Utils.h"

Graphics::TargetedCamera::TargetedCamera(const float distance) :
	_distance(distance)
{
	this->SetRotationX(45.0f);
	this->Spectate(Math::Vector3f(0.0f, 0.0f, 0.0f));
}

void Graphics::TargetedCamera::Spectate(const Math::Vector3f& target)
{
	const float radiansX = glm::radians(this->_rotationX);
	const float radiansY = glm::radians(this->_rotationY);

	const float offsetX = std::sinf(radiansY) * this->_distance;
	const float offsetY = std::sinf(radiansX) * this->_distance;
	const float offsetZ = std::cosf(radiansX) * this->_distance;

	this->_position.x = target.x - offsetX;
	this->_position.y = target.y + offsetY;
	this->_position.z = target.z + offsetZ;
}
