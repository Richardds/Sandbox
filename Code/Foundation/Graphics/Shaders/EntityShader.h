#pragma once

#include "ShaderSystem.h"
#include "../../Game/Scene/Camera.h"
#include "../../Game/Scene/Light.h"
#include "../../Game/Scene/Sun.h"
#include "../../Math/Matrix.h"
#include "../Projection.h"
#include "../Material.h"

namespace Graphics
{

    class EntityShader : public ShaderSystem
    {
    public:
        EntityShader();
        virtual ~EntityShader();
        void InitializeUniformVariables();
        void LoadProjection(std::shared_ptr<const Projection> projection);
        void LoadCamera(const std::shared_ptr<Camera>& view);
        void LoadSun(std::shared_ptr<Sun> sun);
        void LoadLights(const std::unordered_map<std::string, std::shared_ptr<Light>>& lights);
        void LoadLight(int index, const std::shared_ptr<Light>& light);
        void LoadFog(float density, float gradient);
        void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix);
        void LoadMaterial(const Material& material);
        void LoadHasDiffuseMap(bool hasDiffuseMap);
        void LoadHasNormalMap(bool hasNormalMap);
        void LoadHasSpecularMap(bool hasSpecularMap);

    private:
        static const int maxLightCount = 10;

        struct SunLocation {
            SunLocation() : direction(-1), ambient(-1), diffuse(-1), specular(-1) {}
            GLint direction;
            GLint ambient;
            GLint diffuse;
            GLint specular;
        };

        struct PointLightLocation {
            PointLightLocation() : position(-1), attenuation(-1), ambient(-1), diffuse(-1), specular(-1) {}
            GLint position;
            GLint attenuation;
            GLint ambient;
            GLint diffuse;
            GLint specular;
        };

        struct TextureSamplerLocation {
            TextureSamplerLocation() : texture(-1), enabled(-1) {}
            GLint texture;
            GLint enabled;
        };

        GLint _projectionLocation;
        GLint _viewLocation;
        GLint _viewInverseLocation;
        GLint _modelTransformationLocation;
        GLint _normalTransformationLocation;

        SunLocation _sunLocation;
        PointLightLocation _lightLocations[maxLightCount];
        GLint _lightsCountLocation;

        TextureSamplerLocation _diffuseSamplerLocation;
        TextureSamplerLocation _normalSamplerLocation;
        TextureSamplerLocation _specularSamplerLocation;

        GLint _fogDensityLocation;
        GLint _fogGradientLocation;
        GLint _fogColorLocation;

        GLint _materialAmbientLocation;
        GLint _materialDiffuseLocation;
        GLint _materialSpecularLocation;
        GLint _materialReflectivityLocation;


        Math::Matrix4f _viewMatrix;
    };

}
