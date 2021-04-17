// ----------------------------------------------------------------------------------------
//  \file       HasRotation3D.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Game/Attributes/HasRotation3D.h"

Graphics::HasRotation3D::HasRotation3D() :
    _rotation(Math::Vector3f(0.0f, 0.0f, 0.0f))
{
}

Graphics::HasRotation3D::HasRotation3D(const Math::Vector3f& rotation) :
    _rotation(rotation)
{
}
