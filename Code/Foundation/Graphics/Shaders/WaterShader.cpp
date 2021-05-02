// ----------------------------------------------------------------------------------------
//  \file       WaterShader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Shaders/WaterShader.h"
#include "Core/Debug.h"
#include "Core/Types.h"
#include "Graphics/Texture.h"
#include "Math/MathUtils.h"

Graphics::WaterShader::WaterShader() :
    ShaderSystem("Water"),
    _projectionLocation(-1),
    _viewLocation(-1),
    _viewPositionLocation(-1),
    _worldTransformationLocation(-1),
    _normalTransformationLocation(-1),

    _textureTilingLocation(-1),
    _wavesEnabledLocation(-1),
    _distortionOffsetLocation(-1),
    _reflectionSamplerLocation(-1),
    _refractionSamplerLocation(-1),

    _directionalLightsCountLocation(-1),
    _pointLightsCountLocation(-1),
    _flashLightEnabledLocation(-1),

    _fogEnabledLocation(-1),
    _fogColorLocation(-1),
    _fogDensityLocation(-1),
    _fogGradientLocation(-1),

    _fogEnabled(false)
{
}

void Graphics::WaterShader::InitializeUniformVariables()
{
    // Setup transformations
    this->InitializeMatrix4fLocation("projection", Math::Matrix4f(1.0f), this->_projectionLocation);
    this->InitializeMatrix4fLocation("view", Math::Matrix4f(1.0f), this->_viewLocation);
    this->InitializeVector3fLocation("viewPosition", Math::Vector3f(1.0f), this->_viewPositionLocation);
    this->InitializeMatrix4fLocation("worldTransformation", Math::Matrix4f(1.0f), this->_worldTransformationLocation);
    this->InitializeMatrix3fLocation("normalTransformation", Math::Matrix4f(1.0f), this->_normalTransformationLocation);

    // Setup texture mappers
    this->InitializeFloatLocation("textureTiling", 1.0f, this->_textureTilingLocation);
    this->InitializeBoolLocation("normalSampler.enabled", false, this->_normalSamplerLocation.enabled);
    this->InitializeIntLocation("normalSampler.texture", EnumToValue(Texture::Bank::Normal),
                                this->_normalSamplerLocation.texture);
    this->InitializeBoolLocation("distortionSampler.enabled", false, this->_distortionSamplerLocation.enabled);
    this->InitializeIntLocation("distortionSampler.texture", EnumToValue(Texture::Bank::Distortion),
                                this->_distortionSamplerLocation.texture);
    this->InitializeBoolLocation("wavesEnabled", false, this->_wavesEnabledLocation);
    this->InitializeFloatLocation("distortionOffset", 0.0f, this->_distortionOffsetLocation);
    this->InitializeIntLocation("reflectionSampler", EnumToValue(Texture::Bank::Reflection),
                                this->_reflectionSamplerLocation);
    this->InitializeIntLocation("refractionSampler", EnumToValue(Texture::Bank::Refraction),
                                this->_refractionSamplerLocation);

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
    this->InitializeFloatLocation("flashLight.cutOff", 0.965926f, this->_flashLightLocation.cutOff); // cosine 15 degrees
    this->InitializeFloatLocation("flashLight.outerCutOff", 0.951056f, this->_flashLightLocation.outerCutOff); // cosine 18 degrees
    this->InitializeVector3fLocation("flashLight.diffuse", Math::Vector3f(1.0f), this->_flashLightLocation.diffuse);
    this->InitializeFloatLocation("flashLight.specular", 1.0f, this->_flashLightLocation.specular);

    // Setup fog
    this->InitializeBoolLocation("fog.enabled", this->_fogEnabled, this->_fogEnabledLocation);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.2f, 0.325f, 0.375f), this->_fogColorLocation);
    this->InitializeFloatLocation("fog.density", 0.0175f, this->_fogDensityLocation);
    this->InitializeFloatLocation("fog.gradient", 7.5f, this->_fogGradientLocation);
}

