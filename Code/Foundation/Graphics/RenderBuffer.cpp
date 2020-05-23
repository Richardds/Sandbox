// ----------------------------------------------------------------------------------------
//  \file       RenderBuffer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/RenderBuffer.h"

GLuint Graphics::RenderBuffer::_boundRenderBuffer = 0;

Graphics::RenderBuffer::RenderBuffer(const GLenum format, const unsigned int width, const unsigned int height) :
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
