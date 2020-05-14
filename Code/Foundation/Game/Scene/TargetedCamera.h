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
        void IncreaseDistance(float distance);
        void LookAt(Math::Vector3f target);
        void Update(std::shared_ptr<HasPosition> target);

    private:
        float _distance;
    };

    inline float Graphics::TargetedCamera::GetDistance() const
    {
        return this->_distance;
    }

    inline void Graphics::TargetedCamera::SetDistance(float distance)
    {
        this->_distance = distance;
    }

    inline void Graphics::TargetedCamera::IncreaseDistance(float distance)
    {
        this->_distance += distance;
    }

}
