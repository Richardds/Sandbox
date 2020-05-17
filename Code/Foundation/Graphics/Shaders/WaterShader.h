#pragma once

#include "ShaderSystem.h"
#include "../../Game/Scene/Camera.h"
#include "../../Game/Scene/PointLight.h"
#include "../../Game/Scene/DirectionalLight.h"
#include "../../Math/Matrix.h"
#include "../Projection.h"
#include "../Material.h"

namespace Graphics
{

    class WaterShader : public ShaderSystem
    {
    public:
        WaterShader();
        virtual ~WaterShader();
        void InitializeUniformVariables();
        void LoadProjection(std::shared_ptr<const Projection> projection);
        void LoadCamera(const std::shared_ptr<Camera>& camera);
        void LoadSun(std::shared_ptr<DirectionalLight> sun);
        void LoadFog(float density, float gradient);
        void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix);
        void LoadTextureTiling(float tiling);
        void LoadHasNormalMap(bool hasNormalMap);
        void LoadHasDistortionMap(bool hasDistortionMap);
        void LoadDistortionOffset(float offset);

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
        GLint _depthSamplerLocation;

        SunLocation _sunLocation;

        GLint _fogDensityLocation;
        GLint _fogGradientLocation;
        GLint _fogColorLocation;

        Math::Matrix4f _viewMatrix;
    };

}
