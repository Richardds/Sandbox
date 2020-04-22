#pragma once

#include <vector>
#include <unordered_map>
#include <gli/texture.hpp>

#include "Core.h"

namespace Graphics
{

    class Texture
    {
    public:
        enum class State {
            INITIAL,
            LOADED
        };

        Texture(GLenum target = GL_TEXTURE_2D);
        virtual ~Texture();
        State GetState() const;
        void Bind();
        bool IsBound() const;
        void Unbind();
        void Data(const gli::texture& texture);
        void Data(const void * pixels, uint32_t width, uint32_t height);
        GLenum GetTarget() const;
        GLuint GetGlTexture() const;
        GLsizei GetWidth() const;
        GLsizei GetHeight() const;

        static GLuint GetBound(GLenum target);

    private:
        State _state;
        GLenum _target;
        GLuint _glTexture;
        GLsizei _width;
        GLsizei _height;

        static std::unordered_map<GLenum, GLuint> _boundTextures;
    };

    inline Graphics::Texture::State Graphics::Texture::GetState() const
    {
        return this->_state;
    }

    inline bool Texture::IsBound() const
    {
        return Texture::_boundTextures[this->_target] == this->_glTexture;
    }

    inline GLenum Texture::GetTarget() const
    {
        return this->_target;
    }

    inline GLuint Texture::GetGlTexture() const
    {
        return this->_glTexture;
    }

    inline GLsizei Texture::GetWidth() const
    {
        return this->_width;
    }

    inline GLsizei Texture::GetHeight() const
    {
        return this->_height;
    }

    inline GLuint Texture::GetBound(GLenum target)
    {
        return Texture::_boundTextures[target];
    }

}
