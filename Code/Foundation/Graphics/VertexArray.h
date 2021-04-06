// ----------------------------------------------------------------------------------------
//  \file       VertexArray.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Graphics
{
    /// Low-level OpenGL vertex array object wrapper
    class VertexArray
    {
    public:
        VertexArray();
        virtual ~VertexArray();

        void Bind() const;
        bool IsBound() const;
        void Unbind() const;
        GLuint GetGlVertexArray() const;

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
