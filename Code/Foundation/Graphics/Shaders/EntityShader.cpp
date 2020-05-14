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
    _viewPositionLocation(-1),
    _worldTransformationLocation(-1),
    _normalTransformationLocation(-1),

    _lightsCountLocation(-1),

    _fogDensityLocation(-1),
    _fogGradientLocation(-1),
    _fogColorLocation(-1),

    _materialAmbientLocation(-1),
    _materialColorLocation(-1),
    _materialSpecularLocation(-1),
    _materialShininessLocation(-1),

    _viewMatrix(1.0f)
{
}

Graphics::EntityShader::~EntityShader()
{
}

void Graphics::EntityShader::InitializeUniformVariables()
{
    // Setup transformations
    this->InitializeMatrix4fLocation("projection", Math::Matrix4f(1.0f), this->_projectionLocation);
    this->InitializeMatrix4fLocation("view", Math::Matrix4f(1.0f), this->_viewLocation);
    this->InitializeVector3fLocation("viewPosition", Math::Vector3f(1.0f), this->_viewPositionLocation);
    this->InitializeMatrix4fLocation("worldTransformation", Math::Matrix4f(1.0f), this->_worldTransformationLocation);
    this->InitializeMatrix3fLocation("normalTransformation", Math::Matrix4f(1.0f), this->_normalTransformationLocation);

    // Setup clipping plane
    this->InitializeVector4fLocation("clippingPlane.plane", Math::Vector4f(0.0f, -1.0f, 0.0f, 0.5f), this->_clippingPlaneLocation.plane);
    this->InitializeBoolLocation("clippingPlane.enabled", true, this->_clippingPlaneLocation.enabled);

    // Setup sun
    this->InitializeVector3fLocation("sun.direction", Math::Vector3f(-1.0f, -1.0f, 0.0f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.ambient", Math::Vector3f(0.2f), this->_sunLocation.ambient);
    this->InitializeVector3fLocation("sun.diffuse", Math::Vector3f(0.5f), this->_sunLocation.diffuse);
    this->InitializeFloatLocation("sun.specular", 1.0f, this->_sunLocation.specular);

    // Setup point lights
    this->InitializeIntLocation("lightsCount", 0, this->_lightsCountLocation);
    for (int index = 0; index < EntityShader::maxLightCount; index++) {
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].position", Math::Vector3f(0.0f), this->_lightLocations[index].position);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].ambient", Math::Vector3f(1.0f), this->_lightLocations[index].ambient);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].diffuse", Math::Vector3f(1.0f), this->_lightLocations[index].diffuse);
        this->InitializeFloatLocation("light[" + std::to_string(index) + "].specular", 1.0f, this->_lightLocations[index].specular);
        this->InitializeVector3fLocation("light[" + std::to_string(index) + "].attenuation", Math::Vector3f(1.0f, 0.0f, 0.0f), this->_lightLocations[index].attenuation);
    }

    // Setup fog
    this->InitializeFloatLocation("fog.density", 0.0175f, this->_fogDensityLocation);
    this->InitializeFloatLocation("fog.gradient", 7.5f, this->_fogGradientLocation);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.2f, 0.325f, 0.375f), this->_fogColorLocation);

    // Setup material
    this->InitializeVector3fLocation("material.color", Math::Vector3f(0.85f), this->_materialColorLocation);
    this->InitializeFloatLocation("material.specular", 0.5f, this->_materialSpecularLocation);
    this->InitializeFloatLocation("material.shininess", 25.0f, this->_materialShininessLocation);

    // Setup texture mappers
    this->InitializeBoolLocation("diffuseSampler.enabled", false, this->_diffuseSamplerLocation.enabled);
    this->InitializeBoolLocation("normalSampler.enabled", false, this->_normalSamplerLocation.enabled);
    this->InitializeBoolLocation("specularSampler.enabled", false, this->_specularSamplerLocation.enabled);

    this->InitializeIntLocation("diffuseSampler.texture", EnumToValue(Texture::Bank::DIFFUSE), this->_diffuseSamplerLocation.texture);
    this->InitializeIntLocation("normalSampler.texture", EnumToValue(Texture::Bank::NORMAL), this->_normalSamplerLocation.texture);
    this->InitializeIntLocation("specularSampler.texture", EnumToValue(Texture::Bank::SPECULAR), this->_specularSamplerLocation.texture);
}

