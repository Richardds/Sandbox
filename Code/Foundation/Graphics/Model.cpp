// ----------------------------------------------------------------------------------------
//  \file       Model.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Model.h"
#include "Core/Debug.h"

Graphics::Model::Model() :
    _state(State::Initial)
{
}

void Graphics::Model::Render(const std::shared_ptr<EntityShader>& shader)
{
    for (const auto& [name, mesh] : this->_meshes)
    {
        mesh->Render(shader);
    }
}

void Graphics::Model::AddMesh(const std::string& name, const std::shared_ptr<TexturedMesh>& mesh)
{
    _Assert(State::Initial == this->_state)
    this->_meshes[name] = mesh;
}

void Graphics::Model::AddMesh(const std::string& name, const std::shared_ptr<Mesh>& mesh)
{
    this->AddMesh(name, std::make_shared<TexturedMesh>(mesh));
}

std::shared_ptr<Graphics::TexturedMesh> Graphics::Model::GetMesh(const std::string& name) const
{
    const auto mesh = this->_meshes.find(name);

    _Assert(mesh != this->_meshes.end())

    return mesh->second;
}

bool Graphics::Model::IsEmpty() const
{
    return this->_meshes.empty();
}
