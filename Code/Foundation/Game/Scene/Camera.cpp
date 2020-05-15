#include "Camera.h"
#include "../../Math/Utils.h"

Graphics::Camera::Camera() :
    Camera(70.0f)
{
}

Graphics::Camera::Camera(float fieldOfView) :
    _fieldOfView(fieldOfView)
{
}

Graphics::Camera::~Camera()
{
}
