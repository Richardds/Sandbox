// ----------------------------------------------------------------------------------------
//  \file       RenderBuffer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Debug.h"

namespace Graphics
{
	/// Low-level OpenGL render buffer object wrapper
	class RenderBuffer
	{
	public:
		enum class State
		{
			Initial,
			Ready
		};
		
		RenderBuffer();
		~RenderBuffer();
		
		[[nodiscard]] State GetState() const;
		void Storage(GLenum format, unsigned int width, unsigned int height);
		[[nodiscard]] GLenum GetFormat() const;
		[[nodiscard]] unsigned int GetWidth() const;
		[[nodiscard]] unsigned int GetHeight() const;
		void Bind() const;
		[[nodiscard]] bool IsBound() const;
		void Unbind() const;
		[[nodiscard]] GLuint GetGlRenderBuffer() const;

		static GLuint GetBound();

	private:
		State _state;
		GLuint _glRenderBuffer;
		GLenum _format;
		unsigned int _width;
		unsigned int _height;

		static GLuint _boundRenderBuffer;
	};

	inline RenderBuffer::State RenderBuffer::GetState() const
	{
		return this->_state;
	}

	inline GLenum RenderBuffer::GetFormat() const
	{
		_Assert(State::Initial != this->_state);
		return this->_format;
	}

	inline unsigned int RenderBuffer::GetWidth() const
	{
		_Assert(State::Initial != this->_state);
		return this->_width;
	}

	inline unsigned int RenderBuffer::GetHeight() const
	{
		_Assert(State::Initial != this->_state);
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
