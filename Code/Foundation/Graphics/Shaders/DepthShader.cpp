#include "DepthShader.h"

Graphics::DepthShader::DepthShader() :
	ShaderSystem("Depth"),
	_transformationPosition(-1)
{
}

void Graphics::DepthShader::InitializeUniformVariables()
{
	this->InitializeMatrix4fLocation("transformation", Math::Matrix4f(1.0f), this->_transformationPosition);
}

void Graphics::DepthShader::LoadTransformation(const Math::Matrix4f& transformation)
{
	this->LoadMatrix4f(this->_transformationPosition, transformation);
}
