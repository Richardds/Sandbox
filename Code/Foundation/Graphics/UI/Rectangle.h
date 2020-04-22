#pragma once

#include "../Attributes/HasPosition.h"
#include "../../Math/Vector.h"

namespace Graphics
{

    class Rectangle
    {
    public:
        Rectangle(float width, float height, Math::Vector3f color);
        virtual ~Rectangle();
        void Render();
        void SetWidth(float width);
        float GetWidth() const;
        void SetHeight(float height);
        float GetHeight() const;
        void SetColor(Math::Vector3f color);
        Math::Vector3f GetColor() const;

    private:
        float _width;
        float _height;
        Math::Vector3f _color;
    };

    inline void Graphics::Rectangle::SetWidth(float width)
    {
        this->_width = width;
    }

    inline float Rectangle::GetWidth() const
    {
        return this->_width;
    }

    inline void Rectangle::SetHeight(float height)
    {
        this->_height = height;
    }

    inline float Rectangle::GetHeight() const
    {
        return this->_height;
    }

    inline void Rectangle::SetColor(Math::Vector3f color)
    {
        this->_color = color;
    }

    inline Math::Vector3f Rectangle::GetColor() const
    {
        return this->_color;
    }

}
