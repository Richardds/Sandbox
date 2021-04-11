// ----------------------------------------------------------------------------------------
//  \file       HasRotation2D.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Game/Attributes/HasRotation2D.h"

Graphics::HasRotation2D::HasRotation2D() :
    HasRotation2D(0.0f)
{
}

Graphics::HasRotation2D::HasRotation2D(const float rotation) :
    _rotation(rotation)
{
}
