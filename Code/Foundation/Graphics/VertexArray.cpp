#include "VertexArray.h"

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

void Graphics::VertexArray::Bind()
{
    if (!this->IsBound()) {
        glBindVertexArray(this->_glVertexArray);
        VertexArray::_boundVertexArray = this->_glVertexArray;
    }
}

void Graphics::VertexArray::Unbind()
{
    if (this->IsBound()) {
        glBindVertexArray(0);
        VertexArray::_boundVertexArray = 0;
    }
}
