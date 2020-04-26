#include "Material.h"

Graphics::Material::Material(const Math::Vector3f& diffuse, float reflectivity, const Math::Vector3f& specular) :
	_diffuse(diffuse),
	_specular(specular),
	_reflectivity(reflectivity)
{
}

Graphics::Material::~Material()
{
}
