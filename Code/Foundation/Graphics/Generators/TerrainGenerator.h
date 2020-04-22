#pragma once

#include <vector>
#include <memory>

#include "../../Math/Vector.h"
#include "../../Graphics/Mesh.h"
#include "../../Graphics/VertexAttributeConfig.h"

namespace Graphics
{

    class TerrainGenerator
    {
    public:
        TerrainGenerator();
        virtual ~TerrainGenerator();
        void Generate(float size);
        std::shared_ptr<Graphics::Mesh> Store();
        std::vector<Graphics::Mesh::VertexData> GetVertexData() const;
        std::vector<uint32_t> GetElements() const;

    private:
        Graphics::VertexAttributeConfig _attributesTemplate;
        std::vector<Graphics::Mesh::VertexData> _vertexData;
        std::vector<uint32_t> _elements;
    };

    inline std::vector<Graphics::Mesh::VertexData> Graphics::TerrainGenerator::GetVertexData() const
    {
        return this->_vertexData;
    }

    inline std::vector<uint32_t> Graphics::TerrainGenerator::GetElements() const
    {
        return this->_elements;
    }

}
