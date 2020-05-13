#pragma once

#include "Light.h"

namespace Graphics
{

    class DirectionalLight : public Light
    {
    public:
        DirectionalLight();
        virtual ~DirectionalLight();
        Math::Vector3f GetDirection() const;
        void SetDirection(const Math::Vector3f& direction);

    private:
        Math::Vector3f _direction;
    };

    inline Math::Vector3f Graphics::DirectionalLight::GetDirection() const
    {
        return this->_direction;
    }

    inline void Graphics::DirectionalLight::SetDirection(const Math::Vector3f& direction)
    {
        this->_direction = direction;
    }

}
