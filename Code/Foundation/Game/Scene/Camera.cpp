#include "Camera.h"

Graphics::Camera::Camera()
{
}

Graphics::Camera::Camera(Math::Vector3f position, float rotX, float rotY, float rotZ) :
    HasPosition(position),
    HasRotation(rotX, rotY, rotZ)
{
}

Graphics::Camera::~Camera()
{
}
