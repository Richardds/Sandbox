#include <gli/gli.hpp>

#include "Texture.h"
#include "../Core/Types.h"

std::unordered_map<GLenum, GLuint> Graphics::Texture::_boundTextures = {
	{GL_TEXTURE_1D, 0},
	{GL_TEXTURE_2D, 0},
	{GL_TEXTURE_3D, 0}
};

Graphics::Texture::Texture(const GLenum target) :
	_state(State::Initial),
	_target(target),
	_glTexture(0),
	_width(0),
	_height(0)
{
	glGenTextures(1, &this->_glTexture);
}

Graphics::Texture::~Texture()
{
	this->Unbind();
	glDeleteTextures(1, &this->_glTexture);
}

void Graphics::Texture::Bind() const
{
	if (!this->IsBound())
	{
		glBindTexture(this->_target, this->_glTexture);
		_boundTextures[this->_target] = this->_glTexture;
	}
}

void Graphics::Texture::Activate(const Bank bank) const
{
	this->Unbind();
	glActiveTexture(GL_TEXTURE0 + EnumToValue(bank));
	this->Bind();
}

void Graphics::Texture::Unbind() const
{
	if (this->IsBound())
	{
		glBindTexture(this->_target, 0);
		_boundTextures[this->_target] = 0;
	}
}

void Graphics::Texture::Data(const gli::texture& texture)
{
	_Assert(State::Initial == this->_state);
	_Assert(this->IsBound());

	const gli::gl internalFormat(gli::gl::PROFILE_GL33);
	gli::gl::format const format = internalFormat.translate(texture.format(), texture.swizzles());

	_Assert(gli::TARGET_2D == texture.target());

	glm::tvec3<GLsizei> const extent(texture.extent());

	this->_width = extent.x;
	this->_height = extent.y;

	this->Bind();
	glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(this->_target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(this->_target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(texture.levels() - 1));
	glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_R, format.Swizzles[0]);
	glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_G, format.Swizzles[1]);
	glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_B, format.Swizzles[2]);
	glTexParameteri(this->_target, GL_TEXTURE_SWIZZLE_A, format.Swizzles[3]);

	glTexStorage2D(
		this->_target,
		static_cast<GLint>(texture.levels()),
		format.Internal,
		this->_width, this->_height
	);

	for (std::size_t level = 0; level < texture.levels(); ++level)
	{
		glm::tvec3<GLsizei> extent(texture.extent(level));

		if (is_compressed(texture.format()))
		{
			glCompressedTexSubImage2D(
				this->_target,
				static_cast<GLint>(level),
				0, 0,
				extent.x, extent.y,
				format.Internal,
				static_cast<GLsizei>(texture.size(level)),
				texture.data(0, 0, level)
			);
		}
		else
		{
			glTexSubImage2D(
				this->_target,
				static_cast<GLint>(level),
				0, 0,
				extent.x, extent.y,
				format.External,
				format.Type,
				texture.data(0, 0, level)
			);
		}
	}

	this->_state = State::Loaded;
}

void Graphics::Texture::Data(const void* pixels, const unsigned int width, const unsigned int height)
{
	_Assert(State::Initial == this->_state);
	_Assert(this->IsBound());

	this->_width = width;
	this->_height = height;

	glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(this->_target, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	this->_state = State::Loaded;
}

void Graphics::Texture::Data(const std::shared_ptr<FrameBuffer>& frameBuffer, const unsigned int width,
                             const unsigned int height)
{
	_Assert(State::Initial == this->_state);
	_Assert(this->IsBound());
	_Assert(frameBuffer->IsBound());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->_glTexture, 0);

	this->_state = State::Loaded;
}

void Graphics::Texture::DepthData(const std::shared_ptr<FrameBuffer>& frameBuffer, const unsigned int width,
                                  const unsigned int height)
{
	_Assert(State::Initial == this->_state);
	_Assert(this->IsBound());
	_Assert(frameBuffer->IsBound());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->_glTexture, 0);

	this->_state = State::Loaded;
}

void Graphics::Texture::UnbindBound(const GLenum target)
{
	const GLuint bound = GetBound(target);
	if (bound != 0)
	{
		glBindTexture(target, 0);
		_boundTextures[target] = 0;
	}
}
