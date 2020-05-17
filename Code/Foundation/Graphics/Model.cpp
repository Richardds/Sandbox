#include "Model.h"
#include "../Core/Debug.h"

Graphics::Model::Model() :
	_state(State::Initial)
{
}

void Graphics::Model::Render(const std::shared_ptr<EntityShader>& shader)
{
	for (auto& mesh : this->_meshes)
	{
		mesh.second->Render(shader);
	}
}

void Graphics::Model::AddMesh(const std::string& name, const std::shared_ptr<TexturedMesh>& mesh)
{
	_Assert(State::Initial == this->_state);
	this->_meshes[name] = mesh;
}

std::shared_ptr<Graphics::TexturedMesh> Graphics::Model::GetMesh(const std::string& name) const
{
	const auto mesh = this->_meshes.find(name);

	_Assert(mesh != this->_meshes.end());

	return mesh->second;
}

std::unordered_map<std::string, std::shared_ptr<Graphics::TexturedMesh>> Graphics::Model::GetMeshes() const
{
	return this->_meshes;
}

void Graphics::Model::FinishLoading()
{
	_Assert(State::Initial == this->_state);

	this->_state = State::Loaded;
}
