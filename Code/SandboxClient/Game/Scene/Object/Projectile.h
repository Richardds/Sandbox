// ----------------------------------------------------------------------------------------
//  \file       Projectile.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Precompiled.h>
#include <Game/Scene/Object/Actor.h>
#include <Math/Vector.h>

namespace Sandbox
{
    /// 3D world actor overrider class used for abstracting a projectile
    class Projectile : public Graphics::Actor
    {
    public:
        explicit Projectile(const std::shared_ptr<Actor>& actor);
        Projectile(const Math::Vector3f& position, float rotation);

        float DistanceToOrigin() const;
        bool OutOfRange() const;

    private:
        Math::Vector3f _origin;
        float _range;
    };
}
