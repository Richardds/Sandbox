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
    _viewInverseLocation(-1),
    _waterTransformationLocation(-1),
    _normalTransformationLocation(-1),

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
    this->InitializeMatrix4fLocation("viewInverse", Math::Matrix4f(1.0f), this->_viewInverseLocation);
    this->InitializeMatrix4fLocation("worldTransformation", Math::Matrix4f(1.0f), this->_waterTransformationLocation);
    this->InitializeMatrix3fLocation("normalTransformation", Math::Matrix4f(1.0f), this->_normalTransformationLocation);

    // Setup texture mappers
    this->InitializeIntLocation("reflectionSampler", EnumToValue(Texture::Bank::REFLECTION), this->_reflectionSamplerLocation);
    this->InitializeIntLocation("refractionSampler", EnumToValue(Texture::Bank::REFRACTION), this->_refractionSamplerLocation);

    // Setup sun
    this->InitializeVector3fLocation("sun.direction", Math::Vector3f(-1.0f, -1.0f, 0.0f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.ambient", Math::Vector3f(0.05f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.diffuse", Math::Vector3f(0.15f), this->_sunLocation.direction);
    this->InitializeVector3fLocation("sun.specular", Math::Vector3f(0.1f), this->_sunLocation.direction);

    // Setup fog
    this->InitializeFloatLocation("fog.density", 0.0175f, this->_fogDensityLocation);
    this->InitializeFloatLocation("fog.gradient", 7.5f, this->_fogGradientLocation);
    this->InitializeVector3fLocation("fog.color", Math::Vector3f(0.0f), this->_fogColorLocation);
}

void Graphics::WaterShader::LoadProjection(std::shared_ptr<const Projection> projection)
{
    this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::WaterShader::LoadView(const std::shared_ptr<Graphics::Camera>& view)
{
    _assert(view);

    this->_viewMatrix = Math::ViewMatrix(view->getPosition(), view->getRotationX(), view->getRotationY());
    this->LoadMatrix4f(this->_viewLocation, this->_viewMatrix);
    this->LoadMatrix4f(this->_viewInverseLocation, glm::inverse(this->_viewMatrix));
}

void Graphics::WaterShader::LoadSun(std::shared_ptr<Sun> sun)
{
    Math::Vector3f diffuse = sun->GetIntensity() * sun->GetColor();
    this->LoadVector3f(this->_sunLocation.direction, sun->GetDirection());
    this->LoadVector3f(this->_sunLocation.direction, diffuse / 3.0f);
    this->LoadVector3f(this->_sunLocation.direction, diffuse);
    this->LoadVector3f(this->_sunLocation.direction, diffuse / 15.0f);
}

void Graphics::WaterShader::LoadFog(float density, float gradient)
{
    this->LoadFloat(this->_fogDensityLocation, density);
    this->LoadFloat(this->_fogGradientLocation, gradient);
}

void Graphics::WaterShader::LoadWorldTransformation(const Math::Matrix4f& transformationMatrix)
{
    ShaderProgram::LoadMatrix4f(this->_waterTransformationLocation, transformationMatrix);
    ShaderProgram::LoadMatrix3f(this->_normalTransformationLocation, glm::transpose(glm::inverse(transformationMatrix)));
}
