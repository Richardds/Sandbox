// ----------------------------------------------------------------------------------------
//  \file       Buffer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Buffer.h"

std::unordered_map<GLenum, GLuint> Graphics::Buffer::_boundBuffers = {
    {GL_ARRAY_BUFFER, 0},
    {GL_ELEMENT_ARRAY_BUFFER, 0},
    {GL_TEXTURE_BUFFER, 0},
    {GL_ATOMIC_COUNTER_BUFFER, 0},
    {GL_COPY_READ_BUFFER, 0},
    {GL_COPY_WRITE_BUFFER, 0},
    {GL_DISPATCH_INDIRECT_BUFFER, 0},
    {GL_DRAW_INDIRECT_BUFFER, 0},
    {GL_PIXEL_PACK_BUFFER, 0},
    {GL_PIXEL_UNPACK_BUFFER, 0},
    {GL_QUERY_BUFFER, 0},
    {GL_SHADER_STORAGE_BUFFER, 0},
    {GL_TRANSFORM_FEEDBACK_BUFFER, 0},
    {GL_UNIFORM_BUFFER, 0}
};

GLuint Graphics::Buffer::GetBound(const GLenum target)
{
    return _boundBuffers[target];
}

Graphics::Buffer::Buffer(const GLenum target) :
    _glBuffer(0),
    _target(target)
{
    glGenBuffers(1, &this->_glBuffer);
}

Graphics::Buffer::~Buffer()
{
    this->Unbind();
    glDeleteBuffers(1, &this->_glBuffer);
}

void Graphics::Buffer::Bind()
{
    if (!this->IsBound())
    {
        glBindBuffer(this->_target, this->_glBuffer);
        _boundBuffers[this->_target] = this->_glBuffer;
    }
}

bool Graphics::Buffer::IsBound() const
{
    return _boundBuffers[this->_target] == this->_glBuffer;
}

void Graphics::Buffer::Unbind()
{
    if (this->IsBound())
    {
        glBindBuffer(this->_target, 0);
        _boundBuffers[this->_target] = 0;
    }
}

void Graphics::Buffer::LoadData(const void* data, const size_t size, const GLenum type)
{
    glBufferData(this->_target, size, data, type);
}
