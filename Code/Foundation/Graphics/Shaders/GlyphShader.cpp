// ----------------------------------------------------------------------------------------
//  \file       GlyphShader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Shaders/GlyphShader.h"


#include "Core/Types.h"
#include "Graphics/Texture.h"

Graphics::GlyphShader::GlyphShader() :
    ShaderSystem("Glyph"),
    _screenResolutionLocation(-1),
    _glyphsMapSamplerLocation(-1)
{
}

void Graphics::GlyphShader::InitializeUniformVariables()
{
    // Setup transformations
    this->InitializeVector2fLocation("screenResolution", Math::Vector2f(1280.0f, 720.0f), this->_screenResolutionLocation);

    // Setup glyphs texture mapper
    this->InitializeIntLocation("glyphsMapSampler", EnumToValue(Texture::Bank::Glyphs), this->_glyphsMapSamplerLocation);
}

void Graphics::GlyphShader::LoadScreenResolution(const Math::Vector2f& resolution) const
{
    this->LoadVector2f(this->_screenResolutionLocation, resolution);
}
