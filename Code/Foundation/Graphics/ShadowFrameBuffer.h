#pragma once

#include "FrameBuffer.h"
#include "Texture.h"
namespace Graphics
{

    class ShadowFrameBuffer : public FrameBuffer
    {
    public:
        ShadowFrameBuffer();
        virtual ~ShadowFrameBuffer();
        std::shared_ptr<Texture> CreateDepthBufferAttachment(unsigned int width, unsigned int height);
    };

}
