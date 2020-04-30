#pragma once

#include "Entity.h"

namespace Graphics
{

    class Player : public Entity
    {
    public:
        Player();
        Player(Math::Vector3f position);
        virtual ~Player();
        void Move(float distance);
        void LookAt(Math::Vector2f target);
    };

}
