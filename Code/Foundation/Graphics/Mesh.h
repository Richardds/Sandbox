#pragma once

#include <memory>

#include "Material.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shaders/EntityShader.h"

namespace Graphics
{

    class Mesh
    {
    public:
        Mesh(std::shared_ptr<Graphics::VertexArray> vertexArrayObject, std::shared_ptr<Graphics::Buffer> vertexBuffer, std::shared_ptr<Graphics::Buffer> elementsBuffer, uint32_t elementsCount);
        virtual ~Mesh();
        virtual void Render(std::shared_ptr<EntityShader> shader);
        Material GetMaterial() const;
        void SetMaterial(const Material& material);
        std::shared_ptr<Graphics::VertexArray> GetVertexArray() const;
        std::shared_ptr<Graphics::Buffer> GetVertexBuffer() const;
        std::shared_ptr<Graphics::Buffer> GetElementBuffer() const;
        uint32_t GetElementsCount() const;

    protected:
        Material _material;
        std::shared_ptr<Graphics::VertexArray> _vao;
        std::shared_ptr<Graphics::Buffer> _vbo;
        std::shared_ptr<Graphics::Buffer> _ebo;
        uint32_t _elementsCount;
    };

    inline Graphics::Material Graphics::Mesh::GetMaterial() const
    {
        return this->_material;
    }

    inline void Mesh::SetMaterial(const Material& material)
    {
        this->_material = material;
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
