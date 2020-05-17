#pragma once

#include "Core.h"
#include "RenderBuffer.h"

namespace Graphics
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		virtual ~FrameBuffer();
		void Bind() const;
		void Activate(unsigned int width, unsigned int height) const;
		void Clear() const;
		void Deactivate() const;
		void Attach(const std::shared_ptr<RenderBuffer>& renderBuffer, GLenum attachment) const;
		[[nodiscard]] bool IsBound() const;
		void Unbind() const;
		[[nodiscard]] GLuint GetGlFrameBuffer() const;

		static GLuint GetBound(GLenum target);

	private:
		GLuint _glFrameBuffer;

		static GLuint _boundFrameBuffer;
	};

	inline bool FrameBuffer::IsBound() const
	{
		return _boundFrameBuffer == this->_glFrameBuffer;
	}

	inline GLuint FrameBuffer::GetGlFrameBuffer() const
	{
		return this->_glFrameBuffer;
	}

	inline GLuint FrameBuffer::GetBound(GLenum target)
	{
		return _boundFrameBuffer;
	}
}
