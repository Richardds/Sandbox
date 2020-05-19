#pragma once

#include "ShaderSystem.h"
#include "../Projection.h"
#include "../../Game/Scene/Camera.h"

namespace Graphics
{
	class SkyboxShader : public ShaderSystem
	{
	public:
		SkyboxShader();
		void InitializeUniformVariables() override;
		void LoadProjection(const std::shared_ptr<const Projection>& projection) const;
		void LoadCamera(const std::shared_ptr<Camera>& camera) const;

	private:
		GLint _projectionLocation;
		GLint _viewLocation;
	};
}
