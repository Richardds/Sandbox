#pragma once

#include "Precompiled.h"
#include "Graphics/Mesh.h"
#include "Graphics/VertexAttributeConfig.h"

namespace Util
{
	class Generator
	{

	public:
		Generator() = default;

	protected:
		template <typename T>
		std::shared_ptr<Graphics::Mesh> Store(const std::vector<T>& vertexData,
											  const std::vector<uint32_t>& elements,
		                                      const Graphics::VertexAttributeConfig& config);
	};

	template <typename T>
	std::shared_ptr<Graphics::Mesh> Generator::Store(const std::vector<T>& vertexData,
	                                                 const std::vector<uint32_t>& elements,
	                                                 const Graphics::VertexAttributeConfig& config)
	{
		std::shared_ptr<Graphics::VertexArray> vao = std::make_shared<Graphics::VertexArray>();
		vao->Bind();

		std::shared_ptr<Graphics::Buffer> ebo = std::make_shared<Graphics::Buffer>(GL_ELEMENT_ARRAY_BUFFER);
		ebo->Bind();
		ebo->Data(elements);

		std::shared_ptr<Graphics::Buffer> vbo = std::make_shared<Graphics::Buffer>(GL_ARRAY_BUFFER);
		vbo->Bind();
		vbo->Data(vertexData);

		config.Apply(vao);

		vao->Unbind();
		ebo->Unbind();
		vbo->Unbind();

		return std::make_shared<Graphics::Mesh>(vao, vbo, ebo, static_cast<uint32_t>(elements.size()));
	}
}
