// ----------------------------------------------------------------------------------------
//  \file       ProjectileManager.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Graphics/Renderers/EntityRenderer.h>

#include "Game/Scene/Object/Projectile.h"

namespace Sandbox
{
    /// Projectile manager class for managing 3D world projectiles
    class ProjectileManager
    {
    public:
        ProjectileManager(const std::shared_ptr<Graphics::Model>& projectileModel);

        void Update(float delta);
        void RenderWith(const std::shared_ptr<Graphics::EntityRenderer>& renderer);
        void Manage(const std::shared_ptr<Projectile>& projectile);

    private:
        std::shared_ptr<Graphics::Model> _projectileModel;
        std::list<std::shared_ptr<Projectile>> _projectiles;
    };
}
