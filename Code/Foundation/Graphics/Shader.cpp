#include "Shader.h"
#include "../Core/Debug.h"
#include "../IO/Console.h"

Graphics::Shader::Shader(GLenum type) :
    _state(State::INITIAL),
    _type(type),
    _glShader(0)
{
    this->_glShader = glCreateShader(type);
}

Graphics::Shader::~Shader()
{
    glDeleteShader(this->_glShader);
}

void Graphics::Shader::SetSource(const std::string& source)
{
    _assert(State::INITIAL == this->_state);

    this->_source = source;
    const char* source_ptr = this->_source.c_str();
    glShaderSource(this->_glShader, 1, &source_ptr, NULL);
    this->_state = State::SOURCE;
}

bool Graphics::Shader::Compile()
{
    _assert(State::SOURCE == this->_state);

    GLint compilationStatus = 0;

    glCompileShader(this->_glShader);
    glGetShaderiv(this->_glShader, GL_COMPILE_STATUS, &compilationStatus);

    if (compilationStatus == 0) {
        GLint logLength = 0;
        glGetShaderiv(this->_glShader, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetShaderInfoLog(this->_glShader, logLength, NULL, log.data());

        IO::Console::Instance().Warning("Failed to compile shader. Error: %s\n", log.data());

        return false;
    }

    this->_state = State::COMPILED;

    return true;
}

std::string Graphics::Shader::GetStringFromType(GLenum type)
{
    switch (type)
    {
    case GL_VERTEX_SHADER:
        return "vertex";
    case GL_FRAGMENT_SHADER:
        return "fragment";
    default:
        return "invalid";
    }
}

std::string Graphics::Shader::GetExtensionFromType(GLenum type)
{
    switch (type)
    {
    case GL_VERTEX_SHADER:
        return "vert";
    case GL_FRAGMENT_SHADER:
        return "frag";
    default:
        return "invalid";
    }
}
