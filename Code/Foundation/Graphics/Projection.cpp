#include "Projection.h"
#include "../Math/Utils.h"

Graphics::Projection::Projection(float aspectRatio, float fieldOfView, float nearPlane, float farPlane) :
	_aspectRatio(aspectRatio),
	_fieldOfView(fieldOfView),
	_nearPlane(nearPlane),
	_farPlane(farPlane)
{
}

Graphics::Projection::~Projection()
{
}

Math::Matrix4f Graphics::Projection::GetMatrix() const
{
	return Math::ProjectionMatrix(this->_aspectRatio, this->_fieldOfView, this->_nearPlane, this->_farPlane);
}
