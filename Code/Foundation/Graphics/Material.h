#pragma once

#include "Core.h"
#include "../Math/Vector.h"

namespace Graphics
{

    class Material
    {
    public:
        Material(const Math::Vector3f& diffuse, float reflectivity, const Math::Vector3f& specular, const Math::Vector3f& ambient);
        virtual ~Material();
        Math::Vector3f GetAmbient() const;
        void SetAmbient(const Math::Vector3f& ambient);
        Math::Vector3f GetDiffuse() const;
        void SetDiffuse(const Math::Vector3f& diffuse);
        Math::Vector3f GetSpecular() const;
        void SetSpecular(const Math::Vector3f& specular);
        float GetReflectivity() const;
        void SetReflectivity(float reflectivity);

    private:
        Math::Vector3f _ambient;
        Math::Vector3f _diffuse;
        Math::Vector3f _specular;
        float _reflectivity;
    };

    inline Math::Vector3f Graphics::Material::GetAmbient() const
    {
        return this->_ambient;
    }

    inline void Material::SetAmbient(const Math::Vector3f& ambient)
    {
        this->_ambient = ambient;
    }

    inline Math::Vector3f Graphics::Material::GetDiffuse() const
    {
        return this->_diffuse;
    }

    inline void Material::SetDiffuse(const Math::Vector3f& diffuse)
    {
        this->_diffuse = diffuse;
    }

    inline Math::Vector3f Graphics::Material::GetSpecular() const
    {
        return this->_specular;
    }

    inline void Material::SetSpecular(const Math::Vector3f& specular)
    {
        this->_specular = specular;
    }

    inline float Graphics::Material::GetReflectivity() const
    {
        return this->_reflectivity;
    }

    inline void Material::SetReflectivity(float reflectivity)
    {
        this->_reflectivity = reflectivity;
    }

}
