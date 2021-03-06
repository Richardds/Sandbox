// ----------------------------------------------------------------------------------------
//  \file       Texture.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/Core.h"

namespace Graphics
{
    /// Low-level OpenGL texture object wrapper
    class EXPORT Texture
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

        static GLuint GetBound(GLenum target);
        static void UnbindBound(GLenum target);

        Texture();
        Texture(const Texture& texture) = delete;
        virtual ~Texture();

        Texture& operator=(const Texture& texture) = delete;

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
        float GetLODBias() const;
        void SetLODBias(float value);
        float GetAnisotropicFiltering() const;
        void SetAnisotropicFiltering(float value);

    private:
        static std::unordered_map<GLenum, GLuint> _boundTextures;

        State _state;
        GLenum _target;
        GLuint _glTexture;
        GLsizei _width;
        GLsizei _height;
        GLsizei _depth;
        float _lodBias;
        float _anisotropicFiltering;
    };

    inline GLuint Texture::GetBound(const GLenum target)
    {
        return _boundTextures[target];
    }

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
        _Assert(State::Initial == this->_state)
        this->_target = target;
    }

    inline unsigned int Texture::GetWidth() const
    {
        return this->_width;
    }

    inline void Texture::SetWidth(const unsigned int width)
    {
        _Assert(State::Initial == this->_state)
        this->_width = width;
    }

    inline unsigned int Texture::GetHeight() const
    {
        return this->_height;
    }

    inline void Texture::SetHeight(const unsigned int height)
    {
        _Assert(State::Initial == this->_state)
        this->_height = height;
    }

    inline unsigned int Texture::GetDepth() const
    {
        return this->_depth;
    }

    inline void Texture::SetDepth(const unsigned int depth)
    {
        _Assert(State::Initial == this->_state)
        this->_depth = depth;
    }

    inline float Texture::GetAnisotropicFiltering() const
    {
        return this->_anisotropicFiltering;
    }

    inline float Texture::GetLODBias() const
    {
        return this->_lodBias;
    }
}
