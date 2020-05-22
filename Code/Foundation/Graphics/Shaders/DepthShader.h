#pragma once

#include "Precompiled.h"
#include "Graphics/Shaders/ShaderSystem.h"

namespace Graphics
{
	class DepthShader : public ShaderSystem
	{
	public:
		DepthShader();
		void InitializeUniformVariables() override;
		void LoadProjection(const Math::Matrix4f& transformation) const;

	private:
		GLint _projectionPosition;
	};
}
