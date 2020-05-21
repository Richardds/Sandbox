#pragma once

#include "Renderer.h"
#include "../Projection.h"
#include "../../Game/Scene/DirectionalLight.h"
#include "../../Game/Scene/Entity.h"
#include "../../Game/Scene/PointLight.h"
#include "../Shaders/EntityShader.h"

namespace Graphics
{
	class EntityRenderer : public Renderer<EntityShader>
	{
	public:
		EntityRenderer() = default;

		bool Setup(const std::shared_ptr<const Projection>& projection);
		void Begin(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DirectionalLight>& sun,
			const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights) const;
		void Render(const std::shared_ptr<Entity>& entity) const;
	};
}
