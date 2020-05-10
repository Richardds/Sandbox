#pragma once

#include "../Attributes/HasPosition.h"
#include "../Attributes/HasRotation.h"

namespace Graphics
{

    class Camera : public HasPosition, public HasRotation
    {
    public:
        Camera();
        Camera(float fieldOfView);
        virtual ~Camera();
        float GetFieldOfView() const;
        void SetFieldOfView(float fieldOfView);

    private:
        float _fieldOfView;
    };

    inline float Graphics::Camera::GetFieldOfView() const
    {
        return this->_fieldOfView;
    }

    inline void Camera::SetFieldOfView(float fieldOfView)
    {
        this->_fieldOfView = fieldOfView;
    }

}
