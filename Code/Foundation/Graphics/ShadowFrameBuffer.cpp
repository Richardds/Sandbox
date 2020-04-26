#include "ShadowFrameBuffer.h"

Graphics::ShadowFrameBuffer::ShadowFrameBuffer()
{
}

Graphics::ShadowFrameBuffer::~ShadowFrameBuffer()
{
}

std::shared_ptr<Graphics::Texture> Graphics::ShadowFrameBuffer::CreateDepthBufferAttachment(unsigned int width, unsigned int height)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	this->Bind();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetGlTexture(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return texture;
}
