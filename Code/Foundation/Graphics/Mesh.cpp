#include "Mesh.h"

#include <utility>

Graphics::Mesh::Mesh(std::shared_ptr<VertexArray> vertexArrayObject,
                     std::shared_ptr<Buffer> vertexBuffer, std::shared_ptr<Buffer> elementsBuffer,
                     const uint32_t elementsCount) :
	_vao(std::move(vertexArrayObject)),
	_vbo(std::move(vertexBuffer)),
	_ebo(std::move(elementsBuffer)),
	_elementsCount(elementsCount)
{
}

void Graphics::Mesh::DrawElements() const
{
	this->_vao->Bind();
	glDrawElements(GL_TRIANGLES, this->_elementsCount * 3, GL_UNSIGNED_INT, nullptr);
	this->_vao->Unbind();
}
