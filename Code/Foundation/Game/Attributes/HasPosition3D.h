// ----------------------------------------------------------------------------------------
//  \file       HasPosition3D.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Math/Vector.h"

namespace Graphics
{
    /// Provides 3D position attributes and operations
    class EXPORT HasPosition3D
    {
    public:
        HasPosition3D();
        virtual ~HasPosition3D() = default;

        explicit HasPosition3D(const Math::Vector3f& position);
        Math::Vector3f GetPosition() const;
        void SetPosition(const Math::Vector3f& position);
        float GetPositionX() const;
        void SetPositionX(float positionX);
        void IncreasePositionX(float relativePositionX);
        float GetPositionY() const;
        void SetPositionY(float positionY);
        void IncreasePositionY(float relativePositionY);
        float GetPositionZ() const;
        void SetPositionZ(float positionZ);
        void IncreasePositionZ(float relativePositionZ);
        void IncreasePosition(const Math::Vector3f& relativePosition);

    protected:
        Math::Vector3f _position;
    };

    inline Math::Vector3f HasPosition3D::GetPosition() const
    {
        return this->_position;
    }

    inline void HasPosition3D::SetPosition(const Math::Vector3f& position)
    {
        this->_position = position;
    }

    inline float HasPosition3D::GetPositionX() const
    {
        return this->_position.x;
    }

    inline void HasPosition3D::SetPositionX(const float positionX)
    {
        this->_position.x = positionX;
    }

    inline void HasPosition3D::IncreasePositionX(const float relativePositionX)
    {
        this->_position.x += relativePositionX;
    }

    inline float HasPosition3D::GetPositionY() const
    {
        return this->_position.y;
    }

    inline void HasPosition3D::SetPositionY(const float positionY)
    {
        this->_position.y = positionY;
    }

    inline void HasPosition3D::IncreasePositionY(const float relativePositionY)
    {
        this->_position.y += relativePositionY;
    }

    inline float HasPosition3D::GetPositionZ() const
    {
        return this->_position.z;
    }

    inline void HasPosition3D::SetPositionZ(const float positionZ)
    {
        this->_position.z = positionZ;
    }

    inline void HasPosition3D::IncreasePositionZ(const float relativePositionZ)
    {
        this->_position.z += relativePositionZ;
    }

    inline void HasPosition3D::IncreasePosition(const Math::Vector3f& relativePosition)
    {
        this->_position += relativePosition;
    }
}
