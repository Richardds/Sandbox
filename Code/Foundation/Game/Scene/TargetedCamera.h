#pragma once

#include <memory>

#include "Camera.h"
#include "../Attributes/HasPosition.h"

namespace Graphics
{

    class TargetedCamera : public Camera
    {
    public:
        TargetedCamera(float distance);
        virtual ~TargetedCamera();
        float GetDistance() const;
        void SetDistance(float distance);
        float GetAngle() const;
        void SetAngle(float angle);
        void IncreaseAngle(float relativeAngle);
        void IncreaseDistance(float distance);
        void LookAt(Math::Vector3f position);
        void Update(std::shared_ptr<HasPosition> target);

    private:
        float _distance;
        float _angle;
    };

    inline float Graphics::TargetedCamera::GetDistance() const
    {
        return this->_distance;
    }

    inline void Graphics::TargetedCamera::SetDistance(float distance)
    {
        this->_distance = distance;
    }

    inline float TargetedCamera::GetAngle() const
    {
        return this->_angle;
    }

    inline void TargetedCamera::SetAngle(float angle)
    {
        this->_angle = angle;
    }

    inline void TargetedCamera::IncreaseAngle(float relativeAngle)
    {
        this->_angle += relativeAngle;
    }

}
