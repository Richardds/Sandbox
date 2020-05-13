#include "Material.h"

Graphics::Material::Material(const Math::Vector3f& color, float specular, float reflectivity) :
	_color(color),
	_specular(specular),
	_reflectivity(reflectivity)
{
}

Graphics::Material::~Material()
{
}
