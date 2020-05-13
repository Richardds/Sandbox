#pragma once

#include <functional>

#include "../Shaders/WaterShader.h"
#include "../../Game/Scene/DirectionalLight.h"
#include "../../Game/Scene/Water.h"
#include "../FrameBuffer.h"
#include "../RenderBuffer.h"
#include "../Texture.h"

namespace Graphics
{

    class WaterRenderer
    {
    public:
        enum class State {
            INITIAL,
            READY
        };

        const unsigned int TEXTURE_SIZE = 2048;

        WaterRenderer();
        virtual ~WaterRenderer();
        bool Setup(std::shared_ptr<const Projection> projection);
        void Begin(std::shared_ptr<Camera> camera, std::shared_ptr<DirectionalLight> sun);
        void RenderToReflectionBuffer(const std::function<void()>& renderFunction);
        void RenderToRefractionBuffer(const std::function<void()>& renderFunction);
        void Render(std::shared_ptr<Water> water);

    private:
        State _state;
        std::shared_ptr<WaterShader> _shader;

        std::shared_ptr<FrameBuffer> _reflectionFrameBuffer;
        std::shared_ptr<Texture> _reflectionTexture;
        std::shared_ptr<RenderBuffer> _reflectionRenderBuffer;

        std::shared_ptr<FrameBuffer> _refractionFrameBuffer;
        std::shared_ptr<Texture> _refractionTexture;
        std::shared_ptr<RenderBuffer> _refractionRenderBuffer;
    };

}
