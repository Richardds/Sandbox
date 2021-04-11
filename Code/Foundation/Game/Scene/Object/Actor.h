// ----------------------------------------------------------------------------------------
//  \file       Actor.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Object/Entity.h"

namespace Graphics
{
    /// 3D scene actor entity
    class EXPORT Actor : public Entity
    {
    public:
        Actor();

        float GetMovingSpeed() const;
        void SetMovingSpeed(float speed);
        float GetTurningSpeed() const;
        void SetTurningSpeed(float speed);
        void Move(float distance);
        virtual void GoForward(float delta);
        virtual void TurnLeft(float delta);
        virtual void TurnRight(float delta);
        void LookAt(const Math::Vector2f& target);
        float LookAtDiff(const Math::Vector2f& target) const;
        float DistanceTo(const Math::Vector2f& target) const;

    protected:
        float _movingSpeed;
        float _turningSpeed;
    };

    inline float Actor::GetMovingSpeed() const
    {
        return this->_movingSpeed;
    }

    inline void Actor::SetMovingSpeed(const float speed)
    {
        this->_movingSpeed = speed;
    }

    inline float Actor::GetTurningSpeed() const
    {
        return this->_turningSpeed;
    }

    inline void Actor::SetTurningSpeed(const float speed)
    {
        this->_turningSpeed = speed;
    }
}
