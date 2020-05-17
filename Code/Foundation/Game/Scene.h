#pragma once

#include <string>
#include <unordered_map>

#include "../Graphics/Renderers/EntityRenderer.h"
#include "../Graphics/Renderers/HUDRenderer.h"
#include "../Graphics/Renderers/WaterRenderer.h"
#include "../Timing/Time.h"
#include "Scene/DirectionalLight.h"
#include "Scene/Entity.h"
#include "Scene/PointLight.h"
#include "Scene/TargetedCamera.h"
#include "Scene/Water.h"

namespace Graphics
{
	class Scene
	{
	public:
		enum class State
		{
			Initial,
			Run
		};

		Scene();
		virtual ~Scene() = default;

		[[nodiscard]] State GetState() const;
		virtual bool Setup();
		virtual void ProcessInput();
		virtual void Update(float delta);
		virtual void Render();
		[[nodiscard]] Math::Vector3f GetScreenWorldPosition(const Math::Vector2ui& screenPosition) const;

	protected:
		virtual void RenderScene();
		virtual void RenderEntities();
		std::shared_ptr<Water> AddWater(const std::string& name, float size);
		std::shared_ptr<PointLight> AddLight(const std::string& name);
		std::shared_ptr<Entity> AddEntity(const std::string& name, const std::string& resourceName);

		std::shared_ptr<TargetedCamera> _camera;
		std::shared_ptr<EntityRenderer> _entityRenderer;
		std::shared_ptr<WaterRenderer> _waterRenderer;
		std::shared_ptr<HUDRenderer> _hudRenderer;
		std::shared_ptr<DirectionalLight> _sun;
		std::unordered_map<std::string, std::shared_ptr<Water>> _waterTiles;
		std::unordered_map<std::string, std::shared_ptr<PointLight>> _lights;
		std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;

	private:
		State _state;
	};
}
