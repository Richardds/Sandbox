// ----------------------------------------------------------------------------------------
//  \file       GlyphShader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Shaders/ShaderSystem.h"

namespace Graphics
{
    /// Shader system used for drawing glyphs
    class GlyphShader : public ShaderSystem
    {
    public:
        GlyphShader();

        void InitializeUniformVariables() override;
        void LoadScreenResolution(const Math::Vector2f& resolution) const;

    private:
        GLint _screenResolutionLocation;
        GLint _glyphsMapSamplerLocation;
    };
}
