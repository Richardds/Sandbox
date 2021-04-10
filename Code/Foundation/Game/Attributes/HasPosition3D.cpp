// ----------------------------------------------------------------------------------------
//  \file       HasPosition3D.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Attributes/HasPosition3D.h"

Graphics::HasPosition3D::HasPosition3D() :
    _position(0.0f)
{
}

Graphics::HasPosition3D::HasPosition3D(const Math::Vector3f& position) :
    _position(position)
{
}
