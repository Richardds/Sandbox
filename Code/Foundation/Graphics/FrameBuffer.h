#pragma once

#include "Core.h"
#include "RenderBuffer.h"

namespace Graphics
{

    class FrameBuffer
    {
    public:
        FrameBuffer(GLenum attachment);
        virtual ~FrameBuffer();
        GLenum GetAttachment() const;
        void Bind();
        void Attach(std::shared_ptr<RenderBuffer> renderBuffer);
        bool IsBound() const;
        void Unbind();
        GLuint GetGlFrameBuffer() const;

        static GLuint GetBound(GLenum target);

    private:
        GLuint _glFrameBuffer;
        GLenum _attachment;

        static GLuint _boundFrameBuffer;
    };

    inline GLenum Graphics::FrameBuffer::GetAttachment() const
    {
        return this->_attachment;
    }

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
