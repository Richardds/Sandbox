// ----------------------------------------------------------------------------------------
//  \file       PointLight.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Game/Scene/Light/PointLight.h"

Graphics::PointLight::PointLight() :
    _attenuation(1.0f, 0.1f, 0.025f)
{
}
