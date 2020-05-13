#pragma once

#include "Core.h"
#include "../Math/Vector.h"

namespace Graphics
{

    class Material
    {
    public:
        Material(const Math::Vector3f& color, float specular, float reflectivity);
        virtual ~Material();
        Math::Vector3f GetColor() const;
        void SetColor(const Math::Vector3f& color);
        float GetSpecular() const;
        void SetSpecular(float specular);
        float GetReflectivity() const;
        void SetReflectivity(float reflectivity);

    private:
        Math::Vector3f _color;
        float _specular;
        float _reflectivity;
    };

    inline Math::Vector3f Graphics::Material::GetColor() const
    {
        return this->_color;
    }

    inline void Material::SetColor(const Math::Vector3f& color)
    {
        this->_color = color;
    }

    inline float Graphics::Material::GetSpecular() const
    {
        return this->_specular;
    }

    inline void Material::SetSpecular(float specular)
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
