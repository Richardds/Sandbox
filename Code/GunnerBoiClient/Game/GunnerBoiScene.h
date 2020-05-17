#pragma once

#include <Game/Scene.h>

#include "Graphics/Renderers/HUDRenderer.h"
#include "Managers/ProjectileManager.h"
#include "Scene/Boi.h"

namespace GunnerBoi
{
	class GunnerBoiScene : public Graphics::Scene
	{
	public:
		enum class State
		{
			Initial,
			Run
		};

		GunnerBoiScene();

		bool Setup() override;
		void ProcessInput() override;
		void Update(float delta) override;
		void Render() override;
		std::shared_ptr<Boi> SetupPlayer(const std::string& resourceName);

	protected:
		void RenderEntities() override;

	private:
		std::shared_ptr<Boi> _player;
		std::shared_ptr<Graphics::HUDRenderer> _hudRenderer;
		std::shared_ptr<ProjectileManager> _projectileManager;

		bool _lockCameraToPlayer;
	};
}
