#pragma once

#include <vector>
#include <Graphics/Renderers/EntityRenderer.h>

#include "../Scene/Projectile.h"

namespace Sandbox
{
	class ProjectileManager
	{
	public:
		ProjectileManager();

		void Update(float delta);
		void RenderWith(const std::shared_ptr<Graphics::EntityRenderer>& renderer);
		void Manage(const std::shared_ptr<Projectile>& projectile);

	private:
		std::shared_ptr<Graphics::Model> _projectileModel;
		std::vector<std::shared_ptr<Projectile>> _projectiles;
	};
}
