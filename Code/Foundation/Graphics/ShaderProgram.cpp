#include "ShaderProgram.h"
#include "../Math/Utils.h"
#include "../Core/Debug.h"
#include "../IO/Console.h"

GLuint Graphics::ShaderProgram::_inUseGlShaderProgram = 0;

Graphics::ShaderProgram::ShaderProgram() :
    _state(State::INITIAL),
    _glShaderProgram(0)
{
    this->_glShaderProgram = glCreateProgram();
}

Graphics::ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->_glShaderProgram);
}

void Graphics::ShaderProgram::AttachRequiredShaders(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
{
    _assert(State::INITIAL == this->_state);
    _assert(Shader::State::COMPILED == vertexShader->GetState());
    _assert(Shader::State::COMPILED == fragmentShader->GetState());

    this->_vertexShader = vertexShader;
    glAttachShader(this->_glShaderProgram, this->_vertexShader->GetGlShader());

    this->_fragmentShader = fragmentShader;
    glAttachShader(this->_glShaderProgram, this->_fragmentShader->GetGlShader());

    this->_state = State::ATTACHED;
}

bool Graphics::ShaderProgram::Link()
{
    _assert(State::ATTACHED == this->_state);

    GLint linkStatus = 0;

    glLinkProgram(this->_glShaderProgram);
    glGetProgramiv(this->_glShaderProgram, GL_LINK_STATUS, &linkStatus);

    _assert(0 != linkStatus);

    if (linkStatus == 0) {
        GLint logLength = 0;
        glGetProgramiv(this->_glShaderProgram, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetProgramInfoLog(this->_glShaderProgram, logLength, NULL, log.data());

        IO::Console::Instance().Warning("Failed to link shader program. Error: %s\n", log.data());

        return false;
    }

    this->_state = State::LINKED;

    return true;
}

void Graphics::ShaderProgram::Use()
{
    _assert(State::LINKED == this->_state);

    if (!this->IsInUse()) {
        glUseProgram(this->_glShaderProgram);
        ShaderProgram::_inUseGlShaderProgram = this->_glShaderProgram;
    }
}

GLint Graphics::ShaderProgram::GetUniformLocation(const std::string& name)
{
    _assert(State::LINKED == this->_state);
    _assert(!name.empty());

    return glGetUniformLocation(this->_glShaderProgram, name.c_str());
}

void Graphics::ShaderProgram::LoadBool(GLint location, bool enable)
{
    _assert(this->IsInUse());
    _assert(State::LINKED == this->_state);

    glUniform1ui(location, enable ? 1 : 0);
}

void Graphics::ShaderProgram::LoadInt(GLint location, uint32_t value)
{
    _assert(this->IsInUse());
    _assert(State::LINKED == this->_state);

    glUniform1i(location, value);
}

void Graphics::ShaderProgram::LoadFloat(GLint location, float value)
{
    _assert(this->IsInUse());
    _assert(State::LINKED == this->_state);

    glUniform1f(location, value);
}

void Graphics::ShaderProgram::LoadMatrix3f(GLint location, const Math::Matrix3f& matrix)
{
    _assert(this->IsInUse());
    _assert(State::LINKED == this->_state);

    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Graphics::ShaderProgram::LoadMatrix4f(GLint location, const Math::Matrix4f& matrix)
{
    _assert(this->IsInUse());
    _assert(State::LINKED == this->_state);

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Graphics::ShaderProgram::LoadVector3f(GLint location, const Math::Vector3f& vector)
{
    _assert(this->IsInUse());
    _assert(State::LINKED == this->_state);

    glUniform3fv(location, 1, glm::value_ptr(vector));
}

void Graphics::ShaderProgram::LoadVector4f(GLint location, const Math::Vector4f& vector)
{
    _assert(this->IsInUse());
    _assert(State::LINKED == this->_state);
    _assert(-1 != location);

    glUniform4fv(location, 1, glm::value_ptr(vector));
}
