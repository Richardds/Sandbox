#pragma once

#include "ShaderSystem.h"
#include "../Scene/Camera.h"
#include "../Scene/Light.h"
#include "../../Math/Matrix.h"
#include "../Material.h"

namespace Graphics
{

    class EntityShader : public ShaderSystem
    {
    public:
        EntityShader();
        virtual ~EntityShader();
        void InitializeUniformVariables();
        void Begin(std::shared_ptr<Graphics::Camera> camera, const std::unordered_map<std::string, std::shared_ptr<Light>>& lights);
        void SetProjection(float ratio, float fov, float near, float far);
        void SetView(const std::shared_ptr<Camera>& view);
        void LoadLight(int index, const std::shared_ptr<Light>& light);
        void LoadEntityTransformation(const Math::Matrix4f& modelMatrix);
        void LoadMaterial(const Material& material);
        void LoadHasDiffuseMap(bool hasDiffuseMap);
        void LoadHasNormalMap(bool hasNormalMap);
        void LoadHasSpecularMap(bool hasSpecularMap);
        void LoadHasMaterialMap(bool hasMaterialMap);
        Math::Vector3f GetScreenWorldPosition(Math::Vector2ui screenPosition) const;

    private:
        static const int maxLightCount = 10;

        struct DirectionalLightLocation {
            DirectionalLightLocation() : direction(-1), ambient(-1), diffuse(-1), specular(-1) {}
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

        DirectionalLightLocation _sunLocation;
        PointLightLocation _lightLocations[maxLightCount];
        GLint _lightsCountLocation;

        TextureSamplerLocation _diffuseSampler;
        TextureSamplerLocation _normalSampler;
        TextureSamplerLocation _specularSampler;
        TextureSamplerLocation _materialSampler;

        GLint _fogDensityPosition;
        GLint _fogGradientPosition;
        GLint _fogColorPosition;

        GLint _materialAmbientLocation;
        GLint _materialDiffuseLocation;
        GLint _materialSpecularLocation;
        GLint _materialReflectivityLocation;

        Math::Matrix4f _projectionMatrix;
        Math::Matrix4f _viewMatrix;
    };

}
