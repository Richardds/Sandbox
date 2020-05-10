#pragma once

#include <vector>
#include <Graphics/Renderers/EntityRenderer.h>

#include "../Scene/Projectile.h"

namespace GunnerBoi
{

    class ProjectileManager
    {
    public:
        ProjectileManager();
        virtual ~ProjectileManager();
        void Update(float delta);
        void RenderWith(std::shared_ptr<Graphics::EntityRenderer> renderer);
        void Manage(std::shared_ptr<Projectile> projectile);

    private:
        std::shared_ptr<Graphics::Model> _projectileModel;
        std::vector<std::shared_ptr<Projectile>> _projectiles;
    };

}
