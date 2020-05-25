#pragma once

#include <Precompiled.h>
#include <Game/Scene.h>

#include "Managers/ProjectileManager.h"
#include "Scene/Player.h"

namespace Sandbox
{
	/// 3D scene overrider of base scene class
	class SandboxScene : public Graphics::Scene
	{
	public:
		enum class State
		{
			Initial,
			Run
		};

		static constexpr float SUN_LOWER_LIMIT = 0.125f;

		SandboxScene();

		bool Setup() override;
		void ProcessCameraInput();
		void ProcessPlayerInput();
		void ProcessInput() override;
		void Update(float delta) override;
		void Render() override;
		std::shared_ptr<Player> SetupPlayer(const std::string& resourceName);

	protected:
		void RenderEntities() override;

	private:
		std::shared_ptr<Player> _player;
		std::shared_ptr<ProjectileManager> _projectileManager;

		bool _lockCameraToPlayer;
		float _deformationFactor;
	};
}
