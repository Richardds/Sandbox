// ----------------------------------------------------------------------------------------
//  \file       TextShader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Shaders/ShaderSystem.h"

namespace Graphics
{
    /// Shader system used for drawing text
    class EXPORT TextShader : public ShaderSystem
    {
    public:
        TextShader();
        virtual ~TextShader() = default;

        void InitializeUniformVariables() override;
        void LoadTransformation(const Math::Matrix3f& transformation) const;
        void LoadColor(const Math::Vector4f& color) const;

    private:
        GLint _transformationLocation;
        GLint _fontMapSamplerLocation;
        GLint _colorLocation;
    };
}
