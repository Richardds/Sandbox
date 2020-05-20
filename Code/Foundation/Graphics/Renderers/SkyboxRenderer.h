#pragma once

#include "../../Game/Scene/DirectionalLight.h"
#include "../../Game/Scene/Skybox.h"
#include "../../Game/Scene/Water.h"
#include "../Shaders/SkyboxShader.h"

namespace Graphics
{
	class SkyboxRenderer
	{
	public:
		enum class State
		{
			Initial,
			Ready
		};

		SkyboxRenderer();
		bool Setup(const std::shared_ptr<const Projection>& projection);
		void Begin(const std::shared_ptr<Camera>& camera) const;
		void Render(const std::shared_ptr<Skybox>& skybox) const;

	private:
		State _state;
		std::shared_ptr<SkyboxShader> _shader;
		std::shared_ptr<Mesh> _skyboxMesh;
	};
}
