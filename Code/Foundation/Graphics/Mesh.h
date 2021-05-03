// ----------------------------------------------------------------------------------------
//  \file       Mesh.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/Buffer.h"
#include "Graphics/VertexArray.h"

namespace Graphics
{
    /// Holds necessary low-level OpenGL attributes for drawing a mesh of triangles
    class EXPORT Mesh
    {
    public:
        static bool GetCullingEnabled();
        static void SetCullingEnabled(bool enabled);

        Mesh(const std::shared_ptr<VertexArray>& vertexArrayObject,
             const std::shared_ptr<Buffer>& vertexBuffer,
             const std::shared_ptr<Buffer>& elementsBuffer,
             uint32_t elementsCount);
        virtual ~Mesh() = default;

        void DrawElements() const;
        std::shared_ptr<VertexArray> GetVertexArray() const;
        std::shared_ptr<Buffer> GetVertexBuffer() const;
        std::shared_ptr<Buffer> GetElementBuffer() const;
        uint32_t GetElementsCount() const;
        bool GetCulling() const;
        void SetCulling(bool enabled);

    protected:
        std::shared_ptr<VertexArray> _vao;
        std::shared_ptr<Buffer> _vbo;
        std::shared_ptr<Buffer> _ebo;
        uint32_t _elementsCount;
        bool _culling;

    private:
        static bool _cullingEnabled;
    };

    inline bool Mesh::GetCullingEnabled()
    {
        return _cullingEnabled;
    }

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

    inline bool Mesh::GetCulling() const
    {
        return this->_culling;
    }

    inline void Mesh::SetCulling(const bool enabled)
    {
        this->_culling = enabled;
    }

}
