// ----------------------------------------------------------------------------------------
//  \file       WaterShader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Camera.h"
#include "Game/Scene/Light/DirectionalLight.h"
#include "Game/Scene/Light/PointLight.h"
#include "Game/Scene/Light/SpotLight.h"
#include "Graphics/Projection.h"
#include "Graphics/Shaders/ShaderSystem.h"
#include "Math/Matrix.h"

namespace Graphics
{
    /// Shader system used for drawing water tiles
    class EXPORT WaterShader : public ShaderSystem
    {
    public:
        WaterShader();

        void InitializeUniformVariables() override;
        void LoadProjection(const std::shared_ptr<const Projection>& projection) const;
        void LoadCamera(const std::shared_ptr<Camera>& camera) const;
        void LoadSun(const std::shared_ptr<DirectionalLight>& sun) const;
        void LoadLights(const std::vector<std::shared_ptr<PointLight>>& lights) const;
        void LoadLight(int index, const std::shared_ptr<PointLight>& light) const;
        void LoadFlashLight(const std::shared_ptr<SpotLight>& light) const;
        void LoadFlashLightEnabled(bool enabled) const;
        void LoadFog(const Math::Vector3f& color, float density, float gradient) const;
        void LoadFogEnabled(bool enabled);
        void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix) const;
        void LoadTextureTiling(float tiling) const;
        void LoadHasNormalMap(bool hasNormalMap) const;
        void LoadHasDistortionMap(bool hasDistortionMap) const;
        void LoadDistortionOffset(float offset) const;

    private:
        /// Maximal count of possible lights used in the scene
        static const int MAX_LIGHT_COUNT = 10;

        GLint _projectionLocation;
        GLint _viewLocation;
        GLint _viewPositionLocation;
        GLint _worldTransformationLocation;
        GLint _normalTransformationLocation;

        TextureSamplerLocation _normalSamplerLocation;
        TextureSamplerLocation _distortionSamplerLocation;
        GLint _textureTilingLocation;
        GLint _distortionOffsetLocation;
        GLint _reflectionSamplerLocation;
        GLint _refractionSamplerLocation;

        SunLocation _sunLocation;
        PointLightLocation _lightLocations[MAX_LIGHT_COUNT];
        GLint _lightsCountLocation;
        SpotLightLocation _flashLightLocation;
        GLint _flashLightEnabledLocation;

        GLint _fogEnabledLocation;
        GLint _fogColorLocation;
        GLint _fogDensityLocation;
        GLint _fogGradientLocation;

        bool _fogEnabled;
    };
}
