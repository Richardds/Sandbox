#include <iostream>

#include "WaterShader.h"
#include "../../Core/Types.h"
#include "../../Core/Debug.h"
#include "../../Graphics/Core.h"
#include "../../Math/Utils.h"
#include "../Texture.h"

Graphics::WaterShader::WaterShader() :
    ShaderSystem("Water"),
    _projectionLocation(-1),
    _viewLocation(-1),
    _viewPositionLocation(-1),
    _worldTransformationLocation(-1),
    _normalTransformationLocation(-1),

    _distortionOffsetLocation(-1),
    _textureTilingLocation(-1),
    _reflectionSamplerLocation(-1),
    _refractionSamplerLocation(-1),

    _fogDensityLocation(-1),
    _fogGradientLocation(-1),
    _fogColorLocation(-1),

    _viewMatrix(1.0f)
{
}

Graphics::WaterShader::~WaterShader()
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
    this->InitializeIntLocation("normalSampler.texture", EnumToValue(Texture::Bank::NORMAL), this->_normalSamplerLocation.texture);
    this->InitializeBoolLocation("distortionSampler.enabled", false, this->_distortionSamplerLocation.enabled);
    this->InitializeIntLocation("distortionSampler.texture", EnumToValue(Texture::Bank::DISTORTION), this->_distortionSamplerLocation.texture);
    this->InitializeFloatLocation("distortionOffset", 0.0f, this->_distortionOffsetLocation);
    this->InitializeIntLocation("reflectionSampler", EnumToValue(Texture::Bank::REFLECTION), this->_reflectionSamplerLocation);
    this->InitializeIntLocation("refractionSampler", EnumToValue(Texture::Bank::REFRACTION), this->_refractionSamplerLocation);

    // Setup sun
    this->InitializeVector3fLocation("sun.direction", Math::Vector3f(-1.0f, -1.0f, 0.0f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.ambient", Math::Vector3f(0.2f), this->_sunLocation.ambient);
    this->InitializeVector3fLocation("sun.diffuse", Math::Vector3f(0.5f), this->_sunLocation.diffuse);
    this->InitializeFloatLocation("sun.specular", 1.0f, this->_sunLocation.specular);

    // Setup fog
    this->InitializeFloatLocation("fog.density", 0.0175f, this->_fogDensityLocation);
    this->InitializeFloatLocation("fog.gradient", 7.5f, this->_fogGradientLocation);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.2f, 0.325f, 0.375f), this->_fogColorLocation);
}

void Graphics::WaterShader::LoadProjection(std::shared_ptr<const Projection> projection)
{
    this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::WaterShader::LoadCamera(const std::shared_ptr<Graphics::Camera>& camera)
{
    _assert(camera);

    this->_viewMatrix = Math::ViewMatrix(camera->getPosition(), camera->getRotationX(), camera->getRotationY());
    this->LoadMatrix4f(this->_viewLocation, this->_viewMatrix);
    this->LoadVector3f(this->_viewPositionLocation, camera->getPosition());
}

void Graphics::WaterShader::LoadSun(std::shared_ptr<DirectionalLight> sun)
{
    Math::Vector3f diffuseColor = sun->GetIntensity() * sun->GetColor();
    Math::Vector3f ambientColor = diffuseColor / 5.0f;

    this->LoadVector3f(this->_sunLocation.direction, sun->GetDirection());
    this->LoadVector3f(this->_sunLocation.ambient, ambientColor);
    this->LoadVector3f(this->_sunLocation.diffuse, diffuseColor);
    this->LoadFloat(this->_sunLocation.specular, 1.0f);
}

void Graphics::WaterShader::LoadFog(float density, float gradient)
{
    this->LoadFloat(this->_fogDensityLocation, density);
    this->LoadFloat(this->_fogGradientLocation, gradient);
}

void Graphics::WaterShader::LoadWorldTransformation(const Math::Matrix4f& transformationMatrix)
{
    ShaderProgram::LoadMatrix4f(this->_worldTransformationLocation, transformationMatrix);
    ShaderProgram::LoadMatrix3f(this->_normalTransformationLocation, glm::transpose(glm::inverse(transformationMatrix)));
}

void Graphics::WaterShader::LoadTextureTiling(float tiling)
{
    this->LoadFloat(this->_textureTilingLocation, tiling);
}

void Graphics::WaterShader::LoadHasNormalMap(bool hasNormalMap)
{
    ShaderProgram::LoadBool(this->_normalSamplerLocation.enabled, hasNormalMap);
}

void Graphics::WaterShader::LoadHasDistortionMap(bool hasDistortionMap)
{
    ShaderProgram::LoadBool(this->_distortionSamplerLocation.enabled, hasDistortionMap);
}

void Graphics::WaterShader::LoadDistortionOffset(float offset)
{
    this->LoadFloat(this->_distortionOffsetLocation, offset);
}
