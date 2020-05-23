// ----------------------------------------------------------------------------------------
//  \file       ShaderSystem.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Shaders/ShaderSystem.h"
#include "Core/Debug.h"
#include "IO/Console.h"
#include "Util/ResourcesLoader.h"

Graphics::ShaderSystem::ShaderSystem(std::string name) :
	_state(State::Initial),
	_name(std::move(name))
{
}

bool Graphics::ShaderSystem::Setup()
{
	_Assert(State::Initial == this->_state);

	std::shared_ptr<Shader> vertexShader = Util::ResourcesLoader::Instance().LoadShader(
		this->_name, GL_VERTEX_SHADER);
	if (!vertexShader->Compile())
	{
		return false;
	}

	std::shared_ptr<Shader> fragmentShader = Util::ResourcesLoader::Instance().LoadShader(
		this->_name, GL_FRAGMENT_SHADER);
	if (!fragmentShader->Compile())
	{
		return false;
	}

	this->AttachRequiredShaders(vertexShader, fragmentShader);
	if (!this->Link())
	{
		return false;
	}

	this->_state = State::Shader;

	return true;
}

void Graphics::ShaderSystem::Use()
{
	// Check if uniform locations are preloaded and default values set
	if (this->_state == State::Shader)
	{
		ShaderProgram::Use();
		this->InitializeUniformVariables();
		this->_state = State::Ready;
		return;
	}

	_Assert(State::Ready == this->_state);

	ShaderProgram::Use();
}

GLint Graphics::ShaderSystem::GetUniformLocation(const std::string& name)
{
	const auto it = this->_uniformVariables.find(name);
	if (it == this->_uniformVariables.end())
	{
		GLint location = ShaderProgram::GetUniformLocation(name);
		this->_uniformVariables.emplace_hint(it, name, location);

		return location;
	}

	return it->second;
}

void Graphics::ShaderSystem::InitializeBoolLocation(const std::string& name, const bool enabled, GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize bool '%s' uniform location!\n", name.c_str());
	}
	this->LoadBool(location, enabled);
}

void Graphics::ShaderSystem::InitializeIntLocation(const std::string& name, const int value, GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize int '%s' uniform location!\n", name.c_str());
	}
	this->LoadInt(location, value);
}

void Graphics::ShaderSystem::InitializeFloatLocation(const std::string& name, const float value, GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize float '%s' uniform location!\n", name.c_str());
	}
	this->LoadFloat(location, value);
}

void Graphics::ShaderSystem::InitializeMatrix3fLocation(const std::string& name, const Math::Matrix3f& matrix,
                                                        GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize Matrix3f '%s' uniform location!\n", name.c_str());
	}
	this->LoadMatrix3f(location, matrix);
}

void Graphics::ShaderSystem::InitializeMatrix4fLocation(const std::string& name, const Math::Matrix4f& matrix,
                                                        GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize Matrix4f '%s' uniform location!\n", name.c_str());
	}
	this->LoadMatrix4f(location, matrix);
}

void Graphics::ShaderSystem::InitializeVector2fLocation(const std::string& name, const Math::Vector2f& vector,
                                                        GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize Vector2f '%s' uniform location!\n", name.c_str());
	}
	this->LoadVector2f(location, vector);
}

void Graphics::ShaderSystem::InitializeVector3fLocation(const std::string& name, const Math::Vector3f& vector,
                                                        GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize Vector3f '%s' uniform location!\n", name.c_str());
	}
	this->LoadVector3f(location, vector);
}

void Graphics::ShaderSystem::InitializeVector4fLocation(const std::string& name, const Math::Vector4f& vector,
                                                        GLint& location)
{
	location = this->GetUniformLocation(name);
	if (location == -1)
	{
		IO::Console::Instance().Warning("Failed to initialize Vector4f '%s' uniform location!\n", name.c_str());
	}
	this->LoadVector4f(location, vector);
}
