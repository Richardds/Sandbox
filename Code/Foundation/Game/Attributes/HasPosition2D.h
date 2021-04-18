// ----------------------------------------------------------------------------------------
//  \file       HasPosition2D.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Vector.h"

namespace Graphics
{
    /// Provides 2D position attributes and operations
    class EXPORT HasPosition2D
    {
    public:
        HasPosition2D();
        virtual ~HasPosition2D() = default;

        explicit HasPosition2D(const Math::Vector2f& position);
        Math::Vector2f GetPosition() const;
        void SetPosition(const Math::Vector2f& position);
        float GetPositionX() const;
        void SetPositionX(float positionX);
        void IncreasePositionX(float relativePositionX);
        float GetPositionY() const;
        void SetPositionY(float positionY);
        void IncreasePositionY(float relativePositionY);

    protected:
        Math::Vector2f _position;
    };

    inline Math::Vector2f HasPosition2D::GetPosition() const
    {
        return this->_position;
    }

    inline void HasPosition2D::SetPosition(const Math::Vector2f& position)
    {
        this->_position = position;
    }

    inline float HasPosition2D::GetPositionX() const
    {
        return this->_position.x;
    }

    inline void HasPosition2D::SetPositionX(const float positionX)
    {
        this->_position.x = positionX;
    }

    inline void HasPosition2D::IncreasePositionX(const float relativePositionX)
    {
        this->_position.x += relativePositionX;
    }

    inline float HasPosition2D::GetPositionY() const
    {
        return this->_position.y;
    }

    inline void HasPosition2D::SetPositionY(const float positionY)
    {
        this->_position.y = positionY;
    }

    inline void HasPosition2D::IncreasePositionY(const float relativePositionY)
    {
        this->_position.y += relativePositionY;
    }
}
