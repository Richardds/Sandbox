#include "FrameBuffer.h"
#include "../Core/Types.h"
#include "Texture.h"

GLuint Graphics::FrameBuffer::_boundFrameBuffer = 0;

Graphics::FrameBuffer::FrameBuffer() :
	_glFrameBuffer(0)
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
        FrameBuffer::_boundFrameBuffer = this->_glFrameBuffer;
    }
}

void Graphics::FrameBuffer::Activate(unsigned int width, unsigned int height)
{
    Texture::UnbindBound(GL_TEXTURE_2D);
    this->Bind();
    glViewport(0, 0, width, height);
}

void Graphics::FrameBuffer::Deactivate()
{
    this->Unbind();
    std::shared_ptr<Window> context = Core::Instance().GetRenderingContext();
    glViewport(0, 0, context->GetWidth(), context->GetHeight());
}

void Graphics::FrameBuffer::Attach(std::shared_ptr<RenderBuffer> renderBuffer, GLenum attachment)
{
    _assert(this->IsBound());
    _assert(renderBuffer->IsBound());

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBuffer->GetGlRenderBuffer());

}

void Graphics::FrameBuffer::Unbind()
{
    if (this->IsBound()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        FrameBuffer::_boundFrameBuffer = 0;
    }
}
