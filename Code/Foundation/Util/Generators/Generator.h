// ----------------------------------------------------------------------------------------
//  \file       Generator.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/Mesh.h"
#include "Graphics/VertexAttributeConfig.h"

namespace Util
{
    /// Base class for every mesh generator
    class EXPORT Generator
    {
    public:
        Generator() = default;
        virtual ~Generator() = default;

    protected:
        template <typename T>
        std::shared_ptr<Graphics::Mesh> Store(const std::vector<T>& vertices,
                                              const std::vector<uint32_t>& indices,
                                              const Graphics::VertexAttributeConfig& config) const;
    };

    template <typename T>
    std::shared_ptr<Graphics::Mesh> Generator::Store(const std::vector<T>& vertices,
                                                     const std::vector<uint32_t>& indices,
                                                     const Graphics::VertexAttributeConfig& config) const
    {
        std::shared_ptr<Graphics::VertexArray> vao = std::make_shared<Graphics::VertexArray>();
        vao->Bind();

        std::shared_ptr<Graphics::Buffer> ebo = std::make_shared<Graphics::Buffer>(GL_ELEMENT_ARRAY_BUFFER);
        ebo->Bind();
        ebo->Data(indices);

        std::shared_ptr<Graphics::Buffer> vbo = std::make_shared<Graphics::Buffer>(GL_ARRAY_BUFFER);
        vbo->Bind();
        vbo->Data(vertices);

        config.Apply(vao);

        vao->Unbind();
        ebo->Unbind();
        vbo->Unbind();

        return std::make_shared<Graphics::Mesh>(vao, vbo, ebo, static_cast<uint32_t>(indices.size()));
    }
}
