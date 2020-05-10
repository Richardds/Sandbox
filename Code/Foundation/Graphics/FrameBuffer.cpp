#include "FrameBuffer.h"
#include "../Core/Types.h"

GLuint Graphics::FrameBuffer::_boundFrameBuffer = 0;

Graphics::FrameBuffer::FrameBuffer(GLenum attachment) :
	_glFrameBuffer(0),
    _attachment(attachment)
{
	glGenFramebuffers(1, &this->_glFrameBuffer);
}

Graphics::FrameBuffer::~FrameBuffer()
{
    this->Unbind();
	glDeleteFramebuffers(1, &this->_glFrameBuffer);
}

void Graphics::FrameBuffer::Bind()
{
    if (!this->IsBound()) {
        glBindFramebuffer(GL_FRAMEBUFFER, this->_glFrameBuffer);
        glDrawBuffer(this->_attachment);
        FrameBuffer::_boundFrameBuffer = this->_glFrameBuffer;
    }
}

void Graphics::FrameBuffer::Attach(std::shared_ptr<RenderBuffer> renderBuffer)
{
    _assert(this->IsBound());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, this->_attachment, GL_RENDERBUFFER, renderBuffer->GetGlRenderBuffer());

}

void Graphics::FrameBuffer::Unbind()
{
    if (this->IsBound()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        FrameBuffer::_boundFrameBuffer = 0;
    }
}
