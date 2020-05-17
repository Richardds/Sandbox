#include "HUDShader.h"
#include "../Texture.h"
#include "../../Core/Types.h"
#include "../../Math/Utils.h"

Graphics::HUDShader::HUDShader() :
	ShaderSystem("HUD"),
	_aspectRatioLocation(-1),
	_screenPositionLocation(-1),
	_mapSamplerLocation(-1)
{
}

void Graphics::HUDShader::InitializeUniformVariables()
{
	this->InitializeFloatLocation("aspectRatio", 1.0f, this->_aspectRatioLocation);
	this->InitializeVector2fLocation("screenPosition", Math::Vector2f(0.0f), this->_screenPositionLocation);

	this->InitializeIntLocation("mapSampler", EnumToValue(Texture::Bank::Diffuse), this->_mapSamplerLocation);
}

void Graphics::HUDShader::LoadAspectRatio(const float aspectRatio)
{
	this->LoadFloat(this->_aspectRatioLocation, aspectRatio);
}

void Graphics::HUDShader::LoadPosition(const Math::Vector2f& position)
{
	this->LoadVector2f(this->_screenPositionLocation, position);
}
