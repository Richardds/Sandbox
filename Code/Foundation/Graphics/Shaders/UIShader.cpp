#include "UIShader.h"

Graphics::UIShader::UIShader() :
    ShaderSystem("UI"),
    _transformationLocation(0)
{
}

Graphics::UIShader::~UIShader()
{
}

void Graphics::UIShader::InitializeUniformVariables()
{
    this->_transformationLocation = this->GetUniformLocation("transformation");
    this->LoadMatrix4f(this->_transformationLocation, Math::Matrix4f(1.0f));
}

void Graphics::UIShader::LoadTransformation(const Math::Matrix4f& transformation)
{
    this->LoadMatrix4f(this->_transformationLocation, transformation);
}
