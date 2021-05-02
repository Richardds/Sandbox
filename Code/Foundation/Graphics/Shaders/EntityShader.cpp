// ----------------------------------------------------------------------------------------
//  \file       EntityShader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Shaders/EntityShader.h"
#include "Core/Debug.h"
#include "Core/Types.h"
#include "Graphics/Texture.h"
#include "Math/MathUtils.h"

Graphics::EntityShader::EntityShader() :
    ShaderSystem("Entity"),
    _projectionLocation(-1),
    _viewLocation(-1),
    _viewPositionLocation(-1),
    _worldTransformationLocation(-1),
    _normalTransformationLocation(-1),

    _directionalLightsCountLocation(-1),
    _pointLightsCountLocation(-1),
    _flashLightEnabledLocation(-1),

    _fogEnabledLocation(-1),
    _fogDensityLocation(-1),
    _fogGradientLocation(-1),
    _fogColorLocation(-1),

    _materialColorLocation(-1),
    _materialReflectivityLocation(-1),
    _materialSpecularLocation(-1),
    _materialShininessLocation(-1),

    _deformationFactorLocation(-1),

    _fogEnabled(false)
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
    this->InitializeBoolLocation("clippingPlane.enabled", true, this->_clippingPlaneLocation.enabled);
    this->InitializeVector4fLocation("clippingPlane.plane", Math::Vector4f(0.0f, -1.0f, 0.0f, 0.5f), this->_clippingPlaneLocation.plane);

    // Setup directional lights
    this->InitializeIntLocation("directionalLightsCount", 0, this->_directionalLightsCountLocation);
    for (int index = 0; index < MAX_DIRECTIONAL_LIGHT_COUNT; index++)
    {
        this->InitializeVector3fLocation("directionalLights[" + std::to_string(index) + "].direction",
                                         Math::Vector3f(0.0f, -1.0f, 0.0f),
                                         this->_directionalLightsLocations[index].direction);
        this->InitializeVector3fLocation("directionalLights[" + std::to_string(index) + "].diffuse",
                                         Math::Vector3f(0.5f),
                                         this->_directionalLightsLocations[index].diffuse);
        this->InitializeFloatLocation("directionalLights[" + std::to_string(index) + "].intensity",
                                      1.0f,
                                      this->_directionalLightsLocations[index].intensity);
        this->InitializeFloatLocation("directionalLights[" + std::to_string(index) + "].specular",
                                      1.0f,
                                      this->_directionalLightsLocations[index].specular);
    }

    // Setup point lights
    this->InitializeIntLocation("pointLightsCount", 0, this->_pointLightsCountLocation);
    for (int index = 0; index < MAX_POINT_LIGHT_COUNT; index++)
    {
        this->InitializeVector3fLocation("pointLights[" + std::to_string(index) + "].position",
                                         Math::Vector3f(0.0f),
                                         this->_pointLightsLocations[index].position);
        this->InitializeVector3fLocation("pointLights[" + std::to_string(index) + "].attenuation",
                                         Math::Vector3f(1.0f, 0.0f, 0.0f),
                                         this->_pointLightsLocations[index].attenuation);
        this->InitializeVector3fLocation("pointLights[" + std::to_string(index) + "].diffuse",
                                         Math::Vector3f(1.0f),
                                         this->_pointLightsLocations[index].diffuse);
        this->InitializeFloatLocation("pointLights[" + std::to_string(index) + "].specular",
                                      1.0f,
                                      this->_pointLightsLocations[index].specular);
    }

    // Setup flash light
    this->InitializeBoolLocation("flashLightEnabled", false, this->_flashLightEnabledLocation);
    this->InitializeVector3fLocation("flashLight.position", Math::Vector3f(0.0f), this->_flashLightLocation.position);
    this->InitializeVector3fLocation("flashLight.direction", Math::Vector3f(0.0f, -1.0f, 0.0f), this->_flashLightLocation.direction);
    this->InitializeFloatLocation("flashLight.cutOff", 0.965926f, this->_flashLightLocation.cutOff);           // cosine 15 degrees
    this->InitializeFloatLocation("flashLight.outerCutOff", 0.951056f, this->_flashLightLocation.outerCutOff); // cosine 18 degrees
    this->InitializeVector3fLocation("flashLight.diffuse", Math::Vector3f(1.0f), this->_flashLightLocation.diffuse);
    this->InitializeFloatLocation("flashLight.specular", 1.0f, this->_flashLightLocation.specular);

    // Setup fog
    this->InitializeBoolLocation("fog.enabled", this->_fogEnabled, this->_fogEnabledLocation);
    this->InitializeFloatLocation("fog.density", 0.0175f, this->_fogDensityLocation);
    this->InitializeFloatLocation("fog.gradient", 7.5f, this->_fogGradientLocation);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.2f, 0.325f, 0.375f), this->_fogColorLocation);

    // Setup material
    this->InitializeVector3fLocation("material.color", Math::Vector3f(0.85f), this->_materialColorLocation);
    this->InitializeFloatLocation("material.reflectivity", 0.0f, this->_materialReflectivityLocation);
    this->InitializeFloatLocation("material.specular", 0.5f, this->_materialSpecularLocation);
    this->InitializeFloatLocation("material.shininess", 25.0f, this->_materialShininessLocation);

    // Setup texture mappers
    this->InitializeBoolLocation("diffuseSampler.enabled", false, this->_diffuseSamplerLocation.enabled);
    this->InitializeBoolLocation("normalSampler.enabled", false, this->_normalSamplerLocation.enabled);
    this->InitializeBoolLocation("specularSampler.enabled", false, this->_specularSamplerLocation.enabled);
    this->InitializeBoolLocation("skyboxSampler.enabled", false, this->_skyboxSamplerLocation.enabled);

    this->InitializeIntLocation("diffuseSampler.texture", EnumToValue(Texture::Bank::Diffuse), this->_diffuseSamplerLocation.texture);
    this->InitializeIntLocation("normalSampler.texture", EnumToValue(Texture::Bank::Normal), this->_normalSamplerLocation.texture);
    this->InitializeIntLocation("specularSampler.texture", EnumToValue(Texture::Bank::Specular), this->_specularSamplerLocation.texture);
    this->InitializeIntLocation("skyboxSampler.texture", EnumToValue(Texture::Bank::Skybox), this->_skyboxSamplerLocation.texture);

    // Setup deformation factor
    this->InitializeFloatLocation("deformationFactor", 0.0f, this->_deformationFactorLocation);
}

