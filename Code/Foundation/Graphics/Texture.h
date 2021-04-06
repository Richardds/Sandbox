// ----------------------------------------------------------------------------------------
//  \file       Texture.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Core.h"

namespace Graphics
{
    /// Low-level OpenGL texture object wrapper
    class Texture
    {
    public:
        enum class State
        {
            Initial,
            Loaded
        };

        enum class Bank
        {
            Diffuse = 0,
            Normal = 1,
            Specular = 2,
            Depth = 3,

            Distortion = 4,
            Reflection = 5,
            Refraction = 6,

            Skybox = 7,
            Font = 8
        };

        Texture();
        virtual ~Texture();

        State GetState() const;
        void Bind() const;
        void Activate(Bank bank) const;
        bool IsBound() const;
        void Unbind() const;
        void FinishLoading();
        GLenum GetTarget() const;
        void SetTarget(GLenum target);
        GLuint GetGlTexture() const;
        unsigned int GetWidth() const;
        void SetWidth(unsigned int width);
        unsigned int GetHeight() const;
        void SetHeight(unsigned int height);
        unsigned int GetDepth() const;
        void SetDepth(unsigned int depth);

        static GLuint GetBound(GLenum target);
        static void UnbindBound(GLenum target);

    private:
        State _state;
        GLenum _target;
        GLuint _glTexture;
        GLsizei _width;
        GLsizei _height;
        GLsizei _depth;

        static std::unordered_map<GLenum, GLuint> _boundTextures;
    };

    inline Texture::State Texture::GetState() const
    {
        return this->_state;
    }

    inline bool Texture::IsBound() const
    {
        return _boundTextures[this->_target] == this->_glTexture;
    }

    inline GLenum Texture::GetTarget() const
    {
        return this->_target;
    }

    inline GLuint Texture::GetGlTexture() const
    {
        return this->_glTexture;
    }

    inline void Texture::SetTarget(const GLenum target)
    {
        _Assert(State::Initial == this->_state);
        this->_target = target;
    }

    inline unsigned int Texture::GetWidth() const
    {
        return this->_width;
    }

    inline void Texture::SetWidth(const unsigned int width)
    {
        _Assert(State::Initial == this->_state);
        this->_width = width;
    }

    inline unsigned int Texture::GetHeight() const
    {
        return this->_height;
    }

    inline void Texture::SetHeight(const unsigned int height)
    {
        _Assert(State::Initial == this->_state);
        this->_height = height;
    }

    inline unsigned int Texture::GetDepth() const
    {
        return this->_depth;
    }

    inline void Texture::SetDepth(const unsigned int depth)
    {
        _Assert(State::Initial == this->_state);
        this->_depth = depth;
    }

    inline GLuint Texture::GetBound(const GLenum target)
    {
        return _boundTextures[target];
    }
}
