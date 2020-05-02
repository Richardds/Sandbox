#pragma once

#include "../Attributes/HasPosition.h"
#include "../Attributes/HasRotation.h"

namespace Graphics
{

    class Camera : public HasPosition, public HasRotation
    {
    public:
        Camera();
        Camera(Math::Vector3f position, float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f);
        virtual ~Camera();
    };

}
