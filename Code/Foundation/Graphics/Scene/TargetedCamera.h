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
        void SetDistance(float distance);
        float GetDistance() const;
        void IncreaseDistance(float distance);
        void LookAt(Math::Vector3f position);
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

}
