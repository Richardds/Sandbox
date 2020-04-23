#include "Model.h"
#include "../Core/Debug.h"

Graphics::Model::Model() :
	_state(State::INITIAL)
{
}

Graphics::Model::~Model()
{
}

void Graphics::Model::Render(std::shared_ptr<EntityShader> shader)
{
	for (auto& mesh : this->_meshes) {
		mesh.second->Render(shader);
	}
}

void Graphics::Model::AddMesh(const std::string& name, std::shared_ptr<Mesh> mesh)
{
	_assert(State::INITIAL == this->_state);
	this->_meshes[name] = mesh;
}

std::shared_ptr<Graphics::Mesh> Graphics::Model::GetMesh(const std::string& name) const
{
	auto mesh = this->_meshes.find(name);

	_assert(mesh != this->_meshes.end());

	return mesh->second;
}

std::unordered_map<std::string, std::shared_ptr<Graphics::Mesh>> Graphics::Model::GetMeshes() const
{
	return this->_meshes;
}

void Graphics::Model::FinishLoading()
{
	_assert(State::INITIAL == this->_state);

	this->_state = State::LOADED;
}
