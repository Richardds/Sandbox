// ----------------------------------------------------------------------------------------
//  \file       Texture.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Texture.h"
#include "Core/Types.h"

std::unordered_map<GLenum, GLuint> Graphics::Texture::_boundTextures = {
    {GL_TEXTURE_1D, 0},
    {GL_TEXTURE_1D_ARRAY, 0},
    {GL_TEXTURE_2D, 0},
    {GL_TEXTURE_2D_ARRAY, 0},
    {GL_TEXTURE_3D, 0},
    {GL_TEXTURE_CUBE_MAP, 0},
    {GL_TEXTURE_CUBE_MAP_ARRAY, 0},
};

Graphics::Texture::Texture() :
    _state(State::Initial),
    _target(0),
    _glTexture(0),
    _width(0),
    _height(1),
    _depth(1)
{
    glGenTextures(1, &this->_glTexture);
}

Graphics::Texture::~Texture()
{
    this->Unbind();
    glDeleteTextures(1, &this->_glTexture);
}

void Graphics::Texture::Bind() const
{
    if (!this->IsBound())
    {
        _Assert(0 != this->_target);
        glBindTexture(this->_target, this->_glTexture);
        _boundTextures[this->_target] = this->_glTexture;
    }
}

void Graphics::Texture::Activate(const Bank bank) const
{
    this->Unbind();
    glActiveTexture(GL_TEXTURE0 + EnumToValue(bank));
    this->Bind();
}

void Graphics::Texture::Unbind() const
{
    if (this->IsBound())
    {
        glBindTexture(this->_target, 0);
        _boundTextures[this->_target] = 0;
    }
}

void Graphics::Texture::Data(const void* pixels, const unsigned int width, const unsigned int height)
{
    _Assert(GL_TEXTURE_2D == this->_target);
    _Assert(State::Initial == this->_state);
    _Assert(this->IsBound());

    this->_width = width;
    this->_height = height;

    glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // TODO: glTexStorage2D call
    glTexImage2D(this->_target, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    this->FinishLoading();
}

void Graphics::Texture::FinishLoading()
{
    _Assert(State::Initial == this->_state);

    this->_state = State::Loaded;
}

void Graphics::Texture::UnbindBound(const GLenum target)
{
    const GLuint bound = GetBound(target);
    if (bound != 0)
    {
        glBindTexture(target, 0);
        _boundTextures[target] = 0;
    }
}
