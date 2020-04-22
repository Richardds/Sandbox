#include <iostream>

#include "UIShader.h"
#include "../../Math/Utils.h"
#include "../../Core/Debug.h"
#include "../../Graphics/Core.h"

Graphics::UIShader::UIShader() :
    ShaderSystem("UI"),
    _uiMatrixLocation(0)
{
}

Graphics::UIShader::~UIShader()
{
}

void Graphics::UIShader::Begin()
{
    this->Use();
}

void Graphics::UIShader::InitializeUniformVariables()
{
    this->_uiMatrixLocation = this->GetUniformLocation("uiMatrix");
    this->LoadMatrix4f(this->_uiMatrixLocation, Math::Matrix4f(1.0f));
}

void Graphics::UIShader::LoadUITransformation(const Math::Matrix4f& uiMatrix)
{
    this->LoadMatrix4f(this->_uiMatrixLocation, uiMatrix);
}
