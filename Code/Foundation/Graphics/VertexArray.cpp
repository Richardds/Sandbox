// ----------------------------------------------------------------------------------------
//  \file       VertexArray.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/VertexArray.h"

GLuint Graphics::VertexArray::_boundVertexArray = 0;

Graphics::VertexArray::VertexArray() :
    _glVertexArray(0)
{
    glGenVertexArrays(1, &this->_glVertexArray);
}

Graphics::VertexArray::~VertexArray()
{
    this->Unbind();
    glDeleteVertexArrays(1, &this->_glVertexArray);
}

void Graphics::VertexArray::Bind() const
{
    if (!this->IsBound())
    {
        glBindVertexArray(this->_glVertexArray);
        _boundVertexArray = this->_glVertexArray;
    }
}

void Graphics::VertexArray::Unbind() const
{
    if (this->IsBound())
    {
        glBindVertexArray(0);
        _boundVertexArray = 0;
    }
}
