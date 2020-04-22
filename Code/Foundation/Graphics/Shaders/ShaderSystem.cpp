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
        GLuint location = ShaderProgram::GetUniformLocation(name);

        if (location != -1) {
            this->_uniformVariables.emplace_hint(it, name, ShaderProgram::GetUniformLocation(name));

        }

        return location;
    }

    return it->second;
}
