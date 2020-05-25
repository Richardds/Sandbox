// ----------------------------------------------------------------------------------------
//  \file       Camera.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Camera.h"
#include "Math/Utils.h"

Graphics::Camera::Camera() :
    Camera(70.0f)
{
}

Graphics::Camera::Camera(const float fieldOfView) :
    _fieldOfView(fieldOfView)
{
}

void Graphics::Camera::LookAt(const Math::Vector3f& target)
{
    // TODO
}
