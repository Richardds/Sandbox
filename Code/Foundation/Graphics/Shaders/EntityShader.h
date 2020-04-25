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
        void Begin(std::shared_ptr<Graphics::Camera> camera, std::shared_ptr<Graphics::Light> light);
        void InitializeUniformVariables();
        void SetProjection(float ratio, float fov, float near, float far);
        void SetView(const std::shared_ptr<Camera> view);
        void SetLight(const std::shared_ptr<Light> light);
        void LoadEntityTransformation(const Math::Matrix4f& modelMatrix);
        void LoadHasDiffuseMap(bool hasDiffuseMap);
        void LoadHasNormalMap(bool hasNormalMap);
        void LoadHasSpecularMap(bool hasSpecularMap);
        void LoadHasMaterialMap(bool hasMaterialMap);
        Math::Vector3f GetScreenWorldPosition(Math::Vector2ui screenPosition) const;

    private:
        GLint _diffuseMapperLocation;
        GLint _normalMapperLocation;
        GLint _specularMapperLocation;
        GLint _materialMapperLocation;

        GLint _projectionMatrixLocation;
        GLint _viewMatrixLocation;
        GLint _viewMatrixInverseLocation;
        GLint _modelMatrixLocation;
        GLint _normalMatrixLocation;

        GLint _lightPositionLocation;
        GLint _lightColorLocation;

        GLint _fogDensityPosition;
        GLint _fogGradientPosition;
        GLint _fogColorPosition;

        GLint _enableDiffuseMapperLocation;
        GLint _enableNormalMapperLocation;
        GLint _enableSpecularMapperLocation;
        GLint _enableMaterialMapperLocation;

        Math::Matrix4f _projectionMatrix;
        Math::Matrix4f _viewMatrix;
    };

}
