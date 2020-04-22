#pragma once

#include <memory>

#include "Texture.h"
#include "VertexArray.h"
#include "Buffer.h"

namespace Graphics
{

    class Mesh
    {
    public:
        struct VertexData {
            Math::Vector3f vertex;
            Math::Vector3f normal;
            Math::Vector2f texture;
        };

        Mesh(std::shared_ptr<Graphics::VertexArray> vertexArrayObject, std::shared_ptr<Graphics::Buffer> vertexBuffer, std::shared_ptr<Graphics::Buffer> elementsBuffer, uint32_t elementsCount);
        virtual ~Mesh();
        void Render();
        bool HasTexture() const;
        std::shared_ptr<Graphics::Texture> GetTexture() const;
        void SetTexture(std::shared_ptr<Graphics::Texture> texture);
        std::shared_ptr<Graphics::VertexArray> GetVertexArray() const;
        std::shared_ptr<Graphics::Buffer> GetVertexBuffer() const;
        std::shared_ptr<Graphics::Buffer> GetElementBuffer() const;
        uint32_t GetElementsCount() const;

    private:
        bool _hasTexture;
        std::shared_ptr<Graphics::Texture> _texture;
        std::shared_ptr<Graphics::VertexArray> _vao;
        std::shared_ptr<Graphics::Buffer> _vbo;
        std::shared_ptr<Graphics::Buffer> _ebo;
        uint32_t _elementsCount;
    };

    inline bool Graphics::Mesh::HasTexture() const
    {
        return this->_hasTexture;
    }

    inline std::shared_ptr<Graphics::Texture> Graphics::Mesh::GetTexture() const
    {
        return this->_texture;
    }

    inline void Mesh::SetTexture(std::shared_ptr<Graphics::Texture> texture)
    {
        this->_texture = texture;
        this->_hasTexture = true;
    }

    inline std::shared_ptr<Graphics::VertexArray> Graphics::Mesh::GetVertexArray() const
    {
        return this->_vao;
    }

    inline std::shared_ptr<Graphics::Buffer> Mesh::GetVertexBuffer() const
    {
        return this->_vbo;
    }

    inline std::shared_ptr<Graphics::Buffer> Mesh::GetElementBuffer() const
    {
        return this->_ebo;
    }

    inline uint32_t Mesh::GetElementsCount() const
    {
        return this->_elementsCount;
    }

}
