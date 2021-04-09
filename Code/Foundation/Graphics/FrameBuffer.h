// ----------------------------------------------------------------------------------------
//  \file       FrameBuffer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

#include "Texture.h"
#include "Graphics/RenderBuffer.h"

namespace Graphics
{
    /// Low-level OpenGL frame buffer object wrapper
    class EXPORT FrameBuffer
    {
    public:
        FrameBuffer();
        virtual ~FrameBuffer();

        void Bind() const;
        void Activate(unsigned int width, unsigned int height) const;
        void Clear() const;
        void Deactivate() const;
        void AttachTexture(const std::shared_ptr<Texture>& texture, unsigned int width, unsigned int height) const;
        void AttachDepthTexture(const std::shared_ptr<Texture>& texture, unsigned int width, unsigned int height) const;
        void AttachDepthBuffer(const std::shared_ptr<RenderBuffer>& renderBuffer) const;
        bool IsBound() const;
        void Unbind() const;
        GLuint GetGlFrameBuffer() const;

        static GLuint GetBound(GLenum target);

    private:
        GLuint _glFrameBuffer;

        static GLuint _boundFrameBuffer;
    };

    inline bool FrameBuffer::IsBound() const
    {
        return _boundFrameBuffer == this->_glFrameBuffer;
    }

    inline GLuint FrameBuffer::GetGlFrameBuffer() const
    {
        return this->_glFrameBuffer;
    }

    inline GLuint FrameBuffer::GetBound(GLenum target)
    {
        return _boundFrameBuffer;
    }
}
