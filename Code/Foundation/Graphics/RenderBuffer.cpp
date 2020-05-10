#include "RenderBuffer.h"
#include "../Core/Types.h"

GLuint Graphics::RenderBuffer::_boundRenderBuffer = 0;

Graphics::RenderBuffer::RenderBuffer(GLenum format, unsigned int width, unsigned int height) :
	_glRenderBuffer(0),
    _format(format),
    _width(width),
    _height(height)
{
	glGenRenderbuffers(1, &this->_glRenderBuffer);
    this->Bind();
    glRenderbufferStorage(GL_RENDERBUFFER, this->_format, this->_width, this->_height);
    this->Unbind();
}

Graphics::RenderBuffer::~RenderBuffer()
{
    this->Unbind();
	glDeleteRenderbuffers(1, &this->_glRenderBuffer);
}

void Graphics::RenderBuffer::Bind()
{
    if (!this->IsBound()) {
        glBindRenderbuffer(GL_RENDERBUFFER, this->_glRenderBuffer);
        RenderBuffer::_boundRenderBuffer = this->_glRenderBuffer;
    }
}

void Graphics::RenderBuffer::Unbind()
{
    if (this->IsBound()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        RenderBuffer::_boundRenderBuffer = 0;
    }
}
