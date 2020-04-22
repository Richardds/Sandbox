#pragma once

#include <vector>
#include <unordered_map>

#include "Core.h"

namespace Graphics
{

    class Buffer
    {
    public:
        Buffer(GLenum target);
        virtual ~Buffer();
        void Bind();
        bool IsBound() const;
        void Unbind();
        template<typename T> void Data(std::vector<T> data, GLenum type = GL_STATIC_DRAW);
        GLenum GetTarget() const;
        GLuint GetGlBuffer() const;

        static GLuint GetBound(GLenum target);

    private:
        GLenum _target;
        GLuint _glBuffer;

        static std::unordered_map<GLenum, GLuint> _boundBuffers;
    };

    inline bool Graphics::Buffer::IsBound() const
    {
        return Buffer::_boundBuffers[this->_target] == this->_glBuffer;
    }

    inline GLenum Graphics::Buffer::GetTarget() const
    {
        return this->_target;
    }

    inline GLuint Buffer::GetGlBuffer() const
    {
        return this->_glBuffer;
    }

    inline GLuint Buffer::GetBound(GLenum target)
    {
        return Buffer::_boundBuffers[target];
    }

    template<typename T>
    void Buffer::Data(std::vector<T> data, GLenum type)
    {
        _assert(this->IsBound());

        glBufferData(this->_target, data.size() * sizeof(T), static_cast<const void*>(data.data()), type);
    }

}
