// ----------------------------------------------------------------------------------------
//  \file       HasRotation2D.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Graphics
{
    /// Provides 2D rotation attributes and operations
    class EXPORT HasRotation2D
    {
    public:
        HasRotation2D();
        explicit HasRotation2D(float rotation);
        virtual ~HasRotation2D() = default;

        float GetRotation() const;
        void SetRotation(float rotationX);
        void IncreaseRotation(float relativeRotationX);

    protected:
        float _rotation;
    };

    inline float HasRotation2D::GetRotation() const
    {
        return this->_rotation;
    }

    inline void HasRotation2D::SetRotation(const float rotationX)
    {
        this->_rotation = rotationX;
    }

    inline void HasRotation2D::IncreaseRotation(const float relativeRotationX)
    {
        this->_rotation += relativeRotationX;
    }
}
