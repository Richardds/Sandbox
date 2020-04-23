#include "ShaderSystem.h"
#include "../../Core/Debug.h"
#include "../../Util/ResourcesLoader.h"

Graphics::ShaderSystem::ShaderSystem(const std::string& name) :
    _state(State::INITIAL),
    _name(name)
{
}

Graphics::ShaderSystem::~ShaderSystem()
{
}

bool Graphics::ShaderSystem::Load()
{
    _assert(State::INITIAL == this->_state);

    std::shared_ptr<Graphics::Shader> vertexShader = Util::ResourcesLoader::Instance().LoadShader(this->_name, GL_VERTEX_SHADER);
    if (!vertexShader->Compile()) {
        return false;
    }

    std::shared_ptr<Graphics::Shader> fragmentShader = Util::ResourcesLoader::Instance().LoadShader(this->_name, GL_FRAGMENT_SHADER);
    if (!fragmentShader->Compile()) {
        return false;
    }

    this->AttachRequiredShaders(vertexShader, fragmentShader);
    if (!this->Link()) {
        return false;
    }

    this->_state = State::SHADER;

    return true;
}

void Graphics::ShaderSystem::Use()
{
    // Check if uniform locations are preloaded and default values set
    if (this->_state == State::SHADER) {
        ShaderProgram::Use();
        this->InitializeUniformVariables();
        this->_state = State::READY;
        return;
    }

    _assert(State::READY == this->_state);

    ShaderProgram::Use();
}

void Graphics::ShaderSystem::Begin()
{
    // Override
}

GLint Graphics::ShaderSystem::GetUniformLocation(const std::string& name)
{
    auto it = this->_uniformVariables.find(name);
    if (it == this->_uniformVariables.end()) {
        GLint location = ShaderProgram::GetUniformLocation(name);
        this->_uniformVariables.emplace_hint(it, name, location);

        return location;
    }

    return it->second;
}

void Graphics::ShaderSystem::InitializeBoolLocation(const std::string& name, bool enabled, GLint& location)
{
    location = this->GetUniformLocation(name);
    this->LoadBool(location, enabled);
}

void Graphics::ShaderSystem::InitializeIntLocation(const std::string& name, uint32_t value, GLint& location)
{
    location = this->GetUniformLocation(name);
    this->LoadInt(location, value);
}

void Graphics::ShaderSystem::InitializeFloatLocation(const std::string& name, float value, GLint& location)
{
    location = this->GetUniformLocation(name);
    this->LoadFloat(location, value);
}

void Graphics::ShaderSystem::InitializeMatrix3fLocation(const std::string& name, Math::Matrix3f matrix, GLint& location)
{
    location = this->GetUniformLocation(name);
    this->LoadMatrix3f(location, matrix);
}

void Graphics::ShaderSystem::InitializeMatrix4fLocation(const std::string& name, Math::Matrix4f matrix, GLint& location)
{
    location = this->GetUniformLocation(name);
    this->LoadMatrix4f(location, matrix);
}

void Graphics::ShaderSystem::InitializeVector3fLocation(const std::string& name, Math::Vector3f vector, GLint& location)
{
    location = this->GetUniformLocation(name);
    this->LoadVector3f(location, vector);
}

void Graphics::ShaderSystem::InitializeVector4fLocation(const std::string& name, Math::Vector4f vector, GLint& location)
{
    location = this->GetUniformLocation(name);
    this->LoadVector4f(location, vector);
}
