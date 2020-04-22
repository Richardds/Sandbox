#pragma once

#include "../Attributes/HasPosition.h"

namespace Graphics
{

    class Light : public HasPosition
    {
    public:
        Light();
        Light(Math::Vector3f position);
        Light(Math::Vector3f position, Math::Vector3f color);
        virtual ~Light();
        Math::Vector3f GetColor() const;
        void SetColor(const Math::Vector3f& color);

    private:
        Math::Vector3f _color;
    };

    inline Math::Vector3f Graphics::Light::GetColor() const
    {
        return this->_color;
    }

}
