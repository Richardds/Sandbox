// ----------------------------------------------------------------------------------------
//  \file       HasRotation3D.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Graphics
{
    /// Provides 3D rotation attributes and operations
    class EXPORT HasRotation3D
    {
    public:
        HasRotation3D();
        HasRotation3D(float rotationX, float rotationY, float rotationZ);
        virtual ~HasRotation3D() = default;

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
        void IncreaseRotation(float rotationX, float rotationY, float rotationZ);

    protected:
        float _rotationX;
        float _rotationY;
        float _rotationZ;
    };

    inline float HasRotation3D::GetRotationX() const
    {
        return this->_rotationX;
    }

    inline void HasRotation3D::SetRotationX(const float rotationX)
    {
        this->_rotationX = rotationX;
    }

    inline void HasRotation3D::IncreaseRotationX(const float relativeRotationX)
    {
        this->_rotationX += relativeRotationX;
    }

    inline void HasRotation3D::InvertRotationX()
    {
        this->_rotationX = -this->_rotationX;
    }

    inline float HasRotation3D::GetRotationY() const
    {
        return this->_rotationY;
    }

    inline void HasRotation3D::SetRotationY(const float rotationY)
    {
        this->_rotationY = rotationY;
    }

    inline void HasRotation3D::IncreaseRotationY(const float relativeRotationY)
    {
        this->_rotationY += relativeRotationY;
    }

    inline void HasRotation3D::InvertRotationY()
    {
        this->_rotationY = -this->_rotationY;
    }

    inline float HasRotation3D::GetRotationZ() const
    {
        return this->_rotationZ;
    }

    inline void HasRotation3D::SetRotationZ(const float rotationZ)
    {
        this->_rotationZ = rotationZ;
    }

    inline void HasRotation3D::IncreaseRotationZ(const float relativeRotationZ)
    {
        this->_rotationZ += relativeRotationZ;
    }

    inline void HasRotation3D::InvertRotationZ()
    {
        this->_rotationZ = -this->_rotationZ;
    }

    inline void HasRotation3D::IncreaseRotation(const float rotationX, const float rotationY, const float rotationZ)
    {
        this->_rotationX += rotationX;
        this->_rotationY += rotationY;
        this->_rotationZ += rotationZ;
    }
}
