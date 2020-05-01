#pragma once

#include <Graphics/Scene/Actor.h>
#include <Graphics/Model.h>
#include <Math/Vector.h>
#include <Timing/Time.h>

#include "../Scene/Projectile.h"

namespace GunnerBoi
{

    class Boi : public Graphics::Actor
    {
    public:
        enum class State {
            IDLE,
            RUNNING,
            FOLLOWING
        };

        Boi(Math::Vector3f position);
        virtual ~Boi();
        State GetState() const;
        Math::Vector2f GetTarget() const;
        void SetTarget(Math::Vector2f target);
        void Follow();
        void Idle();
        bool CountdownReady() const;
        std::shared_ptr<Projectile> Fire();
        void Update(float delta);

    private:
        State _state;
        Math::Vector2f _target;
        float _attackSpeed;
        float _countdown;
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

}
