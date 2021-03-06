// ----------------------------------------------------------------------------------------
//  \file       Projection.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Math/Matrix.h"

namespace Graphics
{
    /// Holds projection information necessary for creating projection matrix
    class EXPORT Projection
    {
    public:
        Projection(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);
        virtual ~Projection() = default;

        Math::Matrix4f GetMatrix() const;
        float GetAspectRatio() const;
        void SetAspectRatio(float aspectRatio);
        float GetFieldOfView() const;
        void SetFieldOfView(float fieldOfView);
        float GetNearPlane() const;
        void SetNearPlane(float nearPlane);
        float GetFarPlane() const;
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
