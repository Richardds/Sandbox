#pragma once

#include "ShaderSystem.h"
#include "../Material.h"
#include "../Projection.h"
#include "../../Game/Scene/Camera.h"
#include "../../Game/Scene/DirectionalLight.h"
#include "../../Math/Matrix.h"

namespace Graphics
{
	class WaterShader : public ShaderSystem
	{
	public:
		WaterShader();
		void InitializeUniformVariables() override;
		void LoadProjection(const std::shared_ptr<const Projection>& projection) const;
		void LoadCamera(const std::shared_ptr<Camera>& camera) const;
		void LoadSun(const std::shared_ptr<DirectionalLight>& sun) const;
		void LoadFog(const Math::Vector3f& color, float density, float gradient) const;
		void LoadFogEnabled(bool enabled);
		void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix) const;
		void LoadTextureTiling(float tiling) const;
		void LoadHasNormalMap(bool hasNormalMap) const;
		void LoadHasDistortionMap(bool hasDistortionMap) const;
		void LoadDistortionOffset(float offset) const;

	private:
		GLint _projectionLocation;
		GLint _viewLocation;
		GLint _viewPositionLocation;
		GLint _worldTransformationLocation;
		GLint _normalTransformationLocation;

		GLint _textureTilingLocation;
		TextureSamplerLocation _normalSamplerLocation;
		TextureSamplerLocation _distortionSamplerLocation;
		GLint _distortionOffsetLocation;

		GLint _reflectionSamplerLocation;
		GLint _refractionSamplerLocation;

		SunLocation _sunLocation;

		GLint _fogEnabledLocation;
		GLint _fogColorLocation;
		GLint _fogDensityLocation;
		GLint _fogGradientLocation;

		bool _fogEnabled;
	};
}
