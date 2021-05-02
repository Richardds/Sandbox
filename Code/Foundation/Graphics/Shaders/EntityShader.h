// ----------------------------------------------------------------------------------------
//  \file       EntityShader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Game/Scene/Camera.h"
#include "Game/Scene/Light/DirectionalLight.h"
#include "Game/Scene/Light/PointLight.h"
#include "Game/Scene/Light/SpotLight.h"
#include "Graphics/Material.h"
#include "Graphics/Projection.h"
#include "Graphics/Shaders/ShaderSystem.h"
#include "Math/Matrix.h"

namespace Graphics
{
    /// Shader system used for drawing entities
    class EXPORT EntityShader final : public ShaderSystem
    {
    public:
        EntityShader();

        void InitializeUniformVariables() override;
        void LoadProjection(const std::shared_ptr<const Projection>& projection) const;
        void EnableClippingPlane(const Math::Vector4f& plane) const;
        void DisableClippingPlane() const;
        void LoadCamera(const std::shared_ptr<Camera>& camera) const;
        void LoadDirectionalLights(const std::vector<std::shared_ptr<DirectionalLight>>& lights) const;
        void LoadDirectionalLight(int index, const std::shared_ptr<DirectionalLight>& light) const;
        void LoadPointLights(const std::vector<std::shared_ptr<PointLight>>& lights) const;
        void LoadPointLight(int index, const std::shared_ptr<PointLight>& light) const;
        void LoadFlashLight(const std::shared_ptr<SpotLight>& light) const;
        void LoadFlashLightEnabled(bool enabled) const;
        void LoadFog(const Math::Vector3f& color, float density, float gradient) const;
        void LoadFogEnabled(bool enabled);
        void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix) const;
        void LoadMaterial(const Material& material) const;
        void LoadHasDiffuseMap(bool hasDiffuseMap) const;
        void LoadHasNormalMap(bool hasNormalMap) const;
        void LoadHasSpecularMap(bool hasSpecularMap) const;
        void LoadHasSkyboxMap(bool hasSkyboxMap) const;
        void LoadDeformationFactor(float deformationFactor) const;

    private:
        /// Maximal count of possible lights used in the scene
        /// Needs to be changed in shader source too!
        static const int MAX_DIRECTIONAL_LIGHT_COUNT = 3;
        static const int MAX_POINT_LIGHT_COUNT = 10;

        GLint _projectionLocation;
        GLint _viewLocation;
        GLint _viewPositionLocation;
        GLint _worldTransformationLocation;
        GLint _normalTransformationLocation;

        ClippingPlane _clippingPlaneLocation;

        GLint _directionalLightsCountLocation;
        DirectionalLightLocation _directionalLightsLocations[MAX_DIRECTIONAL_LIGHT_COUNT];

        GLint _pointLightsCountLocation;
        PointLightLocation _pointLightsLocations[MAX_POINT_LIGHT_COUNT];

        SpotLightLocation _flashLightLocation;
        GLint _flashLightEnabledLocation;

        TextureSamplerLocation _diffuseSamplerLocation;
        TextureSamplerLocation _normalSamplerLocation;
        TextureSamplerLocation _specularSamplerLocation;

        TextureSamplerLocation _skyboxSamplerLocation;

        GLint _fogEnabledLocation;
        GLint _fogDensityLocation;
        GLint _fogGradientLocation;
        GLint _fogColorLocation;

        GLint _materialColorLocation;
        GLint _materialReflectivityLocation;
        GLint _materialSpecularLocation;
        GLint _materialShininessLocation;

        GLint _deformationFactorLocation;

        bool _fogEnabled;
    };
}
