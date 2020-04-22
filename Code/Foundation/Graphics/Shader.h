#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>

namespace Graphics
{

    class Shader
    {
    public:
        enum class State {
            INITIAL,
            SOURCE,
            COMPILED
        };

        Shader(GLenum type);
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

    inline Graphics::Shader::State Graphics::Shader::GetState() const
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

    inline std::string Graphics::Shader::GetSource() const
    {
        return this->_source;
    }

}
