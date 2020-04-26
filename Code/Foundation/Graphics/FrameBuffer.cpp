#include "FrameBuffer.h"

Graphics::FrameBuffer::FrameBuffer() :
	_glFrameBuffer(0)
{
	glGenFramebuffers(1, &this->_glFrameBuffer);
}

Graphics::FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &this->_glFrameBuffer);
}

void Graphics::FrameBuffer::Bind()
{
    if (!this->IsBound()) {
        glBindFramebuffer(GL_FRAMEBUFFER, this->_glFrameBuffer);
        FrameBuffer::_boundFrameBuffer = this->_glFrameBuffer;
    }
}

void Graphics::FrameBuffer::Unbind()
{
    if (this->IsBound()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        FrameBuffer::_boundFrameBuffer = 0;
    }
}
