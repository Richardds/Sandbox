#include <IO/Console.h>

#include "ProjectileManager.h"

GunnerBoi::ProjectileManager::ProjectileManager()
{
}

GunnerBoi::ProjectileManager::~ProjectileManager()
{
}

void GunnerBoi::ProjectileManager::Update(float delta)
{
	for (std::shared_ptr<Projectile>& projectile : this->_projectiles) {
		// Move
	}
}

void GunnerBoi::ProjectileManager::Render(std::shared_ptr<Graphics::EntityShader> shader)
{
	for (std::shared_ptr<Projectile>& projectile : this->_projectiles) {
		projectile->Render(shader);
	}
}

void GunnerBoi::ProjectileManager::Manage(std::shared_ptr<Projectile> projectile)
{
	IO::Console::Instance().Info("Projectile fired [ %f %f ] >> %f\n",
		projectile->getPositionX(), projectile->getPositionZ(), projectile->getRotationY());

	this->_projectiles.emplace_back(projectile);
}
