// ----------------------------------------------------------------------------------------
//  \file       Light.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Math/Vector.h"

namespace Graphics
{
    /// Base light class
    class EXPORT Light
    {
    public:
        Light();
        virtual ~Light() = default;

        float GetIntensity() const;
        void SetIntensity(float intensity);
        Math::Vector3f GetColor() const;
        void SetColor(const Math::Vector3f& color);

    private:
        float _intensity;
        Math::Vector3f _color;
    };

    inline float Light::GetIntensity() const
    {
        return this->_intensity;
    }

    inline void Light::SetIntensity(const float intensity)
    {
        this->_intensity = intensity;
    }

    inline Math::Vector3f Light::GetColor() const
    {
        return this->_color;
    }

    inline void Light::SetColor(const Math::Vector3f& color)
    {
        this->_color = color;
    }
}
