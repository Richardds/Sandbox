#pragma once

#include "Core.h"
#include "RenderBuffer.h"

namespace Graphics
{

    class FrameBuffer
    {
    public:
        FrameBuffer();
        virtual ~FrameBuffer();
        void Bind();
        void Activate(unsigned int width, unsigned int height);
        void Deactivate();
        void Attach(std::shared_ptr<RenderBuffer> renderBuffer, GLenum attachment);
        bool IsBound() const;
        void Unbind();
        GLuint GetGlFrameBuffer() const;

        static GLuint GetBound(GLenum target);

    private:
        GLuint _glFrameBuffer;

        static GLuint _boundFrameBuffer;
    };

    inline bool FrameBuffer::IsBound() const
    {
        return FrameBuffer::_boundFrameBuffer == this->_glFrameBuffer;
    }

    inline GLuint FrameBuffer::GetGlFrameBuffer() const
    {
        return this->_glFrameBuffer;
    }

    inline GLuint FrameBuffer::GetBound(GLenum target)
    {
        return FrameBuffer::_boundFrameBuffer;
    }

}
