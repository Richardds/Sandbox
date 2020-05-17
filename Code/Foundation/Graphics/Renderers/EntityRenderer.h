#pragma once

#include "../Projection.h"
#include "../../Game/Scene/DirectionalLight.h"
#include "../../Game/Scene/Entity.h"
#include "../../Game/Scene/PointLight.h"
#include "../Shaders/EntityShader.h"

namespace Graphics
{
	class EntityRenderer
	{
	public:
		enum class State
		{
			Initial,
			Ready
		};

		EntityRenderer();
		virtual ~EntityRenderer();
		[[nodiscard]] std::shared_ptr<EntityShader> GetShader() const;
		bool Setup(const std::shared_ptr<const Projection>& projection);
		void Begin(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DirectionalLight>& sun,
		           const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights) const;
		void Render(const std::shared_ptr<Entity>& entity) const;

	private:
		State _state;
		std::shared_ptr<EntityShader> _shader;
	};

	inline std::shared_ptr<EntityShader> EntityRenderer::GetShader() const
	{
		return this->_shader;
	}
}
