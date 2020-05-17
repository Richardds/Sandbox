#include <vector>

#include "ShaderProgram.h"
#include "../Core/Debug.h"
#include "../IO/Console.h"
#include "../Math/Utils.h"

GLuint Graphics::ShaderProgram::_inUseGlShaderProgram = 0;

Graphics::ShaderProgram::ShaderProgram() :
	_state(State::Initial),
	_glShaderProgram(0)
{
	this->_glShaderProgram = glCreateProgram();
}

Graphics::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->_glShaderProgram);
}

void Graphics::ShaderProgram::AttachRequiredShaders(const std::shared_ptr<Shader>& vertexShader,
                                                    const std::shared_ptr<Shader>& fragmentShader)
{
	_Assert(State::Initial == this->_state);
	_Assert(Shader::State::Compiled == vertexShader->GetState());
	_Assert(Shader::State::Compiled == fragmentShader->GetState());

	this->_vertexShader = vertexShader;
	glAttachShader(this->_glShaderProgram, this->_vertexShader->GetGlShader());

	this->_fragmentShader = fragmentShader;
	glAttachShader(this->_glShaderProgram, this->_fragmentShader->GetGlShader());

	this->_state = State::Attached;
}

bool Graphics::ShaderProgram::Link()
{
	_Assert(State::Attached == this->_state);

	GLint linkStatus = 0;

	glLinkProgram(this->_glShaderProgram);
	glGetProgramiv(this->_glShaderProgram, GL_LINK_STATUS, &linkStatus);

	_Assert(0 != linkStatus);

	if (linkStatus == 0)
	{
		GLint logLength = 0;
		glGetProgramiv(this->_glShaderProgram, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<char> log(logLength);
		glGetProgramInfoLog(this->_glShaderProgram, logLength, nullptr, log.data());

		IO::Console::Instance().Warning("Failed to link shader program. Error: %s\n", log.data());

		return false;
	}

	this->_state = State::Linked;

	return true;
}

void Graphics::ShaderProgram::Use()
{
	_Assert(State::Linked == this->_state);

	if (!this->IsInUse())
	{
		glUseProgram(this->_glShaderProgram);
		_inUseGlShaderProgram = this->_glShaderProgram;
	}
}

GLint Graphics::ShaderProgram::GetUniformLocation(const std::string& name)
{
	_Assert(State::Linked == this->_state);
	_Assert(!name.empty());

	return glGetUniformLocation(this->_glShaderProgram, name.c_str());
}

void Graphics::ShaderProgram::LoadBool(const GLint location, const bool enable) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniform1ui(location, enable ? 1 : 0);
}

void Graphics::ShaderProgram::LoadInt(const GLint location, const uint32_t value) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniform1i(location, value);
}

void Graphics::ShaderProgram::LoadFloat(const GLint location, const float value) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniform1f(location, value);
}

void Graphics::ShaderProgram::LoadMatrix3f(const GLint location, const Math::Matrix3f& matrix) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(matrix));
}

void Graphics::ShaderProgram::LoadMatrix4f(const GLint location, const Math::Matrix4f& matrix) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(matrix));
}

void Graphics::ShaderProgram::LoadVector2f(const GLint location, const Math::Vector2f& vector) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniform2fv(location, 1, value_ptr(vector));
}

void Graphics::ShaderProgram::LoadVector3f(const GLint location, const Math::Vector3f& vector) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniform3fv(location, 1, value_ptr(vector));
}

void Graphics::ShaderProgram::LoadVector4f(const GLint location, const Math::Vector4f& vector) const
{
	_Assert(this->IsInUse());
	_Assert(State::Linked == this->_state);

	glUniform4fv(location, 1, value_ptr(vector));
}
