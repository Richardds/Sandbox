#include <gli/gli.hpp>

#include "Texture.h"
#include "../Core/Types.h"

std::unordered_map<GLenum, GLuint> Graphics::Texture::_boundTextures = {
    {GL_TEXTURE_1D, 0},
    {GL_TEXTURE_2D, 0},
    {GL_TEXTURE_3D, 0}
};

Graphics::Texture::Texture(GLenum target) :
	_state(State::INITIAL),
	_target(target),
	_glTexture(0),
	_width(0),
	_height(0)
{
	glGenTextures(1, &this->_glTexture);
}

Graphics::Texture::~Texture()
{
	glDeleteTextures(1, &this->_glTexture);
}

void Graphics::Texture::Bind()
{
	if (!this->IsBound()) {
		glBindTexture(this->_target, this->_glTexture);
		Texture::_boundTextures[this->_target] = this->_glTexture;
	}
}

void Graphics::Texture::Activate(Bank bank)
{
	this->Unbind();
	glActiveTexture(GL_TEXTURE0 + EnumToValue(bank));
	this->Bind();
}

void Graphics::Texture::Unbind()
{
	if (this->IsBound()) {
		glBindTexture(this->_target, 0);
		Texture::_boundTextures[this->_target] = 0;
	}
}

void Graphics::Texture::Data(const gli::texture& texture)
{
	_assert(State::INITIAL == this->_state);

	gli::gl GL(gli::gl::PROFILE_GL33);
	gli::gl::format const format = GL.translate(texture.format(), texture.swizzles());

	_assert(gli::TARGET_2D == texture.target());

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

	for (std::size_t level = 0; level < texture.levels(); ++level) {
		glm::tvec3<GLsizei> extent(texture.extent(level));

		if (gli::is_compressed(texture.format())) {
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
		else {
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

	this->_state = State::LOADED;
}

void Graphics::Texture::Data(const void * pixels, uint32_t width, uint32_t height)
{
	_assert(State::INITIAL == this->_state);
	_assert(this->IsBound());

	this->_width = width;
	this->_height = height;

	glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(this->_target, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	this->_state = State::LOADED;
}
