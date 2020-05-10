#pragma once

#include "Core.h"

namespace Graphics
{

    class RenderBuffer
    {
    public:
        RenderBuffer(GLenum format, unsigned int width, unsigned int height);
        virtual ~RenderBuffer();
        GLenum GetFormat() const;
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        void Bind();
        bool IsBound() const;
        void Unbind();
        GLuint GetGlRenderBuffer() const;

        static GLuint GetBound(GLenum target);

    private:
        GLuint _glRenderBuffer;
        GLenum _format;
        unsigned int _width;
        unsigned int _height;

        static GLuint _boundRenderBuffer;
    };

    inline GLenum Graphics::RenderBuffer::GetFormat() const
    {
        return this->_format;
    }

    inline unsigned int Graphics::RenderBuffer::GetWidth() const
    {
        return this->_width;
    }

    inline unsigned int Graphics::RenderBuffer::GetHeight() const
    {
        return this->_height;
    }

    inline bool RenderBuffer::IsBound() const
    {
        return RenderBuffer::_boundRenderBuffer == this->_glRenderBuffer;
    }

    inline GLuint RenderBuffer::GetGlRenderBuffer() const
    {
        return this->_glRenderBuffer;
    }

    inline GLuint RenderBuffer::GetBound(GLenum target)
    {
        return RenderBuffer::_boundRenderBuffer;
    }

}
