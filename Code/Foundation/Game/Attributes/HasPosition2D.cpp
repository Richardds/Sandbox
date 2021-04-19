// ----------------------------------------------------------------------------------------
//  \file       HasPosition2D.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Game/Attributes/HasPosition2D.h"

Graphics::HasPosition2D::HasPosition2D() :
    _position(0.0f)
{
}

Graphics::HasPosition2D::HasPosition2D(const Math::Vector2f& position) :
    _position(position)
{
}
