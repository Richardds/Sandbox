// ----------------------------------------------------------------------------------------
//  \file       HasRotation3D.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Vector.h"

namespace Graphics
{
    /// Provides 3D rotation attributes and operations
    class EXPORT HasRotation3D
    {
    public:
        HasRotation3D();
        HasRotation3D(const Math::Vector3f& rotation);
        virtual ~HasRotation3D() = default;

        Math::Vector3f GetRotation() const;
        void SetRotation(const Math::Vector3f& rotation);
        float GetRotationX() const;
        void SetRotationX(float rotationX);
        void IncreaseRotationX(float relativeRotationX);
        void InvertRotationX();
        float GetRotationY() const;
        void SetRotationY(float rotationY);
        void IncreaseRotationY(float relativeRotationY);
        void InvertRotationY();
        float GetRotationZ() const;
        void SetRotationZ(float rotationZ);
        void IncreaseRotationZ(float relativeRotationZ);
        void InvertRotationZ();
        void IncreaseRotation(const Math::Vector3f& relativeRotation);

    protected:
        Math::Vector3f _rotation;
    };

    inline Math::Vector3f HasRotation3D::GetRotation() const
    {
        return this->_rotation;
    }

    inline void HasRotation3D::SetRotation(const Math::Vector3f& rotation)
    {
        this->_rotation = rotation;
    }

    inline float HasRotation3D::GetRotationX() const
    {
        return this->_rotation.x;
    }

    inline void HasRotation3D::SetRotationX(const float rotationX)
    {
        this->_rotation.x = rotationX;
    }

    inline void HasRotation3D::IncreaseRotationX(const float relativeRotationX)
    {
        this->_rotation.x += relativeRotationX;
    }

    inline void HasRotation3D::InvertRotationX()
    {
        this->_rotation.x = -this->_rotation.x;
    }

    inline float HasRotation3D::GetRotationY() const
    {
        return this->_rotation.y;
    }

    inline void HasRotation3D::SetRotationY(const float rotationY)
    {
        this->_rotation.y = rotationY;
    }

    inline void HasRotation3D::IncreaseRotationY(const float relativeRotationY)
    {
        this->_rotation.y += relativeRotationY;
    }

    inline void HasRotation3D::InvertRotationY()
    {
        this->_rotation.y = -this->_rotation.y;
    }

    inline float HasRotation3D::GetRotationZ() const
    {
        return this->_rotation.z;
    }

    inline void HasRotation3D::SetRotationZ(const float rotationZ)
    {
        this->_rotation.z = rotationZ;
    }

    inline void HasRotation3D::IncreaseRotationZ(const float relativeRotationZ)
    {
        this->_rotation.z += relativeRotationZ;
    }

    inline void HasRotation3D::InvertRotationZ()
    {
        this->_rotation.z = -this->_rotation.z;
    }

    inline void HasRotation3D::IncreaseRotation(const Math::Vector3f& relativeRotation)
    {
        this->_rotation += relativeRotation;
    }
}
