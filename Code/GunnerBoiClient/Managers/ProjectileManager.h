#pragma once

#include <vector>
#include <Graphics/Shaders/EntityShader.h>

#include "../Game/Scene/Projectile.h"

namespace GunnerBoi
{

    class ProjectileManager
    {
    public:
        ProjectileManager();
        virtual ~ProjectileManager();
        void Update(float delta);
        void Render(std::shared_ptr<Graphics::EntityShader> shader);
        void Manage(std::shared_ptr<Projectile> projectile);

    private:
        std::vector<std::shared_ptr<Projectile>> _projectiles;
    };

}
