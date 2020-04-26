#pragma once

#include "ShaderSystem.h"
#include "../Scene/Camera.h"
#include "../Scene/Light.h"
#include "../../Math/Matrix.h"

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
        void LoadHasDiffuseMap(bool hasDiffuseMap);
        void LoadHasNormalMap(bool hasNormalMap);
        void LoadHasSpecularMap(bool hasSpecularMap);
        void LoadHasMaterialMap(bool hasMaterialMap);
        Math::Vector3f GetScreenWorldPosition(Math::Vector2ui screenPosition) const;

    private:
        static const int maxLightCount = 10;

        struct LightUniformLocation {
            GLint position;
            GLint attenuation;
            GLint ambient;
            GLint diffuse;
            GLint specular;
        };

        GLint _diffuseMapperTextureLocation;
        GLint _normalMapperTextureLocation;
        GLint _specularMapperTextureLocation;
        GLint _materialMapperTextureLocation;

        GLint _projectionLocation;
        GLint _viewLocation;
        GLint _viewInverseLocation;
        GLint _modelTransformationLocation;
        GLint _normalTransformationLocation;

        GLint _lightsCountLocation;
        LightUniformLocation _lightLocations[maxLightCount];

        GLint _fogDensityPosition;
        GLint _fogGradientPosition;
        GLint _fogColorPosition;

        GLint _materialAmbientLocation;
        GLint _materialDiffuseLocation;
        GLint _materialSpecularLocation;
        GLint _materialShininessLocation;

        GLint _diffuseMapperEnabledLocation;
        GLint _normalMapperEnabledLocation;
        GLint _specularMapperEnabledLocation;
        GLint _materialMapperEnabledLocation;

        Math::Matrix4f _projectionMatrix;
        Math::Matrix4f _viewMatrix;
    };

}
