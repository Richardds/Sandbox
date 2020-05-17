#pragma once

#include "ShaderSystem.h"

namespace Graphics
{
	class DepthShader : public ShaderSystem
	{
	public:
		DepthShader();
		void InitializeUniformVariables() override;
		void LoadTransformation(const Math::Matrix4f& transformation);

	private:
		GLint _transformationPosition;
	};
}
