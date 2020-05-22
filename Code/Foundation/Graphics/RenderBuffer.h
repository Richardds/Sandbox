#pragma once

#include "Precompiled.h"

namespace Graphics
{
	class RenderBuffer
	{
	public:
		RenderBuffer(GLenum format, unsigned int width, unsigned int height);
		~RenderBuffer();
		[[nodiscard]] GLenum GetFormat() const;
		[[nodiscard]] unsigned int GetWidth() const;
		[[nodiscard]] unsigned int GetHeight() const;
		void Bind() const;
		[[nodiscard]] bool IsBound() const;
		void Unbind() const;
		[[nodiscard]] GLuint GetGlRenderBuffer() const;

		static GLuint GetBound();

	private:
		GLuint _glRenderBuffer;
		GLenum _format;
		unsigned int _width;
		unsigned int _height;

		static GLuint _boundRenderBuffer;
	};

	inline GLenum RenderBuffer::GetFormat() const
	{
		return this->_format;
	}

	inline unsigned int RenderBuffer::GetWidth() const
	{
		return this->_width;
	}

	inline unsigned int RenderBuffer::GetHeight() const
	{
		return this->_height;
	}

	inline bool RenderBuffer::IsBound() const
	{
		return _boundRenderBuffer == this->_glRenderBuffer;
	}

	inline GLuint RenderBuffer::GetGlRenderBuffer() const
	{
		return this->_glRenderBuffer;
	}

	inline GLuint RenderBuffer::GetBound()
	{
		return _boundRenderBuffer;
	}
}
