// ----------------------------------------------------------------------------------------
//  \file       ProjectileManager.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "ProjectileManager.h"

Sandbox::ProjectileManager::ProjectileManager(const std::shared_ptr<Graphics::Model>& projectileModel) :
    _projectileModel(projectileModel)
{
}

void Sandbox::ProjectileManager::Update(const float delta)
{
    auto it = this->_projectiles.begin();

    while (it != this->_projectiles.end())
    {
        const auto& projectile = (*it);

        projectile->GoForward(delta);

        if (projectile->OutOfRange())
        {
            it = this->_projectiles.erase(it);
        }
        else
        {
            // TODO: Handle collision

            ++it;
        }
    }
}

void Sandbox::ProjectileManager::RenderWith(const std::shared_ptr<Graphics::EntityRenderer>& renderer)
{
    for (std::shared_ptr<Projectile>& projectile : this->_projectiles)
    {
        renderer->Render(projectile);
    }
}

void Sandbox::ProjectileManager::Manage(const std::shared_ptr<Projectile>& projectile)
{
    projectile->SetModel(this->_projectileModel);
    this->_projectiles.emplace_back(projectile);
}
