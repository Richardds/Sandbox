// ----------------------------------------------------------------------------------------
//  \file       Duck.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Game/Scene/Object/Actor.h>
#include <Math/Vector.h>

namespace Sandbox
{
    /// 3D world actor overrider class used for abstracting a duck
    class Duck : public Graphics::Actor
    {
    public:
        explicit Duck(const std::shared_ptr<Actor>& actor);
        Duck(const Math::Vector3f& origin, float rotation);

        float DistanceToOrigin() const;
        bool OutOfRange() const;

    private:
        Math::Vector3f _origin;
        float _range;
    };
}
