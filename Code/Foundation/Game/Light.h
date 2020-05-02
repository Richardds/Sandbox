#pragma once

#include "../Game/Attributes/HasPosition.h"

namespace Graphics
{

    class Light : public HasPosition
    {
    public:
        Light();
        Light(Math::Vector3f position);
        Light(Math::Vector3f position, Math::Vector3f color);
        Light(Math::Vector3f position, Math::Vector3f color, Math::Vector3f attenuation);
        virtual ~Light();
        Math::Vector3f GetColor() const;
        void SetColor(const Math::Vector3f& color);
        Math::Vector3f GetAttenuation() const;
        void SetAttenuation(const Math::Vector3f& attenuation);

    private:
        Math::Vector3f _color;
        Math::Vector3f _attenuation;
    };

    inline Math::Vector3f Graphics::Light::GetColor() const
    {
        return this->_color;
    }

    inline void Graphics::Light::SetColor(const Math::Vector3f& color)
    {
        this->_color = color;
    }

    inline Math::Vector3f Graphics::Light::GetAttenuation() const
    {
        return this->_attenuation;
    }

    inline void Light::SetAttenuation(const Math::Vector3f& attenuation)
    {
        this->_attenuation = attenuation;
    }

}
