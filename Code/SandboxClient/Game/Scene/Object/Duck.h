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
    class Duck final : public Graphics::Actor
    {
    public:
        Duck(const Math::Vector3f& origin, float rotation);

        Math::Vector3f GetOrigin() const;
        void SetOrigin(const Math::Vector3f& origin);
        float DistanceToOrigin() const;
        bool IsOutOfRange() const;

    private:
        Math::Vector3f _origin;
        float _range;
    };

    inline Math::Vector3f Duck::GetOrigin() const
    {
        return this->_origin;
    }

    inline void Duck::SetOrigin(const Math::Vector3f& origin)
    {
        this->_origin = origin;
    }
}
