// ----------------------------------------------------------------------------------------
//  \file       HasScale.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Attributes/HasScale.h"

Graphics::HasScale::HasScale() :
	_scale(1.0f)
{
}

Graphics::HasScale::HasScale(const float scale) :
	_scale(scale)
{
}

void Graphics::HasScale::IncreaseScale(const float scale)
{
	this->_scale += scale;
}
