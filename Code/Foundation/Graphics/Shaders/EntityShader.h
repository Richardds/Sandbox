#pragma once

#include "ShaderSystem.h"
#include "../Material.h"
#include "../Projection.h"
#include "../../Game/Scene/Camera.h"
#include "../../Game/Scene/DirectionalLight.h"
#include "../../Game/Scene/PointLight.h"
#include "../../Math/Matrix.h"

namespace Graphics
{
	class EntityShader final : public ShaderSystem
	{
	public:
		EntityShader();
		void InitializeUniformVariables() override;
		void LoadProjection(const std::shared_ptr<const Projection>& projection);
		void EnableClippingPlane(const Math::Vector4f& plane);
		void DisableClippingPlane();
		void LoadCamera(const std::shared_ptr<Camera>& camera);
		void LoadSun(const std::shared_ptr<DirectionalLight>& sun);
		void LoadLights(const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights);
		void LoadLight(int index, const std::shared_ptr<PointLight>& light);
		void LoadFog(float density, float gradient);
		void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix);
		void LoadMaterial(const Material& material);
		void LoadHasDiffuseMap(bool hasDiffuseMap);
		void LoadHasNormalMap(bool hasNormalMap);
		void LoadHasSpecularMap(bool hasSpecularMap);

	private:
		static const int maxLightCount = 10;

		GLint _projectionLocation;
		GLint _viewLocation;
		GLint _viewPositionLocation;
		GLint _worldTransformationLocation;
		GLint _normalTransformationLocation;

		ClippingPlane _clippingPlaneLocation;

		SunLocation _sunLocation;
		PointLightLocation _lightLocations[maxLightCount];
		GLint _lightsCountLocation;

		TextureSamplerLocation _diffuseSamplerLocation;
		TextureSamplerLocation _normalSamplerLocation;
		TextureSamplerLocation _specularSamplerLocation;

		GLint _fogDensityLocation;
		GLint _fogGradientLocation;
		GLint _fogColorLocation;

		GLint _materialColorLocation;
		GLint _materialSpecularLocation;
		GLint _materialShininessLocation;

		Math::Matrix4f _viewMatrix;
	};
}
