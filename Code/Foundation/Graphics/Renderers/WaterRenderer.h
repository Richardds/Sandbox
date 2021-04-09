// ----------------------------------------------------------------------------------------
//  \file       WaterRenderer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Light/DirectionalLight.h"
#include "Game/Scene/Object/Water.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Shaders/WaterShader.h"

namespace Graphics
{
    /// Renderer which renders water tiles
    class EXPORT WaterRenderer : public Renderer<WaterShader>
    {
    public:
        /// Water reflection and refraction frame buffer sizes
        const unsigned int TEXTURE_SIZE = 2048;

        WaterRenderer() = default;
        virtual ~WaterRenderer() = default;

        bool Setup(const std::shared_ptr<const Projection>& projection);
        void Begin(const std::shared_ptr<Camera>& camera,
                   const std::shared_ptr<DirectionalLight>& sun,
                   const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights,
                   const std::shared_ptr<SpotLight>& flashLight) const;
        void RenderToReflectionBuffer(const std::function<void()>& renderFunction) const;
        void RenderToRefractionBuffer(const std::function<void()>& renderFunction) const;
        void Render(const std::shared_ptr<Water>& water) const;

    private:
        std::shared_ptr<FrameBuffer> _reflectionFrameBuffer;
        std::shared_ptr<Texture> _reflectionTexture;
        std::shared_ptr<RenderBuffer> _reflectionDepthBuffer;
        std::shared_ptr<FrameBuffer> _refractionFrameBuffer;
        std::shared_ptr<Texture> _refractionTexture;
        std::shared_ptr<RenderBuffer> _refractionDepthBuffer;
    };
}
