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
        void LoadEntityTransformation(const Math::Matrix4f& modelMatrix);
        void SetLight(const std::shared_ptr<Light> light);
        Math::Vector3f GetScreenWorldPosition(Math::Vector2ui screenPosition) const;

    private:
        GLuint _projectionMatrixLocation;
        GLuint _viewMatrixLocation;
        GLuint _viewMatrixInverseLocation;
        GLuint _modelMatrixLocation;
        GLuint _normalMatrixLocation;
        GLuint _lightPositionLocation;
        GLuint _lightColorLocation;
        Math::Matrix4f _projectionMatrix;
        Math::Matrix4f _viewMatrix;
    };

}
