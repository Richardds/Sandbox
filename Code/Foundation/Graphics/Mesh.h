// ----------------------------------------------------------------------------------------
//  \file       Mesh.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Buffer.h"
#include "Graphics/VertexArray.h"

namespace Graphics
{
    /// Holds necessary low-level OpenGL attributes for drawing a mesh of triangles
    class Mesh
    {
    public:
        Mesh(std::shared_ptr<VertexArray> vertexArrayObject, std::shared_ptr<Buffer> vertexBuffer,
             std::shared_ptr<Buffer> elementsBuffer, uint32_t elementsCount);
        virtual ~Mesh() = default;

        void DrawElements() const;
        [[nodiscard]] std::shared_ptr<VertexArray> GetVertexArray() const;
        [[nodiscard]] std::shared_ptr<Buffer> GetVertexBuffer() const;
        [[nodiscard]] std::shared_ptr<Buffer> GetElementBuffer() const;
        [[nodiscard]] uint32_t GetElementsCount() const;

    protected:
        std::shared_ptr<VertexArray> _vao;
        std::shared_ptr<Buffer> _vbo;
        std::shared_ptr<Buffer> _ebo;
        uint32_t _elementsCount;
    };

    inline std::shared_ptr<VertexArray> Mesh::GetVertexArray() const
    {
        return this->_vao;
    }

    inline std::shared_ptr<Buffer> Mesh::GetVertexBuffer() const
    {
        return this->_vbo;
    }

    inline std::shared_ptr<Buffer> Mesh::GetElementBuffer() const
    {
        return this->_ebo;
    }

    inline uint32_t Mesh::GetElementsCount() const
    {
        return this->_elementsCount;
    }
}
