// ----------------------------------------------------------------------------------------
//  \file       RenderBuffer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/RenderBuffer.h"

GLuint Graphics::RenderBuffer::_boundRenderBuffer = 0;

Graphics::RenderBuffer::RenderBuffer() :
    _state(State::Initial),
    _glRenderBuffer(0),
    _format(GL_DEPTH_COMPONENT),
    _width(1024),
    _height(1024)
{
    glGenRenderbuffers(1, &this->_glRenderBuffer);
}

Graphics::RenderBuffer::~RenderBuffer()
{
    this->Unbind();
    glDeleteRenderbuffers(1, &this->_glRenderBuffer);
}

void Graphics::RenderBuffer::Storage(const GLenum format, const unsigned width, const unsigned height)
{
    _Assert(State::Initial == this->_state)
    _Assert(this->IsBound())
    this->_format = format;
    this->_width = width;
    this->_height = height;
    glRenderbufferStorage(GL_RENDERBUFFER, this->_format, this->_width, this->_height);
    this->_state = State::Ready;
}

void Graphics::RenderBuffer::Bind() const
{
    if (!this->IsBound())
    {
        glBindRenderbuffer(GL_RENDERBUFFER, this->_glRenderBuffer);
        _boundRenderBuffer = this->_glRenderBuffer;
    }
}

void Graphics::RenderBuffer::Unbind() const
{
    if (this->IsBound())
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        _boundRenderBuffer = 0;
    }
}
