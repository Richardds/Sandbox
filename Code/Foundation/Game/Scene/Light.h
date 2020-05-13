#pragma once

#include "../../Math/Vector.h"

namespace Graphics
{

    class Light
    {
    public:
        Light();
        virtual ~Light();
        float GetIntensity() const;
        void SetInstensity(float intensity);
        Math::Vector3f GetColor() const;
        void SetColor(const Math::Vector3f& color);

    private:
        float _intensity;
        Math::Vector3f _color;
    };

    inline float Graphics::Light::GetIntensity() const
    {
        return this->_intensity;
    }

    inline void Light::SetInstensity(float intensity)
    {
        this->_intensity = intensity;
    }

    inline Math::Vector3f Graphics::Light::GetColor() const
    {
        return this->_color;
    }

    inline void Graphics::Light::SetColor(const Math::Vector3f& color)
    {
        this->_color = color;
    }

}
