// ----------------------------------------------------------------------------------------
//  \file       Projection.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Matrix.h"

namespace Graphics
{
    /// Holds projection information necessary for creating projection matrix
    class Projection
    {
    public:
        Projection(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);
        [[nodiscard]] Math::Matrix4f GetMatrix() const;
        [[nodiscard]] float GetAspectRatio() const;
        void SetAspectRatio(float aspectRatio);
        [[nodiscard]] float GetFieldOfView() const;
        void SetFieldOfView(float fieldOfView);
        [[nodiscard]] float GetNearPlane() const;
        void SetNearPlane(float nearPlane);
        [[nodiscard]] float GetFarPlane() const;
        void SetFarPlane(float farPlane);

    private:
        float _aspectRatio;
        float _fieldOfView;
        float _nearPlane;
        float _farPlane;
    };

    inline float Projection::GetAspectRatio() const
    {
        return this->_aspectRatio;
    }

    inline void Projection::SetAspectRatio(const float aspectRatio)
    {
        this->_aspectRatio = aspectRatio;
    }

    inline float Projection::GetFieldOfView() const
    {
        return this->_fieldOfView;
    }

    inline void Projection::SetFieldOfView(const float fieldOfView)
    {
        this->_fieldOfView = fieldOfView;
    }

    inline float Projection::GetNearPlane() const
    {
        return this->_nearPlane;
    }

    inline void Projection::SetNearPlane(const float nearPlane)
    {
        this->_nearPlane = nearPlane;
    }

    inline float Projection::GetFarPlane() const
    {
        return this->_farPlane;
    }

    inline void Projection::SetFarPlane(const float farPlane)
    {
        this->_farPlane = farPlane;
    }
}
