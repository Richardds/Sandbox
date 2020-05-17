#include "Camera.h"
#include "../../Math/Utils.h"

Graphics::Camera::Camera() :
	Camera(70.0f)
{
}

Graphics::Camera::Camera(const float fieldOfView) :
	_fieldOfView(fieldOfView)
{
}

void Graphics::Camera::LookAt(Math::Vector3f target)
{
	// TODO
}
