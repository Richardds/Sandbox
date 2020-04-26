#include <iostream>

#include "EntityShader.h"
#include "../../Core/Types.h"
#include "../../Core/Debug.h"
#include "../../Graphics/Core.h"
#include "../../Math/Utils.h"
#include "../Texture.h"

Graphics::EntityShader::EntityShader() :
    ShaderSystem("Entity"),
    _projectionLocation(-1),
    _viewLocation(-1),
    _viewInverseLocation(-1),
    _modelTransformationLocation(-1),
    _normalTransformationLocation(-1),

    _lightsCountLocation(-1),

    _fogDensityPosition(-1),
    _fogGradientPosition(-1),
    _fogColorPosition(-1),

    _materialDiffuseLocation(-1),
    _materialSpecularLocation(-1),
    _materialReflectivityLocation(-1),

    _projectionMatrix(1.0f),
    _viewMatrix(1.0f)
{
}

Graphics::EntityShader::~EntityShader()
{
    for (int index = 0; index < EntityShader::maxLightCount; index++) {
        this->_lightLocations[index].position = -1;
        this->_lightLocations[index].diffuse = -1;
        this->_lightLocations[index].specular = -1;
        this->_lightLocations[index].attenuation = -1;
    }
}

void Graphics::EntityShader::InitializeUniformVariables()
{
    this->InitializeMatrix4fLocation("projection", Math::Matrix4f(1.0f), this->_projectionLocation);
    this->InitializeMatrix4fLocation("view", Math::Matrix4f(1.0f), this->_viewLocation);
    this->InitializeMatrix4fLocation("viewInverse", Math::Matrix4f(1.0f), this->_viewInverseLocation);
    this->InitializeMatrix4fLocation("modelTransformation", Math::Matrix4f(1.0f), this->_modelTransformationLocation);
    this->InitializeMatrix3fLocation("normalTransformation", Math::Matrix4f(1.0f), this->_normalTransformationLocation);

    // Setup sun
    this->InitializeVector3fLocation("sun.direction", Math::Vector3f(-1.0f, -1.0f, 0.0f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.ambient", Math::Vector3f(0.025f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.diffuse", Math::Vector3f(0.075f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.specular", Math::Vector3f(0.05f), this->_sunLocation.direction);

    // Setup point lights
    this->InitializeIntLocation("lightsCount", 0, this->_lightsCountLocation);
    for (int index = 0; index < EntityShader::maxLightCount; index++) {
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].position", Math::Vector3f(0.0f), this->_lightLocations[index].position);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].diffuse", Math::Vector3f(1.0f), this->_lightLocations[index].diffuse);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].specular", Math::Vector3f(1.0f), this->_lightLocations[index].specular);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].attenuation", Math::Vector3f(1.0f, 0.0f, 0.0f), this->_lightLocations[index].attenuation);
    }

    // Setup fog
    this->InitializeFloatLocation("fog.density", 0.035f, this->_fogDensityPosition);
    this->InitializeFloatLocation("fog.gradient", 10.0f, this->_fogGradientPosition);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.0f), this->_fogColorPosition);

    // Setup material
    this->InitializeVector3fLocation("material.diffuse", Math::Vector3f(0.85f), this->_materialDiffuseLocation);
    this->InitializeVector3fLocation("material.specular", Math::Vector3f(0.5f), this->_materialSpecularLocation);
    this->InitializeFloatLocation("material.reflectivity", 5.0f, this->_materialReflectivityLocation);

    // Setup texture mappers
    this->InitializeBoolLocation("diffuseSampler.enabled", false, this->_diffuseSampler.enabled);
    this->InitializeBoolLocation("normalSampler.enabled", false, this->_normalSampler.enabled);
    this->InitializeBoolLocation("specularSampler.enabled", false, this->_specularSampler.enabled);
    this->InitializeBoolLocation("materialSampler.enabled", false, this->_materialSampler.enabled);

    this->InitializeIntLocation("diffuseSampler.texture", EnumToValue(Texture::Bank::DIFFUSE), this->_diffuseSampler.texture);
    this->InitializeIntLocation("normalSampler.texture", EnumToValue(Texture::Bank::NORMAL), this->_normalSampler.texture);
    this->InitializeIntLocation("specularSampler.texture", EnumToValue(Texture::Bank::SPECULAR), this->_specularSampler.texture);
    this->InitializeIntLocation("materialSampler.texture", EnumToValue(Texture::Bank::MATERIAL), this->_materialSampler.texture);
}

