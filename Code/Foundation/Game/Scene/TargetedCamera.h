// ----------------------------------------------------------------------------------------
//  \file       TargetedCamera.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Camera.h"

namespace Graphics
{
    /// 3D scene targeted camera entity
    /// This camera type usually focus on specified 3D position
    class TargetedCamera : public Camera
    {
    public:
        /// Camera distance from target when unspecified
        static constexpr float DEFAULT_DISTANCE = 15.0f;

        TargetedCamera();

        [[nodiscard]] float GetDistance() const;
        void SetDistance(float distance);
        void IncreaseDistance(float distance);
        void Spectate(const Math::Vector3f& target);

    private:
        float _distance;
    };

    inline float TargetedCamera::GetDistance() const
    {
        return this->_distance;
    }

    inline void TargetedCamera::SetDistance(const float distance)
    {
        this->_distance = distance;
    }

    inline void TargetedCamera::IncreaseDistance(const float distance)
    {
        this->_distance += distance;
    }
}
