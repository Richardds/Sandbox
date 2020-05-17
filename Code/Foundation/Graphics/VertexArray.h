#pragma once

#include "Core.h"

namespace Graphics
{
	class VertexArray
	{
	public:
		VertexArray();
		virtual ~VertexArray();
		void Bind() const;
		[[nodiscard]] bool IsBound() const;
		void Unbind() const;
		[[nodiscard]] GLuint GetGlVertexArray() const;

		static GLuint GetBound();

	private:
		GLuint _glVertexArray;

		static GLuint _boundVertexArray;
	};

	inline bool VertexArray::IsBound() const
	{
		return _boundVertexArray == this->_glVertexArray;
	}

	inline GLuint VertexArray::GetGlVertexArray() const
	{
		return this->_glVertexArray;
	}

	inline GLuint VertexArray::GetBound()
	{
		return _boundVertexArray;
	}
}
