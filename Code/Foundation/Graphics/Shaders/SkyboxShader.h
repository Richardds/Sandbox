// ----------------------------------------------------------------------------------------
//  \file       SkyboxShader.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Game/Scene/Camera.h"
#include "Graphics/Projection.h"
#include "Graphics/Shaders/ShaderSystem.h"

namespace Graphics
{
    /// Shader system used for drawing skybox
    class EXPORT SkyboxShader : public ShaderSystem
    {
    public:
        SkyboxShader();

        void InitializeUniformVariables() override;
        void LoadProjection(const std::shared_ptr<const Projection>& projection) const;
        void LoadCamera(const std::shared_ptr<Camera>& camera) const;
        void LoadDarkeningFactor(float darkeningFactor) const;

    private:
        GLint _projectionLocation;
        GLint _viewLocation;
        GLint _textureLocation;
        GLint _darkeningFactorLocation;
    };
}
