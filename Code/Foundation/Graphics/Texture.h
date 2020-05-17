#pragma once

#include <unordered_map>
#include <gli/texture.hpp>

#include "Core.h"
#include "FrameBuffer.h"

namespace Graphics
{
	class Texture
	{
	public:
		enum class State
		{
			Initial,
			Loaded
		};

		enum class Bank
		{
			Diffuse = 0,
			Normal = 1,
			Specular = 2,
			Depth = 3,

			Distortion = 4,
			Reflection = 5,
			Refraction = 6
		};

		explicit Texture(GLenum target);
		virtual ~Texture();
		[[nodiscard]] State GetState() const;
		void Bind() const;
		void Activate(Bank bank) const;
		[[nodiscard]] bool IsBound() const;
		void Unbind() const;
		void Data(const gli::texture& texture);
		void Data(const void* pixels, unsigned int width, unsigned int height);
		void Data(const std::shared_ptr<FrameBuffer>& frameBuffer, unsigned int width, unsigned int height);
		void DepthData(const std::shared_ptr<FrameBuffer>& frameBuffer, unsigned int width, unsigned int height);
		[[nodiscard]] GLenum GetTarget() const;
		[[nodiscard]] GLuint GetGlTexture() const;
		[[nodiscard]] GLsizei GetWidth() const;
		[[nodiscard]] GLsizei GetHeight() const;

		static GLuint GetBound(GLenum target);
		static void UnbindBound(GLenum target);

	private:
		State _state;
		GLenum _target;
		GLuint _glTexture;
		GLsizei _width;
		GLsizei _height;

		static std::unordered_map<GLenum, GLuint> _boundTextures;
	};

	inline Texture::State Texture::GetState() const
	{
		return this->_state;
	}

	inline bool Texture::IsBound() const
	{
		return _boundTextures[this->_target] == this->_glTexture;
	}

	inline GLenum Texture::GetTarget() const
	{
		return this->_target;
	}

	inline GLuint Texture::GetGlTexture() const
	{
		return this->_glTexture;
	}

	inline GLsizei Texture::GetWidth() const
	{
		return this->_width;
	}

	inline GLsizei Texture::GetHeight() const
	{
		return this->_height;
	}

	inline GLuint Texture::GetBound(const GLenum target)
	{
		return _boundTextures[target];
	}
}