void Graphics::EntityShader::LoadProjection(std::shared_ptr<const Projection> projection)
{
    this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::EntityShader::EnableClippingPlane(const Math::Vector4f plane)
{
    glEnable(GL_CLIP_DISTANCE0);
    this->LoadBool(this->_clippingPlaneLocation.enabled, true);
    this->LoadVector4f(this->_clippingPlaneLocation.plane, plane);
}

void Graphics::EntityShader::DisableClippingPlane()
{
    this->LoadBool(this->_clippingPlaneLocation.enabled, false);
    glDisable(GL_CLIP_DISTANCE0);
}

void Graphics::EntityShader::LoadCamera(const std::shared_ptr<Graphics::Camera>& camera)
{
    _assert(camera);

    this->_viewMatrix = Math::ViewMatrix(camera->getPosition(), camera->getRotationX(), camera->getRotationY());

    //this->_viewMatrix = glm::lookAt(camera->getPosition(), Math::Vector3f(0.0f, 0.0f, 0.0f), Math::Vector3f(0.0f, 1.0f, 0.0f));

    this->LoadMatrix4f(this->_viewLocation, this->_viewMatrix);
    this->LoadVector3f(this->_viewPositionLocation, camera->getPosition());
}

void Graphics::EntityShader::LoadSun(std::shared_ptr<DirectionalLight> sun)
{
    Math::Vector3f diffuseColor = sun->GetIntensity() * sun->GetColor();
    Math::Vector3f ambientColor = diffuseColor / 5.0f;

    this->LoadVector3f(this->_sunLocation.direction, sun->GetDirection());
    this->LoadVector3f(this->_sunLocation.ambient, ambientColor);
    this->LoadVector3f(this->_sunLocation.diffuse, diffuseColor);
    this->LoadFloat(this->_sunLocation.specular, 1.0f);
}

void Graphics::EntityShader::LoadLights(const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights)
{
    int lightsCount = static_cast<int>(lights.size());
    _assert(EntityShader::maxLightCount > lightsCount - 1);
    this->LoadInt(this->_lightsCountLocation, lightsCount);

    int index = 0;
    for (auto& light : lights) {
        this->LoadLight(index, light.second);
        index++;
    }
}

void Graphics::EntityShader::LoadLight(int index, const std::shared_ptr<PointLight>& light)
{
    _assert(EntityShader::maxLightCount > index);
    Math::Vector3f diffuseColor = light->GetIntensity() * light->GetColor();
    Math::Vector3f ambientColor = diffuseColor / 5.0f;
    this->LoadVector3f(this->_lightLocations[index].position, light->getPosition());
    this->LoadVector3f(this->_lightLocations[index].ambient, ambientColor);
    this->LoadVector3f(this->_lightLocations[index].diffuse, diffuseColor);
    this->LoadFloat(this->_lightLocations[index].specular, 1.0f);
    this->LoadVector3f(this->_lightLocations[index].attenuation, light->GetAttenuation());
}

void Graphics::EntityShader::LoadFog(float density, float gradient)
{
    this->LoadFloat(this->_fogDensityLocation, density);
    this->LoadFloat(this->_fogGradientLocation, gradient);
}

void Graphics::EntityShader::LoadWorldTransformation(const Math::Matrix4f& transformationMatrix)
{
    ShaderProgram::LoadMatrix4f(this->_worldTransformationLocation, transformationMatrix);
    ShaderProgram::LoadMatrix3f(this->_normalTransformationLocation, glm::transpose(glm::inverse(transformationMatrix)));
}

void Graphics::EntityShader::LoadMaterial(const Material& material)
{
    this->LoadVector3f(this->_materialColorLocation, material.GetColor());
    this->LoadFloat(this->_materialSpecularLocation, material.GetSpecular());
    this->LoadFloat(this->_materialShininessLocation, material.GetReflectivity());
}

void Graphics::EntityShader::LoadHasDiffuseMap(bool hasDiffuseMap)
{
    ShaderProgram::LoadBool(this->_diffuseSamplerLocation.enabled, hasDiffuseMap);
}

void Graphics::EntityShader::LoadHasNormalMap(bool hasNormalMap)
{
    ShaderProgram::LoadBool(this->_normalSamplerLocation.enabled, hasNormalMap);
}

void Graphics::EntityShader::LoadHasSpecularMap(bool hasSpecularMap)
{
    ShaderProgram::LoadBool(this->_specularSamplerLocation.enabled, hasSpecularMap);
}

