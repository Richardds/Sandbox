// ----------------------------------------------------------------------------------------
//  \file       Buffer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Debug.h"

namespace Graphics
{
    /// Low-level OpenGL vertex buffer object wrapper
    class EXPORT Buffer
    {
    public:
        static GLuint GetBound(GLenum target);

        explicit Buffer(GLenum target);
        Buffer(const Buffer& buffer) = delete;
        virtual ~Buffer();

        Buffer& operator=(const Buffer& buffer) = delete;

        void Bind();
        bool IsBound() const;
        void Unbind();
        GLuint GetGlBuffer() const;
        GLenum GetTarget() const;
        template<typename T>
        void Data(std::vector<T> data, GLenum type = GL_STATIC_DRAW);
        void Invalidate();

    private:
        static std::unordered_map<GLenum, GLuint> _boundBuffers;

        GLuint _glBuffer;
        GLenum _target;

        void LoadData(const void* data, size_t size, GLenum type);
    };

    inline GLuint Buffer::GetGlBuffer() const
    {
        return this->_glBuffer;
    }

    inline GLenum Buffer::GetTarget() const
    {
        return this->_target;
    }

    template<typename T>
    void Buffer::Data(std::vector<T> data, const GLenum type)
    {
        _Assert(this->IsBound())
        _Assert(0 < data.size())

        this->LoadData(static_cast<const void*>(data.data()), data.size() * sizeof(T), type);
    }
}
