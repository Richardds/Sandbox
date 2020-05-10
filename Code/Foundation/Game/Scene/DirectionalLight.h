#pragma once

#include "../../Math/Vector.h"

namespace Graphics
{

    class DirectionalLight
    {
    public:
        DirectionalLight();
        virtual ~DirectionalLight();
        Math::Vector3f GetDirection() const;
        void SetDirection(const Math::Vector3f& direction);
        Math::Vector3f GetColor() const;
        void SetColor(const Math::Vector3f& color);

    private:
        Math::Vector3f _direction;
        Math::Vector3f _color;
    };

    inline Math::Vector3f Graphics::DirectionalLight::GetDirection() const
    {
        return this->_direction;
    }

    inline void Graphics::DirectionalLight::SetDirection(const Math::Vector3f& direction)
    {
        this->_direction = direction;
    }

    inline Math::Vector3f Graphics::DirectionalLight::GetColor() const
    {
        return this->_color;
    }

    inline void Graphics::DirectionalLight::SetColor(const Math::Vector3f& color)
    {
        this->_color = color;
    }

}
