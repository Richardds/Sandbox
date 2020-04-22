#pragma once

#include <vector>

#include "Core.h"

namespace Graphics
{

    class VertexArray
    {
    public:
        VertexArray();
        virtual ~VertexArray();
        void Bind();
        bool IsBound() const;
        void Unbind();
        GLuint GetGlVertexArray() const;

        static GLuint GetBound();

    private:
        GLuint _glVertexArray;

        static GLuint _boundVertexArray;
    };

    inline bool Graphics::VertexArray::IsBound() const
    {
        return VertexArray::_boundVertexArray == this->_glVertexArray;
    }

    inline GLuint VertexArray::GetGlVertexArray() const
    {
        return this->_glVertexArray;
    }

    inline GLuint VertexArray::GetBound()
    {
        return VertexArray::_boundVertexArray;
    }

}
