// ----------------------------------------------------------------------------------------
//  \file       PointLight.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Light/PointLight.h"

Graphics::PointLight::PointLight() :
    _attenuation(1.0f, 0.1f, 0.025f)
{
}
