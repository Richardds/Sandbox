#pragma once

#include "Precompiled.h"
#include "Game/Scene/Camera.h"
#include "Game/Scene/DirectionalLight.h"
#include "Game/Scene/PointLight.h"
#include "Graphics/Material.h"
#include "Graphics/Projection.h"
#include "Graphics/Shaders/ShaderSystem.h"
#include "Math/Matrix.h"

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
		void LoadLights(const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights) const;
		void LoadLight(int index, const std::shared_ptr<PointLight>& light) const;
		void LoadFog(const Math::Vector3f& color, float density, float gradient) const;
		void LoadFogEnabled(bool enabled);
		void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix) const;
		void LoadTextureTiling(float tiling) const;
		void LoadHasNormalMap(bool hasNormalMap) const;
		void LoadHasDistortionMap(bool hasDistortionMap) const;
		void LoadDistortionOffset(float offset) const;

	private:
		static const int MAX_LIGHT_COUNT = 10;
		
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
		PointLightLocation _lightLocations[MAX_LIGHT_COUNT];
		GLint _lightsCountLocation;

		GLint _fogEnabledLocation;
		GLint _fogColorLocation;
		GLint _fogDensityLocation;
		GLint _fogGradientLocation;

		bool _fogEnabled;
	};
}
