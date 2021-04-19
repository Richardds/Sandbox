// ----------------------------------------------------------------------------------------
//  \file       SkyboxRenderer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/Renderers/Renderer.h"
#include "Game/Scene/Object/Skybox.h"
#include "Game/Scene/Object/Water.h"
#include "Graphics/Shaders/SkyboxShader.h"

namespace Graphics
{
    /// Renderer which renders skybox
    class EXPORT SkyboxRenderer : public Renderer<SkyboxShader>
    {
    public:
        SkyboxRenderer() = default;

        bool Setup(const std::shared_ptr<const Projection>& projection);
        void Begin(const std::shared_ptr<Camera>& camera) const;
        void Render(const std::shared_ptr<Skybox>& skybox) const;

    private:
        std::shared_ptr<Mesh> _skyboxMesh;
    };
}
