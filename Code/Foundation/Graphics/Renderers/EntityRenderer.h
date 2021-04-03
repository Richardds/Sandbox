// ----------------------------------------------------------------------------------------
//  \file       EntityRenderer.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Light/DirectionalLight.h"
#include "Game/Scene/Object/Entity.h"
#include "Game/Scene/Light/PointLight.h"
#include "Game/Scene/Object/Skybox.h"
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
                   const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights,
                   const std::shared_ptr<SpotLight>& flashLight) const;
        void Render(const std::shared_ptr<Entity>& entity) const;
    };
}
