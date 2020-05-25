// ----------------------------------------------------------------------------------------
//  \file       EntityRenderer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/DirectionalLight.h"
#include "Game/Scene/Entity.h"
#include "Game/Scene/PointLight.h"
#include "Game/Scene/Skybox.h"
#include "Graphics/Projection.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Shaders/EntityShader.h"

namespace Graphics
{
    /// Renderer which renders basic models
    class EntityRenderer : public Renderer<EntityShader>
    {
    public:
        EntityRenderer() = default;

        bool Setup(const std::shared_ptr<const Projection>& projection);
        void Begin(const std::shared_ptr<Camera>& camera,
                   const std::shared_ptr<DirectionalLight>& sun,
                   const std::shared_ptr<Skybox>& skybox,
                   const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights) const;
        void Render(const std::shared_ptr<Entity>& entity) const;
    };
}
