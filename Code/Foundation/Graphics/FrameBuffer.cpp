// ----------------------------------------------------------------------------------------
//  \file       FrameBuffer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
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
	_Assert(this->IsBound());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::FrameBuffer::Deactivate() const
{
	this->Unbind();
	Core::Instance().GetRenderingContext()->ApplyViewport();
}

void Graphics::FrameBuffer::Attach(const std::shared_ptr<RenderBuffer>& renderBuffer, const GLenum attachment) const
{
	_Assert(this->IsBound());
	_Assert(renderBuffer->IsBound());

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBuffer->GetGlRenderBuffer());
}

void Graphics::FrameBuffer::Unbind() const
{
	if (this->IsBound())
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		_boundFrameBuffer = 0;
	}
}
