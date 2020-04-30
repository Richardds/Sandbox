#pragma once

#include <Graphics/Scene/Entity.h>
#include <Math/Vector.h>

namespace GunnerBoi
{

    class Projectile : public Graphics::Entity
    {
    public:
        Projectile(Math::Vector3f position, float rotation);
        virtual ~Projectile();

    private:

    };

}
