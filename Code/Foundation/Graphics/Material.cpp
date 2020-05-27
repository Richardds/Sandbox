// ----------------------------------------------------------------------------------------
//  \file       Material.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Material.h"

Graphics::Material::Material(const float reflectivity) :
    Graphics::Material(Math::Vector3f(1.0f), reflectivity, 1.0f, 25.0f)
{
}

Graphics::Material::Material(const Math::Vector3f& color,
                             const float reflectivity,
                             const float specular,
                             const float shininess) :
    _color(color),
    _reflectivity(reflectivity),
    _specular(specular),
    _shininess(shininess)
{
}
