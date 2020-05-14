#pragma once

#include <functional>

#include "../Shaders/HUDShader.h"
#include "../FrameBuffer.h"
#include "../Texture.h"
#include "../Mesh.h"

namespace Graphics
{

    class HUDRenderer
    {
    public:
        enum class State {
            INITIAL,
            READY
        };

        const unsigned int TEXTURE_SIZE = 512;

        HUDRenderer();
        virtual ~HUDRenderer();
        bool Setup(std::shared_ptr<const Projection> projection);
        void Begin(const Math::Vector3f& position, float height);
        void RenderToMapBuffer(const std::function<void()>& renderFunction);
        void Render(const Math::Vector2f& screenPosition);

    private:
        State _state;
        std::shared_ptr<HUDShader> _shader;
        std::shared_ptr<Mesh> _mapMesh;
        std::shared_ptr<FrameBuffer> _mapFrameBuffer;
        std::shared_ptr<Texture> _mapTexture;
    };

}
