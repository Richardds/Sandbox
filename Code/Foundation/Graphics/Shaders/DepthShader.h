// ----------------------------------------------------------------------------------------
//  \file       DepthShader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Shaders/ShaderSystem.h"

namespace Graphics
{
    /// Shader system usually used for creating scene depth buffer
    /// (currently unused)
    class DepthShader : public ShaderSystem
    {
    public:
        DepthShader();
        void InitializeUniformVariables() override;
        void LoadProjection(const Math::Matrix4f& transformation) const;

    private:
        GLint _projectionPosition;
    };
}
