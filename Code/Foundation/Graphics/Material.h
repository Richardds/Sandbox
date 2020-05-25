// ----------------------------------------------------------------------------------------
//  \file       Material.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Core.h"
#include "Math/Vector.h"

namespace Graphics
{
    /// Surface material class used as model shading attribute
    class Material
    {
    public:
        Material(const Math::Vector3f& color,
                 float reflectivity,
                 float specular,
                 float shininess);
        [[nodiscard]] Math::Vector3f GetColor() const;
        void SetColor(const Math::Vector3f& color);
        [[nodiscard]] float GetReflectivity() const;
        void SetReflectivity(float reflectivity);
        [[nodiscard]] float GetSpecular() const;
        void SetSpecular(float specular);
        [[nodiscard]] float GetShininess() const;
        void SetShininess(float shininess);

    private:
        Math::Vector3f _color;
        float _reflectivity;
        float _specular;
        float _shininess;
    };

    inline Math::Vector3f Material::GetColor() const
    {
        return this->_color;
    }

    inline void Material::SetColor(const Math::Vector3f& color)
    {
        this->_color = color;
    }

    inline float Material::GetReflectivity() const
    {
        return this->_reflectivity;
    }

    inline void Material::SetReflectivity(const float reflectivity)
    {
        this->_reflectivity = reflectivity;
    }

    inline float Material::GetSpecular() const
    {
        return this->_specular;
    }

    inline void Material::SetSpecular(const float specular)
    {
        this->_specular = specular;
    }

    inline float Material::GetShininess() const
    {
        return this->_shininess;
    }

    inline void Material::SetShininess(const float shininess)
    {
        this->_shininess = shininess;
    }
}
