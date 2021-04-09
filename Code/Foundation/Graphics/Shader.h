// ----------------------------------------------------------------------------------------
//  \file       Shader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Graphics
{
    /// Low-level OpenGL generic shader object wrapper
    class EXPORT Shader
    {
    public:
        enum class State
        {
            Initial,
            Source,
            Compiled
        };

        explicit Shader(GLenum type);
        virtual ~Shader();

        State GetState() const;
        void SetSource(const std::string& source);
        bool Compile();
        GLenum GetType() const;
        GLuint GetGlShader() const;
        std::string GetSource() const;

        static std::string GetStringFromType(GLenum type);
        static std::string GetExtensionFromType(GLenum type);

    private:
        State _state;
        GLenum _type;
        GLuint _glShader;
        std::string _source;
    };

    inline Shader::State Shader::GetState() const
    {
        return this->_state;
    }

    inline GLenum Shader::GetType() const
    {
        return this->_type;
    }

    inline GLuint Shader::GetGlShader() const
    {
        return this->_glShader;
    }

    inline std::string Shader::GetSource() const
    {
        return this->_source;
    }
}
