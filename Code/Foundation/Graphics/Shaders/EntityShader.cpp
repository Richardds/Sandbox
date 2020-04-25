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

    _lightsCountLocation(-1),
    _lightLocations(),

    _fogDensityPosition(-1),
    _fogGradientPosition(-1),
    _fogColorPosition(-1),

    _materialAmbientLocation(-1),
    _materialDiffuseLocation(-1),
    _materialSpecularLocation(-1),
    _materialShininessLocation(-1),

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
    for (int index = 0; index < EntityShader::maxLightCount; index++) {
        this->_lightLocations[index].position = -1;
        this->_lightLocations[index].ambient = -1;
        this->_lightLocations[index].diffuse = -1;
        this->_lightLocations[index].specular = -1;
        this->_lightLocations[index].attenuation = -1;
    }
}

void Graphics::EntityShader::InitializeUniformVariables()
{
    this->InitializeMatrix4fLocation("projectionMatrix", Math::Matrix4f(1.0f), this->_projectionMatrixLocation);
    this->InitializeMatrix4fLocation("viewMatrix", Math::Matrix4f(1.0f), this->_viewMatrixLocation);
    this->InitializeMatrix4fLocation("viewMatrixInverse", Math::Matrix4f(1.0f), this->_viewMatrixInverseLocation);
    this->InitializeMatrix4fLocation("modelMatrix", Math::Matrix4f(1.0f), this->_modelMatrixLocation);
    this->InitializeMatrix3fLocation("normalMatrix", Math::Matrix4f(1.0f), this->_normalMatrixLocation);

    // Setup lights
    this->InitializeIntLocation("lightsCount", 0, this->_lightsCountLocation);
    for (int index = 0; index < EntityShader::maxLightCount; index++) {
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].position", Math::Vector3f(0.0f), this->_lightLocations[index].position);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].ambient", Math::Vector3f(0.0f), this->_lightLocations[index].ambient);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].diffuse", Math::Vector3f(0.0f), this->_lightLocations[index].diffuse);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].specular", Math::Vector3f(0.0f), this->_lightLocations[index].specular);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].attenuation", Math::Vector3f(1.0f, 0.0f, 0.0f), this->_lightLocations[index].attenuation);
    }

    // Setup fog
    this->InitializeFloatLocation("fog.density", 0.035f, this->_fogDensityPosition);
    this->InitializeFloatLocation("fog.gradient", 10.0f, this->_fogGradientPosition);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.25f, 0.25f, 0.25f), this->_fogColorPosition);

    // Setup material
    this->InitializeVector3fLocation("material.ambient", Math::Vector3f(0.4f, 0.2f, 0.25f), this->_materialAmbientLocation);
    this->InitializeVector3fLocation("material.diffuse", Math::Vector3f(0.85f, 0.85f, 0.85f), this->_materialDiffuseLocation);
    this->InitializeFloatLocation("material.specular", 0.5f, this->_materialSpecularLocation);
    this->InitializeFloatLocation("material.shininess", 5.0f, this->_materialShininessLocation);

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

void Graphics::EntityShader::Begin(std::shared_ptr<Graphics::Camera> camera, std::vector<std::shared_ptr<Graphics::Light>> lights)
{
    this->Use();

    this->SetView(camera);

    int lightsCount = static_cast<int>(lights.size());
    _assert(EntityShader::maxLightCount > lightsCount - 1);
    this->LoadInt(this->_lightsCountLocation, lightsCount);

    int index = 0;
    for (std::shared_ptr<Graphics::Light>& light : lights) {
        this->LoadLight(index++, light);
    }

    this->LoadMatrix4f(this->_projectionMatrixLocation, this->_projectionMatrix);
    this->LoadMatrix4f(this->_viewMatrixLocation, this->_viewMatrix);
    this->LoadMatrix4f(this->_viewMatrixInverseLocation, glm::inverse(this->_viewMatrix));
}

void Graphics::EntityShader::SetProjection(float ratio, float fov, float near, float far)
{
    this->_projectionMatrix = Math::projectionMatrix(ratio, fov, near, far);
}

void Graphics::EntityShader::SetView(const std::shared_ptr<Graphics::Camera>& view)
{
    _assert(view);

    this->_viewMatrix = Math::viewMatrix(view->getPosition(), view->getRotationX(), view->getRotationY());
}

void Graphics::EntityShader::LoadLight(int index, const std::shared_ptr<Light>& light)
{
    _assert(EntityShader::maxLightCount > index);
    Math::Vector3f diffuse = light->GetColor() * 0.75f;
    this->LoadVector3f(this->_lightLocations[index].position, light->getPosition());
    this->LoadVector3f(this->_lightLocations[index].ambient, diffuse * 0.2f);
    this->LoadVector3f(this->_lightLocations[index].diffuse, diffuse);
    this->LoadVector3f(this->_lightLocations[index].specular, Math::Vector3f(1.0f));
    this->LoadVector3f(this->_lightLocations[index].attenuation, light->GetAttenuation());
}

void Graphics::EntityShader::LoadEntityTransformation(const Math::Matrix4f& modelMatrix)
{
    ShaderProgram::LoadMatrix4f(this->_modelMatrixLocation, modelMatrix);
    ShaderProgram::LoadMatrix3f(this->_normalMatrixLocation, glm::transpose(glm::inverse(modelMatrix)));
}

void Graphics::EntityShader::LoadHasDiffuseMap(bool hasDiffuseMap)
{
    ShaderProgram::LoadBool(this->_diffuseMapperEnabledLocation, hasDiffuseMap);
}

void Graphics::EntityShader::LoadHasNormalMap(bool hasNormalMap)
{
    ShaderProgram::LoadBool(this->_normalMapperEnabledLocation, hasNormalMap);
}

void Graphics::EntityShader::LoadHasSpecularMap(bool hasSpecularMap)
{
    ShaderProgram::LoadBool(this->_specularMapperEnabledLocation, hasSpecularMap);
}

void Graphics::EntityShader::LoadHasMaterialMap(bool hasMaterialMap)
{
    ShaderProgram::LoadBool(this->_materialMapperEnabledLocation, hasMaterialMap);
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
