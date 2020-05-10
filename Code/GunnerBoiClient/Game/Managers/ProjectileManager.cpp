#include <IO/Console.h>

#include "ProjectileManager.h"
#include <Util/ResourcesLoader.h>

GunnerBoi::ProjectileManager::ProjectileManager()
{
	this->_projectileModel = Util::ResourcesLoader::Instance().LoadModel("projectile");
}

GunnerBoi::ProjectileManager::~ProjectileManager()
{
}

void GunnerBoi::ProjectileManager::Update(float delta)
{
	auto it = this->_projectiles.begin();

	while (it != this->_projectiles.end()) {
		(*it)->Update(delta);

		if ((*it)->OutOfRange()) {
			it = this->_projectiles.erase(it);
		}
		else {
			// TODO: Handle collision

			++it;
		}
	}
}

void GunnerBoi::ProjectileManager::RenderWith(std::shared_ptr<Graphics::EntityRenderer> renderer)
{
	for (std::shared_ptr<Projectile>& projectile : this->_projectiles) {
		renderer->Render(projectile);
	}
}

void GunnerBoi::ProjectileManager::Manage(std::shared_ptr<Projectile> projectile)
{
	projectile->SetModel(this->_projectileModel);
	this->_projectiles.emplace_back(projectile);

	IO::Console::Instance().Info("Projectile fired: [ %f %f ] >> %f\n",
		projectile->getPositionX(), projectile->getPositionZ(), projectile->getRotationY());
}
