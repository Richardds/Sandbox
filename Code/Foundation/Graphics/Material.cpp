// ----------------------------------------------------------------------------------------
//  \file       Material.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Material.h"

Graphics::Material::Material(const Math::Vector3f& color, const float specular, const float reflectivity) :
	_color(color),
	_specular(specular),
	_reflectivity(reflectivity)
{
}