void Graphics::EntityShader::LoadProjection(const std::shared_ptr<const Projection>& projection) const
{
    this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::EntityShader::EnableClippingPlane(const Math::Vector4f& plane) const
{
    glEnable(GL_CLIP_DISTANCE0);
    this->LoadBool(this->_clippingPlaneLocation.enabled, true);
    this->LoadVector4f(this->_clippingPlaneLocation.plane, plane);
}

void Graphics::EntityShader::DisableClippingPlane() const
{
    this->LoadBool(this->_clippingPlaneLocation.enabled, false);
    glDisable(GL_CLIP_DISTANCE0);
}

void Graphics::EntityShader::LoadCamera(const std::shared_ptr<Camera>& camera) const
{
    _Assert(camera)

    const Math::Matrix4f viewMatrix = Math::ViewMatrix3D(camera->GetPosition(), camera->GetRotation());
    this->LoadMatrix4f(this->_viewLocation, viewMatrix);
    this->LoadVector3f(this->_viewPositionLocation, camera->GetPosition());
}

void Graphics::EntityShader::LoadDirectionalLights(const std::vector<std::shared_ptr<DirectionalLight>>& lights) const
{
    const int lightsCount = static_cast<int>(lights.size());
    _Assert(EntityShader::MAX_DIRECTIONAL_LIGHT_COUNT > lightsCount - 1)
    this->LoadInt(this->_directionalLightsCountLocation, lightsCount);

    int index = 0;
    for (const auto& light : lights)
    {
        this->LoadDirectionalLight(index, light);
        index++;
    }
}

void Graphics::EntityShader::LoadDirectionalLight(const int index, const std::shared_ptr<DirectionalLight>& light) const
{
    _Assert(EntityShader::MAX_DIRECTIONAL_LIGHT_COUNT > index)

    const Math::Vector3f diffuseColor = light->GetIntensity() * light->GetColor();

    this->LoadVector3f(this->_directionalLightsLocations[index].direction, light->GetDirection());
    this->LoadVector3f(this->_directionalLightsLocations[index].diffuse, diffuseColor);
    this->LoadFloat(this->_directionalLightsLocations[index].intensity, light->GetIntensity());
    this->LoadFloat(this->_directionalLightsLocations[index].specular, 1.0f);
}

void Graphics::EntityShader::LoadPointLights(const std::vector<std::shared_ptr<PointLight>>& lights) const
{
    const int lightsCount = static_cast<int>(lights.size());
    _Assert(EntityShader::MAX_POINT_LIGHT_COUNT > lightsCount - 1)
    this->LoadInt(this->_pointLightsCountLocation, lightsCount);

    int index = 0;
    for (const auto& light : lights)
    {
        this->LoadPointLight(index, light);
        index++;
    }
}

void Graphics::EntityShader::LoadPointLight(const int index, const std::shared_ptr<PointLight>& light) const
{
    _Assert(EntityShader::MAX_POINT_LIGHT_COUNT > index)
    const Math::Vector3f diffuseColor = light->GetIntensity() * light->GetColor();
    this->LoadVector3f(this->_pointLightsLocations[index].position, light->GetPosition());
    this->LoadVector3f(this->_pointLightsLocations[index].diffuse, diffuseColor);
    this->LoadFloat(this->_pointLightsLocations[index].specular, 1.0f);
    this->LoadVector3f(this->_pointLightsLocations[index].attenuation, light->GetAttenuation());
}

void Graphics::EntityShader::LoadFlashLight(const std::shared_ptr<SpotLight>& light) const
{
    this->LoadVector3f(this->_flashLightLocation.position, light->GetPosition());
    this->LoadVector3f(this->_flashLightLocation.direction, light->GetDirection());
    this->LoadFloat(this->_flashLightLocation.cutOff, light->GetCosineCutOffAngle());
    this->LoadFloat(this->_flashLightLocation.outerCutOff, light->GetCosineOuterCutOffAngle());
    this->LoadVector3f(this->_flashLightLocation.diffuse, light->GetColor());
    this->LoadFloat(this->_flashLightLocation.specular, 1.0f);
}

void Graphics::EntityShader::LoadFlashLightEnabled(const bool enabled) const
{
    this->LoadBool(this->_flashLightEnabledLocation, enabled);
}

void Graphics::EntityShader::LoadFog(const Math::Vector3f& color, const float density, const float gradient) const
{
    this->LoadVector3f(this->_fogColorLocation, color);
    this->LoadFloat(this->_fogDensityLocation, density);
    this->LoadFloat(this->_fogGradientLocation, gradient);
}

void Graphics::EntityShader::LoadFogEnabled(const bool enabled)
{
    if (this->_fogEnabled != enabled)
    {
        this->_fogEnabled = enabled;
        this->LoadBool(this->_fogEnabledLocation, this->_fogEnabled);
    }
}

void Graphics::EntityShader::LoadWorldTransformation(const Math::Matrix4f& transformationMatrix) const
{
    this->LoadMatrix4f(this->_worldTransformationLocation, transformationMatrix);
    this->LoadMatrix3f(this->_normalTransformationLocation, transpose(inverse(transformationMatrix)));
}

void Graphics::EntityShader::LoadMaterial(const Material& material) const
{
    this->LoadVector3f(this->_materialColorLocation, material.GetColor());
    this->LoadFloat(this->_materialReflectivityLocation, material.GetReflectivity());
    this->LoadFloat(this->_materialSpecularLocation, material.GetSpecular());
    this->LoadFloat(this->_materialShininessLocation, material.GetShininess());
}

void Graphics::EntityShader::LoadHasDiffuseMap(const bool hasDiffuseMap) const
{
    this->LoadBool(this->_diffuseSamplerLocation.enabled, hasDiffuseMap);
}

void Graphics::EntityShader::LoadHasNormalMap(const bool hasNormalMap) const
{
    this->LoadBool(this->_normalSamplerLocation.enabled, hasNormalMap);
}

void Graphics::EntityShader::LoadHasSpecularMap(const bool hasSpecularMap) const
{
    this->LoadBool(this->_specularSamplerLocation.enabled, hasSpecularMap);
}

void Graphics::EntityShader::LoadHasSkyboxMap(const bool hasSkyboxMap) const
{
    this->LoadBool(this->_skyboxSamplerLocation.enabled, hasSkyboxMap);
}

void Graphics::EntityShader::LoadDeformationFactor(const float deformationFactor) const
{
    this->LoadFloat(this->_deformationFactorLocation, deformationFactor);
}
