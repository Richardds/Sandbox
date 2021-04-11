// ----------------------------------------------------------------------------------------
//  \file       Camera.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Attributes/HasPosition3D.h"
#include "Game/Attributes/HasRotation3D.h"

namespace Graphics
{
    /// 3D scene camera entity
    class EXPORT Camera : public HasPosition3D, public HasRotation3D
    {
    public:
        Camera();

        explicit Camera(float fieldOfView);
        float GetFieldOfView() const;
        void SetFieldOfView(float fieldOfView);
        Math::Vector3f GetDirection() const;
        void LookAt(const Math::Vector3f& target);

    private:
        float _fieldOfView;
    };

    inline float Camera::GetFieldOfView() const
    {
        return this->_fieldOfView;
    }

    inline void Camera::SetFieldOfView(const float fieldOfView)
    {
        this->_fieldOfView = fieldOfView;
    }
}
