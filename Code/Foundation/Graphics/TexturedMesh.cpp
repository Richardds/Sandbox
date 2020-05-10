#include "TexturedMesh.h"

Graphics::TexturedMesh::TexturedMesh(std::shared_ptr<Mesh> mesh) :
    _material(Math::Vector3f(0.85f), 5.0f, Math::Vector3f(0.5f), Math::Vector3f(0.1f)),
    Mesh(mesh->GetVertexArray(), mesh->GetVertexBuffer(), mesh->GetElementBuffer(), mesh->GetElementsCount())
{
}

Graphics::TexturedMesh::~TexturedMesh()
{
}

void Graphics::TexturedMesh::Render(std::shared_ptr<EntityShader> shader)
{
    shader->LoadMaterial(this->_material);

    bool hasDiffuseMap = this->HasDiffuseMap();
    shader->LoadHasDiffuseMap(hasDiffuseMap);
    if (hasDiffuseMap) {
        this->_diffuseMap->Activate(Texture::Bank::DIFFUSE);
    }

    bool hasNormalMap = this->HasNormalMap();
    shader->LoadHasNormalMap(hasNormalMap);
    if (hasNormalMap) {
        this->_normalMap->Activate(Texture::Bank::NORMAL);
    }

    bool hasSpecularMap = this->HasSpecularMap();
    shader->LoadHasSpecularMap(hasSpecularMap);
    if (hasSpecularMap) {
        this->_specularMap->Activate(Texture::Bank::SPECULAR);
    }

    Mesh::DrawElements();
}
