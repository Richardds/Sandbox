// ----------------------------------------------------------------------------------------
//  \file       TextShader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Shaders/TextShader.h"


#include "Core/Types.h"
#include "Graphics/Texture.h"

Graphics::TextShader::TextShader() :
    ShaderSystem("Glyph"),
    _screenResolutionLocation(-1),
    _glyphsMapSamplerLocation(-1)
{
}

void Graphics::TextShader::InitializeUniformVariables()
{
    // Setup transformations
    this->InitializeVector2fLocation("screenResolution", Math::Vector2f(1280.0f, 720.0f), this->_screenResolutionLocation);

    // Setup glyphs texture mapper
    this->InitializeIntLocation("glyphsMapSampler", EnumToValue(Texture::Bank::Font), this->_glyphsMapSamplerLocation);
}

void Graphics::TextShader::LoadScreenResolution(const Math::Vector2f& resolution) const
{
    this->LoadVector2f(this->_screenResolutionLocation, resolution);
}
