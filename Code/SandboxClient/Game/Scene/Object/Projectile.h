// ----------------------------------------------------------------------------------------
//  \file       Projectile.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Game/Scene/Object/Actor.h>
#include <Math/Vector.h>

namespace Sandbox
{
    /// 3D world actor overrider class used for abstracting a projectile
    class Projectile final : public Graphics::Actor
    {
    public:
        explicit Projectile(const std::shared_ptr<Actor>& actor);
        Projectile(const Math::Vector3f& origin, float rotation);

        float DistanceToOrigin() const;
        bool IsOutOfRange() const;

    private:
        Math::Vector3f _origin;
        float _range;
    };
}
