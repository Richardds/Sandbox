#include "TexturedMesh.h"

Graphics::TexturedMesh::TexturedMesh(std::shared_ptr<Mesh> mesh) :
    Mesh(mesh->GetVertexArray(), mesh->GetVertexBuffer(), mesh->GetElementBuffer(), mesh->GetElementsCount())
{
}

Graphics::TexturedMesh::~TexturedMesh()
{
}

void Graphics::TexturedMesh::Render(std::shared_ptr<EntityShader> shader)
{
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

    bool hasMaterialMap = this->HasMaterialMap();
    shader->LoadHasMaterialMap(hasMaterialMap);
    if (hasMaterialMap) {
        this->_materialMap->Activate(Texture::Bank::MATERIAL);
    }

    Mesh::Render(shader);
}
