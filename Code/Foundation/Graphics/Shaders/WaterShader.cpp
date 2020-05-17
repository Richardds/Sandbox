#include "WaterShader.h"
#include "../Texture.h"
#include "../../Core/Debug.h"
#include "../../Core/Types.h"
#include "../../Math/Utils.h"

Graphics::WaterShader::WaterShader() :
	ShaderSystem("Water"),
	_projectionLocation(-1),
	_viewLocation(-1),
	_viewPositionLocation(-1),
	_worldTransformationLocation(-1),
	_normalTransformationLocation(-1),

	_textureTilingLocation(-1),
	_distortionOffsetLocation(-1),
	_reflectionSamplerLocation(-1),
	_refractionSamplerLocation(-1),
	_depthSamplerLocation(-1),

	_fogDensityLocation(-1),
	_fogGradientLocation(-1),
	_fogColorLocation(-1),

	_viewMatrix(1.0f)
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
	this->InitializeFloatLocation("distortionOffset", 0.0f, this->_distortionOffsetLocation);
	this->InitializeIntLocation("reflectionSampler", EnumToValue(Texture::Bank::Reflection),
	                            this->_reflectionSamplerLocation);
	this->InitializeIntLocation("refractionSampler", EnumToValue(Texture::Bank::Refraction),
	                            this->_refractionSamplerLocation);
	this->InitializeIntLocation("depthSampler", EnumToValue(Texture::Bank::Depth),
		                        this->_depthSamplerLocation);

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

void Graphics::WaterShader::LoadProjection(const std::shared_ptr<const Projection>& projection) const
{
	this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::WaterShader::LoadCamera(const std::shared_ptr<Camera>& camera)
{
	_Assert(camera);

	this->_viewMatrix = Math::ViewMatrix(camera->GetPosition(), camera->GetRotationX(), camera->GetRotationY());
	this->LoadMatrix4f(this->_viewLocation, this->_viewMatrix);
	this->LoadVector3f(this->_viewPositionLocation, camera->GetPosition());
}

void Graphics::WaterShader::LoadSun(const std::shared_ptr<DirectionalLight>& sun) const
{
	const Math::Vector3f diffuseColor = sun->GetIntensity() * sun->GetColor();
	const Math::Vector3f ambientColor = diffuseColor / 5.0f;

	this->LoadVector3f(this->_sunLocation.direction, sun->GetDirection());
	this->LoadVector3f(this->_sunLocation.ambient, ambientColor);
	this->LoadVector3f(this->_sunLocation.diffuse, diffuseColor);
	this->LoadFloat(this->_sunLocation.specular, 1.0f);
}

void Graphics::WaterShader::LoadFog(const float density, const float gradient) const
{
	this->LoadFloat(this->_fogDensityLocation, density);
	this->LoadFloat(this->_fogGradientLocation, gradient);
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
