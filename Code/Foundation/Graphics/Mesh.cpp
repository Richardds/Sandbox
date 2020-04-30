#include "Mesh.h"

Graphics::Mesh::Mesh(std::shared_ptr<Graphics::VertexArray> vertexArrayObject, std::shared_ptr<Graphics::Buffer> vertexBuffer, std::shared_ptr<Graphics::Buffer> elementsBuffer, uint32_t elementsCount) :
    _material(Math::Vector3f(0.85f), 5.0f, Math::Vector3f(0.5f), Math::Vector3f(0.1f)),
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
    shader->LoadMaterial(this->_material);

    this->_vao->Bind();

    glDrawElements(GL_TRIANGLES, this->_elementsCount * 3, GL_UNSIGNED_INT, 0);

    this->_vao->Unbind();
}
