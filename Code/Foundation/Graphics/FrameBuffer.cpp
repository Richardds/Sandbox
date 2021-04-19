// ----------------------------------------------------------------------------------------
//  \file       FrameBuffer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Texture.h"

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

void Graphics::FrameBuffer::Bind() const
{
    if (!this->IsBound())
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->_glFrameBuffer);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        _boundFrameBuffer = this->_glFrameBuffer;
    }
}

void Graphics::FrameBuffer::Activate(const unsigned int width, const unsigned int height) const
{
    Texture::UnbindBound(GL_TEXTURE_2D);
    this->Bind();
    glViewport(0, 0, width, height);
}

void Graphics::FrameBuffer::Clear() const
{
    _Assert(this->IsBound())

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::FrameBuffer::Deactivate() const
{
    this->Unbind();
    Core::Instance().GetRenderingContext()->ApplyViewport();
}

void Graphics::FrameBuffer::AttachTexture(const std::shared_ptr<Texture>& texture,
                                          const unsigned width,
                                          const unsigned height) const
{
    _Assert(this->IsBound())
    _Assert(Texture::State::Initial == texture->GetState())
    _Assert(GL_TEXTURE_2D == texture->GetTarget())

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->GetGlTexture(), 0);

    texture->FinishLoading();
}

void Graphics::FrameBuffer::AttachDepthTexture(const std::shared_ptr<Texture>& texture,
                                               const unsigned width,
                                               const unsigned height) const
{
    _Assert(this->IsBound())
    _Assert(Texture::State::Initial == texture->GetState())
    _Assert(GL_TEXTURE_2D == texture->GetTarget())

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->GetGlTexture(), 0);

    texture->FinishLoading();
}

void Graphics::FrameBuffer::AttachDepthBuffer(const std::shared_ptr<RenderBuffer>& renderBuffer) const
{
    _Assert(this->IsBound())
    _Assert(RenderBuffer::State::Ready == renderBuffer->GetState())

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->GetGlRenderBuffer());
}

void Graphics::FrameBuffer::Unbind() const
{
    if (this->IsBound())
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        _boundFrameBuffer = 0;
    }
}
