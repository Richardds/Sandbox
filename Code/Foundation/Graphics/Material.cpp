#include "Material.h"

Graphics::Material::Material(const Math::Vector3f& diffuse, float reflectivity, const Math::Vector3f& specular, const Math::Vector3f& ambient) :
	_ambient(ambient),
	_diffuse(diffuse),
	_specular(specular),
	_reflectivity(reflectivity)
{
}

Graphics::Material::~Material()
{
}
