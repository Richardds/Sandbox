// ----------------------------------------------------------------------------------------
//  \file       Light.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Light.h"
#include "Math/Utils.h"

Graphics::Light::Light() :
	_intensity(0.8f),
	_color(1.0f, 1.0f, 1.0f)
{
}
