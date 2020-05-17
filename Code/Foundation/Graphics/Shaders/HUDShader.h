#pragma once

#include "ShaderSystem.h"
#include "../Projection.h"

namespace Graphics
{
	class HUDShader : public ShaderSystem
	{
	public:
		HUDShader();
		void InitializeUniformVariables() override;
		void LoadAspectRatio(float aspectRatio);
		void LoadPosition(const Math::Vector2f& position);

	private:
		GLint _aspectRatioLocation;
		GLint _screenPositionLocation;
		GLint _mapSamplerLocation;
	};
}
