#include "VertexAttributeConfig.h"

Graphics::VertexAttributeConfig::VertexAttributeConfig() :
	_size(0)
{
}

Graphics::VertexAttributeConfig::~VertexAttributeConfig()
{
}

void Graphics::VertexAttributeConfig::Append(GLenum type, uint16_t count, size_t elementSize)
{
	size_t attributeSize = count * elementSize;
	VertexAttribute attribute = { type, count, attributeSize };
	this->_attributes.emplace_back(attribute);
	this->_size += attributeSize;
}

void Graphics::VertexAttributeConfig::Apply(std::shared_ptr<VertexArray> vao)
{
	_assert(vao);
	_assert(vao->IsBound());

	size_t pointer = 0;
	uint16_t count = 0;

	for (const auto& attribute : this->_attributes) {
		glVertexAttribPointer(count, attribute.count, attribute.type, GL_FALSE, static_cast<GLsizei>(this->_size), (const void*)pointer);
		glEnableVertexAttribArray(count);

		pointer += attribute.size;
		count++;
	}
}
