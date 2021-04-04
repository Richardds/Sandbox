// ----------------------------------------------------------------------------------------
//  \file       Mesh.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Mesh.h"

Graphics::Mesh::Mesh(const std::shared_ptr<VertexArray>& vertexArrayObject,
                     const std::shared_ptr<Buffer>& vertexBuffer,
                     const std::shared_ptr<Buffer>& elementsBuffer,
                     const uint32_t elementsCount) :
    _vao(vertexArrayObject),
    _vbo(vertexBuffer),
    _ebo(elementsBuffer),
    _elementsCount(elementsCount)
{
}

void Graphics::Mesh::DrawElements() const
{
    this->_vao->Bind();
    glDrawElements(GL_TRIANGLES, this->_elementsCount * 3, GL_UNSIGNED_INT, nullptr);
    this->_vao->Unbind();
}