void Graphics::WaterShader::LoadProjection(const std::shared_ptr<const Projection>& projection) const
{
    this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::WaterShader::LoadCamera(const std::shared_ptr<Camera>& camera) const
{
    _Assert(camera)

    const Math::Matrix4f viewMatrix = Math::ViewMatrix3D(camera->GetPosition(), camera->GetRotation());
    this->LoadMatrix4f(this->_viewLocation, viewMatrix);
    this->LoadVector3f(this->_viewPositionLocation, camera->GetPosition());
}

void Graphics::WaterShader::LoadDirectionalLights(const std::vector<std::shared_ptr<DirectionalLight>>& lights) const
{
    const int lightsCount = static_cast<int>(lights.size());
    _Assert(WaterShader::MAX_DIRECTIONAL_LIGHT_COUNT > lightsCount - 1)
    this->LoadInt(this->_directionalLightsCountLocation, lightsCount);

    int index = 0;
    for (const auto& light : lights)
    {
        this->LoadDirectionalLight(index, light);
        index++;
    }
}

void Graphics::WaterShader::LoadDirectionalLight(const int index, const std::shared_ptr<DirectionalLight>& light) const
{
    _Assert(WaterShader::MAX_DIRECTIONAL_LIGHT_COUNT > index)
    this->LoadVector3f(this->_directionalLightsLocations[index].direction, light->GetDirection());
    this->LoadVector3f(this->_directionalLightsLocations[index].diffuse, light->GetColor());
    this->LoadFloat(this->_directionalLightsLocations[index].intensity, light->GetIntensity());
    this->LoadFloat(this->_directionalLightsLocations[index].specular, 1.0f);
}

void Graphics::WaterShader::LoadPointLights(const std::vector<std::shared_ptr<PointLight>>& lights) const
{
    const int lightsCount = static_cast<int>(lights.size());
    _Assert(WaterShader::MAX_POINT_LIGHT_COUNT > lightsCount - 1)
    this->LoadInt(this->_pointLightsCountLocation, lightsCount);

    int index = 0;
    for (const auto& light : lights)
    {
        this->LoadPointLight(index, light);
        index++;
    }
}

void Graphics::WaterShader::LoadPointLight(const int index, const std::shared_ptr<PointLight>& light) const
{
    _Assert(WaterShader::MAX_POINT_LIGHT_COUNT > index)
    const Math::Vector3f diffuseColor = light->GetIntensity() * light->GetColor();
    this->LoadVector3f(this->_pointLightsLocations[index].position, light->GetPosition());
    this->LoadVector3f(this->_pointLightsLocations[index].diffuse, diffuseColor);
    this->LoadFloat(this->_pointLightsLocations[index].specular, 1.0f);
    this->LoadVector3f(this->_pointLightsLocations[index].attenuation, light->GetAttenuation());
}

void Graphics::WaterShader::LoadFlashLight(const std::shared_ptr<SpotLight>& light) const
{
    this->LoadVector3f(this->_flashLightLocation.position, light->GetPosition());
    this->LoadVector3f(this->_flashLightLocation.direction, light->GetDirection());
    this->LoadFloat(this->_flashLightLocation.cutOff, light->GetCosineCutOffAngle());
    this->LoadFloat(this->_flashLightLocation.outerCutOff, light->GetCosineOuterCutOffAngle());
    this->LoadVector3f(this->_flashLightLocation.diffuse, light->GetColor());
    this->LoadFloat(this->_flashLightLocation.specular, 1.0f);
}

void Graphics::WaterShader::LoadFlashLightEnabled(const bool enabled) const
{
    this->LoadBool(this->_flashLightEnabledLocation, enabled);
}

void Graphics::WaterShader::LoadFog(const Math::Vector3f& color, const float density, const float gradient) const
{
    this->LoadVector3f(this->_fogColorLocation, color);
    this->LoadFloat(this->_fogDensityLocation, density);
    this->LoadFloat(this->_fogGradientLocation, gradient);
}

void Graphics::WaterShader::LoadFogEnabled(const bool enabled)
{
    if (this->_fogEnabled != enabled)
    {
        this->_fogEnabled = enabled;
        this->LoadBool(this->_fogEnabledLocation, this->_fogEnabled);
    }
}

void Graphics::WaterShader::LoadWorldTransformation(const Math::Matrix4f& transformationMatrix) const
{
    this->LoadMatrix4f(this->_worldTransformationLocation, transformationMatrix);
    this->LoadMatrix3f(this->_normalTransformationLocation, transpose(inverse(transformationMatrix)));
}

void Graphics::WaterShader::LoadTextureTiling(const float tiling) const
{
    this->LoadFloat(this->_textureTilingLocation, tiling);
}

void Graphics::WaterShader::LoadWavesEnabled(const bool wavesEnabled) const
{
    this->LoadBool(this->_wavesEnabledLocation, wavesEnabled);
}

void Graphics::WaterShader::LoadHasNormalMap(const bool hasNormalMap) const
{
    this->LoadBool(this->_normalSamplerLocation.enabled, hasNormalMap);
}

void Graphics::WaterShader::LoadHasDistortionMap(const bool hasDistortionMap) const
{
    this->LoadBool(this->_distortionSamplerLocation.enabled, hasDistortionMap);
}

void Graphics::WaterShader::LoadDistortionOffset(const float offset) const
{
    this->LoadFloat(this->_distortionOffsetLocation, offset);
}
