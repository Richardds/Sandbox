#pragma once

#include "Camera.h"
#include "Entity.h"

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
        void Update(std::shared_ptr<Entity> target);

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
