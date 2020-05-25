// ----------------------------------------------------------------------------------------
//  \file       HasPosition.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Attributes/HasPosition.h"

Graphics::HasPosition::HasPosition() :
    _position()
{
}

Graphics::HasPosition::HasPosition(const Math::Vector3f& position) :
    _position(position)
{
}
