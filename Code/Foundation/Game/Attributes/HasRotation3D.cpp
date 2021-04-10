// ----------------------------------------------------------------------------------------
//  \file       HasRotation3D.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Attributes/HasRotation3D.h"

Graphics::HasRotation3D::HasRotation3D() :
    HasRotation3D(0.0f, 0.0f, 0.0f)
{
}

Graphics::HasRotation3D::HasRotation3D(const float rotationX, const float rotationY, const float rotationZ) :
    _rotationX(rotationX),
    _rotationY(rotationY),
    _rotationZ(rotationZ)
{
}
