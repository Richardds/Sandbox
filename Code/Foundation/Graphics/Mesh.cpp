#include "Mesh.h"

Graphics::Mesh::Mesh(std::shared_ptr<Graphics::VertexArray> vertexArrayObject, std::shared_ptr<Graphics::Buffer> vertexBuffer, std::shared_ptr<Graphics::Buffer> elementsBuffer, uint32_t elementsCount) :
    _vao(vertexArrayObject),
    _vbo(vertexBuffer),
    _ebo(elementsBuffer),
    _elementsCount(elementsCount)
{
}

Graphics::Mesh::~Mesh()
{
}

void Graphics::Mesh::Render(std::shared_ptr<EntityShader> shader)
{
    this->_vao->Bind();
    
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

    glDrawElements(GL_TRIANGLES, this->_elementsCount * 3, GL_UNSIGNED_INT, 0);

    this->_vao->Unbind();
}