void Graphics::EntityShader::Begin(std::shared_ptr<Graphics::Camera> camera, const std::unordered_map<std::string, std::shared_ptr<Light>>& lights)
{
    this->Use();

    this->LoadView(camera);

    int lightsCount = static_cast<int>(lights.size());
    _assert(EntityShader::maxLightCount > lightsCount - 1);
    this->LoadInt(this->_lightsCountLocation, lightsCount);

    int index = 0;
    for (auto& light : lights) {
        this->LoadLight(index++, light.second);
    }
}

void Graphics::EntityShader::LoadProjection(float ratio, float fov, float near, float far)
{
    this->_projectionMatrix = Math::projectionMatrix(ratio, fov, near, far);
    this->LoadMatrix4f(this->_projectionLocation, this->_projectionMatrix);
}

void Graphics::EntityShader::LoadView(const std::shared_ptr<Graphics::Camera>& view)
{
    _assert(view);

    this->_viewMatrix = Math::viewMatrix(view->getPosition(), view->getRotationX(), view->getRotationY());
    this->LoadMatrix4f(this->_viewLocation, this->_viewMatrix);
    this->LoadMatrix4f(this->_viewInverseLocation, glm::inverse(this->_viewMatrix));
}

void Graphics::EntityShader::LoadLight(int index, const std::shared_ptr<Light>& light)
{
    _assert(EntityShader::maxLightCount > index);
    this->LoadVector3f(this->_lightLocations[index].position, light->getPosition());
    this->LoadVector3f(this->_lightLocations[index].diffuse, light->GetColor());
    this->LoadVector3f(this->_lightLocations[index].specular, Math::Vector3f(1.0f));
    this->LoadVector3f(this->_lightLocations[index].attenuation, light->GetAttenuation());
}

void Graphics::EntityShader::LoadEntityTransformation(const Math::Matrix4f& modelMatrix)
{
    ShaderProgram::LoadMatrix4f(this->_modelTransformationLocation, modelMatrix);
    ShaderProgram::LoadMatrix3f(this->_normalTransformationLocation, glm::transpose(glm::inverse(modelMatrix)));
}

void Graphics::EntityShader::LoadMaterial(const Material& material)
{
    this->LoadVector3f(this->_materialDiffuseLocation, material.GetDiffuse());
    this->LoadVector3f(this->_materialSpecularLocation, material.GetSpecular());
    this->LoadFloat(this->_materialReflectivityLocation, material.GetReflectivity());
}

void Graphics::EntityShader::LoadHasDiffuseMap(bool hasDiffuseMap)
{
    ShaderProgram::LoadBool(this->_diffuseSampler.enabled, hasDiffuseMap);
}

void Graphics::EntityShader::LoadHasNormalMap(bool hasNormalMap)
{
    ShaderProgram::LoadBool(this->_normalSampler.enabled, hasNormalMap);
}

void Graphics::EntityShader::LoadHasSpecularMap(bool hasSpecularMap)
{
    ShaderProgram::LoadBool(this->_specularSampler.enabled, hasSpecularMap);
}

void Graphics::EntityShader::LoadHasMaterialMap(bool hasMaterialMap)
{
    ShaderProgram::LoadBool(this->_materialSampler.enabled, hasMaterialMap);
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
