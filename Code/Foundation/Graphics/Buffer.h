#pragma once

#include "Precompiled.h"
#include "Graphics/Core.h"

namespace Graphics
{
	class Buffer
	{
	public:
		explicit Buffer(GLenum target);
		virtual ~Buffer();
		void Bind() const;
		[[nodiscard]] bool IsBound() const;
		void Unbind() const;
		template <typename T>
		void Data(std::vector<T> data, GLenum type = GL_STATIC_DRAW);
		[[nodiscard]] GLenum GetTarget() const;
		[[nodiscard]] GLuint GetGlBuffer() const;

		static GLuint GetBound(GLenum target);

	private:
		GLenum _target;
		GLuint _glBuffer;

		static std::unordered_map<GLenum, GLuint> _boundBuffers;
	};

	inline bool Buffer::IsBound() const
	{
		return _boundBuffers[this->_target] == this->_glBuffer;
	}

	inline GLenum Buffer::GetTarget() const
	{
		return this->_target;
	}

	inline GLuint Buffer::GetGlBuffer() const
	{
		return this->_glBuffer;
	}

	inline GLuint Buffer::GetBound(GLenum target)
	{
		return _boundBuffers[target];
	}

	template <typename T>
	void Buffer::Data(std::vector<T> data, GLenum type)
	{
		_Assert(this->IsBound());

		glBufferData(this->_target, data.size() * sizeof(T), static_cast<const void*>(data.data()), type);
	}
}
