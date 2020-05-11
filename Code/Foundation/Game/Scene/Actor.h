#pragma once

#include "Entity.h"

namespace Graphics
{

    class Actor : public Entity
    {
    public:
        Actor();
        virtual ~Actor();
        float GetMovingSpeed() const;
        void SetMovingSpeed(float speed);
        void Move(float distance);
        virtual void Update(float delta);
        void LookAt(Math::Vector2f target);
        float DistanceTo(Math::Vector2f target) const;

    private:
        float _movingSpeed;
    };

    inline float Graphics::Actor::GetMovingSpeed() const
    {
        return this->_movingSpeed;
    }

    inline void Graphics::Actor::SetMovingSpeed(float speed)
    {
        this->_movingSpeed = speed;
    }

}
