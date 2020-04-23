#include <iostream>

#include "EntityShader.h"
#include "../Texture.h"
#include "../../Math/Utils.h"
#include "../../Core/Debug.h"
#include "../../Graphics/Core.h"
#include "../../Core/Types.h"

Graphics::EntityShader::EntityShader() :
    ShaderSystem("Entity"),
    _diffuseMapSamplerLocation(0),
    _normalMapSamplerLocation(0),
    _projectionMatrixLocation(0),
    _viewMatrixLocation(0),
    _viewMatrixInverseLocation(0),
    _modelMatrixLocation(0),
    _normalMatrixLocation(0),
    _lightPositionLocation(0),
    _lightColorLocation(0),
    _hasDiffuseMapLocation(0),
    _hasNormalMapLocation(0),
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
    this->InitializeMatrix4fLocation("projectionMatrix", Math::Matrix4f(1.0f), this->_projectionMatrixLocation);
    this->InitializeMatrix4fLocation("viewMatrix", Math::Matrix4f(1.0f), this->_viewMatrixLocation);
    this->InitializeMatrix4fLocation("viewMatrixInverse", Math::Matrix4f(1.0f), this->_viewMatrixInverseLocation);
    this->InitializeMatrix4fLocation("modelMatrix", Math::Matrix4f(1.0f), this->_modelMatrixLocation);

    this->InitializeMatrix3fLocation("normalMatrix", Math::Matrix4f(1.0f), this->_normalMatrixLocation);

    this->InitializeVector3fLocation("lightPosition", Math::Vector3f(0.0f), this->_lightPositionLocation);
    this->InitializeVector3fLocation("lightColor", Math::Vector3f(1.0f), this->_lightColorLocation);

    this->InitializeBoolLocation("hasDiffuseMap", false, this->_hasDiffuseMapLocation);
    this->InitializeBoolLocation("hasNormalMap", false, this->_hasNormalMapLocation);

    // Setup texture banks
    this->InitializeIntLocation("diffuseMapSampler", EnumToValue(Texture::Bank::DIFFUSE), this->_diffuseMapSamplerLocation);
    this->InitializeIntLocation("normalMapSampler", EnumToValue(Texture::Bank::NORMAL), this->_normalMapSamplerLocation);
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

void Graphics::EntityShader::SetLight(const std::shared_ptr<Light> light)
{
    this->LoadVector3f(this->_lightPositionLocation, light->getPosition());
    this->LoadVector3f(this->_lightColorLocation, light->GetColor());
}

void Graphics::EntityShader::LoadEntityTransformation(const Math::Matrix4f& modelMatrix)
{
    this->LoadMatrix4f(this->_modelMatrixLocation, modelMatrix);
    this->LoadMatrix3f(this->_normalMatrixLocation, glm::transpose(glm::inverse(modelMatrix)));
}

void Graphics::EntityShader::LoadHasDiffuseMap(bool hasDiffuseMap)
{
    this->LoadBool(this->_hasDiffuseMapLocation, hasDiffuseMap);
}

void Graphics::EntityShader::LoadHasNormalMap(bool hasNormalMap)
{
    this->LoadBool(this->_hasNormalMapLocation, hasNormalMap);
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
