// ----------------------------------------------------------------------------------------
//  \file       TextShader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Shaders/ShaderSystem.h"

namespace Graphics
{
    /// Shader system used for drawing glyphs
    class TextShader : public ShaderSystem
    {
    public:
        TextShader();

        void InitializeUniformVariables() override;
        void LoadScreenResolution(const Math::Vector2f& resolution) const;

    private:
        GLint _screenResolutionLocation;
        GLint _glyphsMapSamplerLocation;
    };
}
