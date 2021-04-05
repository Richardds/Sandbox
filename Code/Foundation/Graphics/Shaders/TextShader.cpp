// ----------------------------------------------------------------------------------------
//  \file       TextShader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Shaders/TextShader.h"


#include "Core/Types.h"
#include "Graphics/Texture.h"

Graphics::TextShader::TextShader() :
    ShaderSystem("Text"),
    _transformationLocation(-1),
    _fontMapSamplerLocation(-1),
    _colorLocation(-1)
{
}

void Graphics::TextShader::InitializeUniformVariables()
{
    // Setup transformations
    this->InitializeMatrix3fLocation("transformation", Math::Matrix3f(1.0f), this->_transformationLocation);

    // Setup font mask mapper
    this->InitializeIntLocation("fontMapSampler", EnumToValue(Texture::Bank::Font), this->_fontMapSamplerLocation);

    // Color
    this->InitializeVector4fLocation("color", Math::Vector4f(1.0f), this->_colorLocation);
}

void Graphics::TextShader::LoadTransformation(const Math::Matrix3f& transformation) const
{
    this->LoadMatrix3f(this->_transformationLocation, transformation);
}

void Graphics::TextShader::LoadColor(const Math::Vector4f& color) const
{
    this->LoadVector4f(this->_colorLocation, color);
}
