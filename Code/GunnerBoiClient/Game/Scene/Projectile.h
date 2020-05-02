#pragma once

#include <Game/Scene/Actor.h>
#include <Math/Vector.h>

namespace GunnerBoi
{

    class Projectile : public Graphics::Actor
    {
    public:
        Projectile(std::shared_ptr<Actor> actor);
        Projectile(Math::Vector3f position, float rotation);
        virtual ~Projectile();
        float DistanceToOrigin() const;
        bool OutOfRange() const;

    private:
        Math::Vector3f _origin;
        float _range;
    };

}
