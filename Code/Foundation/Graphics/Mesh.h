#pragma once

#include <memory>

#include "Texture.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shaders/EntityShader.h"

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
        void Render(std::shared_ptr<EntityShader> shader);
        bool HasDiffuseMap() const;
        std::shared_ptr<Graphics::Texture> GetDiffuseMap() const;
        void SetDiffuseMap(std::shared_ptr<Graphics::Texture> texture);
        bool HasNormalMap() const;
        std::shared_ptr<Graphics::Texture> GetNormalMap() const;
        void SetNormalMap(std::shared_ptr<Graphics::Texture> texture);
        std::shared_ptr<Graphics::VertexArray> GetVertexArray() const;
        std::shared_ptr<Graphics::Buffer> GetVertexBuffer() const;
        std::shared_ptr<Graphics::Buffer> GetElementBuffer() const;
        uint32_t GetElementsCount() const;

    private:
        std::shared_ptr<Graphics::Texture> _diffuseMap;
        std::shared_ptr<Graphics::Texture> _normalMap;
        std::shared_ptr<Graphics::VertexArray> _vao;
        std::shared_ptr<Graphics::Buffer> _vbo;
        std::shared_ptr<Graphics::Buffer> _ebo;
        uint32_t _elementsCount;
    };

    inline bool Graphics::Mesh::HasDiffuseMap() const
    {
        return static_cast<bool>(this->_diffuseMap);
    }

    inline std::shared_ptr<Graphics::Texture> Graphics::Mesh::GetDiffuseMap() const
    {
        return this->_diffuseMap;
    }

    inline void Mesh::SetDiffuseMap(std::shared_ptr<Graphics::Texture> texture)
    {
        this->_diffuseMap = texture;
    }

    inline bool Mesh::HasNormalMap() const
    {
        return static_cast<bool>(this->_normalMap);;
    }

    inline std::shared_ptr<Graphics::Texture> Mesh::GetNormalMap() const
    {
        return this->_normalMap;
    }

    inline void Mesh::SetNormalMap(std::shared_ptr<Graphics::Texture> texture)
    {
        this->_normalMap = texture;
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
