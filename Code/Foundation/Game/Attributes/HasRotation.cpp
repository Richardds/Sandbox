// ----------------------------------------------------------------------------------------
//  \file       HasRotation.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Attributes/HasRotation.h"

Graphics::HasRotation::HasRotation() :
	HasRotation(0.0f, 0.0f, 0.0f)
{
}

Graphics::HasRotation::HasRotation(const float rotationX, const float rotationY, const float rotationZ) :
	_rotationX(rotationX),
	_rotationY(rotationY),
	_rotationZ(rotationZ)
{
}
