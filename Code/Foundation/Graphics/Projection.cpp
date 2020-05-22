#include "Precompiled.h"
#include "Graphics/Projection.h"
#include "Math/Utils.h"

Graphics::Projection::Projection(const float aspectRatio, const float fieldOfView, const float nearPlane,
                                 const float farPlane) :
	_aspectRatio(aspectRatio),
	_fieldOfView(fieldOfView),
	_nearPlane(nearPlane),
	_farPlane(farPlane)
{
}

Math::Matrix4f Graphics::Projection::GetMatrix() const
{
	return Math::ProjectionMatrix(this->_aspectRatio, this->_fieldOfView, this->_nearPlane, this->_farPlane);
}
