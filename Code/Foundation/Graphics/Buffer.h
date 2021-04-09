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
        virtual ~Buffer();

        void Bind();
        bool IsBound() const;
        void Unbind();
        GLuint GetGlBuffer() const;
        GLenum GetTarget() const;
        GLenum GetType() const;
        template<typename T>
        void Data(std::vector<T> data, const GLenum type = GL_STATIC_DRAW);

    private:
        static std::unordered_map<GLenum, GLuint> _boundBuffers;

        GLuint _glBuffer;
        GLenum _target;
        GLenum _type;

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

    inline GLenum Buffer::GetType() const
    {
        return this->_type;
    }

    template<typename T>
    void Buffer::Data(std::vector<T> data, const GLenum type)
    {
        _Assert(this->IsBound())
        _Assert(0 < data.size())

        this->LoadData(static_cast<const void*>(data.data()), data.size() * sizeof(T), type);
    }
}
