#include <iostream>

#include "EntityShader.h"
#include "../../Core/Types.h"
#include "../../Core/Debug.h"
#include "../../Graphics/Core.h"
#include "../../Math/Utils.h"
#include "../Texture.h"

Graphics::EntityShader::EntityShader() :
    ShaderSystem("Entity"),
    _diffuseMapperTextureLocation(-1),
    _normalMapperTextureLocation(-1),
    _specularMapperTextureLocation(-1),
    _materialMapperTextureLocation(-1),

    _projectionMatrixLocation(-1),
    _viewMatrixLocation(-1),
    _viewMatrixInverseLocation(-1),
    _modelMatrixLocation(-1),
    _normalMatrixLocation(-1),

    _lightPositionLocation(-1),
    _lightColorLocation(-1),

    _fogDensityPosition(-1),
    _fogGradientPosition(-1),
    _fogColorPosition(-1),

    _materialAmbientLocation(-1),
    _materialDiffuseLocation(-1),
    _materialSpecularLocation(-1),
    _materialReflectivityLocation(-1),

    _diffuseMapperEnabledLocation(-1),
    _normalMapperEnabledLocation(-1),
    _specularMapperEnabledLocation(-1),
    _materialMapperEnabledLocation(-1),

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

    // Setup light
    this->InitializeVector3fLocation("light.position", Math::Vector3f(0.0f), this->_lightPositionLocation);
    this->InitializeVector3fLocation("light.color", Math::Vector3f(1.0f), this->_lightColorLocation);

    // Setup fog
    this->InitializeFloatLocation("fog.density", 0.045f, this->_fogDensityPosition);
    this->InitializeFloatLocation("fog.gradient", 2.5f, this->_fogGradientPosition);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.25f, 0.25f, 0.25f), this->_fogColorPosition);

    // Setup material
    this->InitializeVector3fLocation("material.ambient", Math::Vector3f(0.0f), this->_materialAmbientLocation); // TODO
    this->InitializeVector3fLocation("material.diffuse", Math::Vector3f(0.85f, 0.85f, 0.85f), this->_materialDiffuseLocation);
    this->InitializeVector3fLocation("material.specular", Math::Vector3f(0.0f), this->_materialSpecularLocation);
    this->InitializeFloatLocation("material.reflectivity", 0.5f, this->_materialReflectivityLocation);

    // Setup texture mappers
    this->InitializeBoolLocation("diffuseMapper.enabled", false, this->_diffuseMapperEnabledLocation);
    this->InitializeBoolLocation("normalMapper.enabled", false, this->_normalMapperEnabledLocation);
    this->InitializeBoolLocation("specularMapper.enabled", false, this->_specularMapperEnabledLocation);
    this->InitializeBoolLocation("materialMapper.enabled", false, this->_materialMapperEnabledLocation);

    this->InitializeIntLocation("diffuseMapper.texture", EnumToValue(Texture::Bank::DIFFUSE), this->_diffuseMapperTextureLocation);
    this->InitializeIntLocation("normalMapper.texture", EnumToValue(Texture::Bank::NORMAL), this->_normalMapperTextureLocation);
    this->InitializeIntLocation("specularMapper.texture", EnumToValue(Texture::Bank::SPECULAR), this->_specularMapperTextureLocation);
    this->InitializeIntLocation("materialMapper.texture", EnumToValue(Texture::Bank::MATERIAL), this->_materialMapperTextureLocation);
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
    this->LoadBool(this->_diffuseMapperEnabledLocation, hasDiffuseMap);
}

void Graphics::EntityShader::LoadHasNormalMap(bool hasNormalMap)
{
    this->LoadBool(this->_normalMapperEnabledLocation, hasNormalMap);
}

void Graphics::EntityShader::LoadHasSpecularMap(bool hasSpecularMap)
{
    this->LoadBool(this->_specularMapperEnabledLocation, hasSpecularMap);
}

void Graphics::EntityShader::LoadHasMaterialMap(bool hasMaterialMap)
{
    this->LoadBool(this->_materialMapperEnabledLocation, hasMaterialMap);
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
