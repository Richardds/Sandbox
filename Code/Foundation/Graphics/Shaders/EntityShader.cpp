#include <iostream>

#include "EntityShader.h"
#include "../../Math/Utils.h"
#include "../../Core/Debug.h"
#include "../../Graphics/Core.h"

Graphics::EntityShader::EntityShader() :
    ShaderSystem("Entity"),
    _projectionMatrixLocation(0),
    _viewMatrixLocation(0),
    _viewMatrixInverseLocation(0),
    _modelMatrixLocation(0),
    _normalMatrixLocation(0),
    _lightPositionLocation(0),
    _lightColorLocation(0),
    _projectionMatrix(1.0f),
    _viewMatrix(1.0f)
{
}

Graphics::EntityShader::~EntityShader()
{
}

void Graphics::EntityShader::Begin(std::shared_ptr<Graphics::Camera> camera, std::shared_ptr<Graphics::Light> light)
{
    this->Use();

    this->SetView(camera);
    this->SetLight(light);

    this->LoadMatrix4f(this->_projectionMatrixLocation, this->_projectionMatrix);
    this->LoadMatrix4f(this->_viewMatrixLocation, this->_viewMatrix);
    this->LoadMatrix4f(this->_viewMatrixInverseLocation, glm::inverse(this->_viewMatrix));
}

void Graphics::EntityShader::InitializeUniformVariables()
{
    this->_projectionMatrixLocation = this->GetUniformLocation("projectionMatrix");
    this->LoadMatrix4f(this->_projectionMatrixLocation, Math::Matrix4f(1.0f));

    this->_viewMatrixLocation = this->GetUniformLocation("viewMatrix");
    this->LoadMatrix4f(this->_viewMatrixLocation, Math::Matrix4f(1.0f));

    this->_viewMatrixInverseLocation = this->GetUniformLocation("viewMatrixInverse");
    this->LoadMatrix4f(this->_viewMatrixInverseLocation, Math::Matrix4f(1.0f));

    this->_modelMatrixLocation = this->GetUniformLocation("modelMatrix");
    this->LoadMatrix4f(this->_modelMatrixLocation, Math::Matrix4f(1.0f));

    this->_normalMatrixLocation = this->GetUniformLocation("normalMatrix");
    this->LoadMatrix3f(this->_normalMatrixLocation, Math::Matrix3f(1.0f));

    this->_lightPositionLocation = this->GetUniformLocation("lightPosition");
    this->_lightColorLocation = this->GetUniformLocation("lightColor");
}

void Graphics::EntityShader::SetProjection(float ratio, float fov, float near, float far)
{
    this->_projectionMatrix = Math::projectionMatrix(ratio, fov, near, far);
}

void Graphics::EntityShader::SetView(const std::shared_ptr<Graphics::Camera> view)
{
    _assert(view);

    this->_viewMatrix = Math::viewMatrix(view->getPosition(), view->getRotationX(), view->getRotationY());
}

void Graphics::EntityShader::LoadEntityTransformation(const Math::Matrix4f& modelMatrix)
{
    this->LoadMatrix4f(this->_modelMatrixLocation, modelMatrix);
    this->LoadMatrix3f(this->_normalMatrixLocation, glm::transpose(glm::inverse(modelMatrix)));
}

void Graphics::EntityShader::SetLight(const std::shared_ptr<Light> light)
{
    this->LoadVector3f(this->_lightPositionLocation, light->getPosition());
    this->LoadVector3f(this->_lightColorLocation, light->GetColor());
}

Math::Vector3f Graphics::EntityShader::GetScreenWorldPosition(Math::Vector2ui screenPosition) const
{
    Math::Vector4ui viewport = Graphics::Core::Instance().GetViewport();

    GLfloat depth;
    glReadPixels(screenPosition.x, viewport.w - screenPosition.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    if (depth == 1.0f) {
        return Math::Vector3f(0.0f, 0.0f, 0.0f);
    }

    Math::Vector3f worldPosition = glm::unProject(
        Math::Vector3f(screenPosition.x, viewport.w - screenPosition.y, depth),
        this->_viewMatrix,
        this->_projectionMatrix,
        viewport
    );

    return worldPosition;
}
