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
		void LoadProjection(const std::shared_ptr<const Projection>& projection) const;
		void EnableClippingPlane(const Math::Vector4f& plane) const;
		void DisableClippingPlane() const;
		void LoadCamera(const std::shared_ptr<Camera>& camera) const;
		void LoadSun(const std::shared_ptr<DirectionalLight>& sun) const;
		void LoadLights(const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights) const;
		void LoadLight(int index, const std::shared_ptr<PointLight>& light) const;
		void LoadFog(const Math::Vector3f& color, float density, float gradient) const;
		void LoadFogEnabled(bool enabled);
		void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix) const;
		void LoadMaterial(const Material& material) const;
		void LoadHasDiffuseMap(bool hasDiffuseMap) const;
		void LoadHasNormalMap(bool hasNormalMap) const;
		void LoadHasSpecularMap(bool hasSpecularMap) const;

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

		GLint _fogEnabledLocation;
		GLint _fogDensityLocation;
		GLint _fogGradientLocation;
		GLint _fogColorLocation;

		GLint _materialColorLocation;
		GLint _materialSpecularLocation;
		GLint _materialShininessLocation;

		bool _fogEnabled;
	};
}
