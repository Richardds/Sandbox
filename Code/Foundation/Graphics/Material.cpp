// ----------------------------------------------------------------------------------------
//  \file       Material.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Material.h"

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
