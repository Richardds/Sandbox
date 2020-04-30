#pragma once

#include <Graphics/Scene/Player.h>
#include <Graphics/Model.h>
#include <Math/Vector.h>
#include <Timing/Time.h>

#include "../Scene/Projectile.h"

namespace GunnerBoi
{

    class Boi : public Graphics::Player
    {
    public:
        enum class State {
            IDLE,
            RUNNING,
            FOLLOWING
        };

        Boi();
        Boi(Math::Vector3f position);
        virtual ~Boi();
        State GetState() const;
        Math::Vector2f GetTarget() const;
        void SetTarget(Math::Vector2f target);
        void Follow();
        void Idle();
        std::shared_ptr<Projectile> Fire() const;
        float GetMovingSpeed() const;
        void SetMovingSpeed(float speed);
        float DistanceTo(Math::Vector2f target);
        void Update(float delta);

    private:
        State _state;
        Math::Vector2f _target;
        float _movingSpeed;
    };

    inline Boi::State GunnerBoi::Boi::GetState() const
    {
        return this->_state;
    }


    inline Math::Vector2f GunnerBoi::Boi::GetTarget() const
    {
        return this->_target;
    }

    inline void GunnerBoi::Boi::SetTarget(Math::Vector2f target)
    {
        this->_target = target;
    }

    inline void Boi::Follow()
    {
        this->_state = State::FOLLOWING;
    }

    inline void Boi::Idle()
    {
        this->_state = State::IDLE;
    }

    inline float GunnerBoi::Boi::GetMovingSpeed() const
    {
        return this->_movingSpeed;
    }

    inline void GunnerBoi::Boi::SetMovingSpeed(float speed)
    {
        this->_movingSpeed = speed;
    }

}
