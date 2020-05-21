#pragma once

#include "Renderer.h"
#include "../../Game/Scene/Skybox.h"
#include "../../Game/Scene/Water.h"
#include "../Shaders/SkyboxShader.h"

namespace Graphics
{
	class SkyboxRenderer : public Renderer<SkyboxShader>
	{
	public:
		SkyboxRenderer() = default;
		
		bool Setup(const std::shared_ptr<const Projection>& projection);
		void Begin(const std::shared_ptr<Camera>& camera) const;
		void Render(const std::shared_ptr<Skybox>& skybox) const;

	private:
		std::shared_ptr<Mesh> _skyboxMesh;
	};
}
