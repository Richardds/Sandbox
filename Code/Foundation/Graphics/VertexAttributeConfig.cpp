// ----------------------------------------------------------------------------------------
//  \file       VertexAttributeConfig.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/VertexAttributeConfig.h"
#include "Core/Debug.h"

Graphics::VertexAttributeConfig::VertexAttributeConfig() :
	_size(0)
{
}

void Graphics::VertexAttributeConfig::Append(const GLenum type, const uint16_t count)
{
	size_t elementSize = 0;

	switch (type)
	{
	case GL_FLOAT:
		elementSize = sizeof(float);
		break;
	case GL_UNSIGNED_INT:
		elementSize = sizeof(GLuint);
		break;
	case GL_INT:
		elementSize = sizeof(GLint);
		break;
	}

	_Assert(0 < elementSize);

	const size_t attributeSize = count * elementSize;
	VertexAttribute attribute = {type, count, attributeSize};
	this->_attributes.emplace_back(attribute);
	this->_size += attributeSize;
}

void Graphics::VertexAttributeConfig::Apply(const std::shared_ptr<VertexArray>& vao) const
{
	_Assert(vao);
	_Assert(vao->IsBound());

	size_t pointer = 0;
	uint16_t count = 0;

	for (const auto& attribute : this->_attributes)
	{
		glVertexAttribPointer(count, attribute.count, attribute.type, GL_FALSE, static_cast<GLsizei>(this->_size),
		                      reinterpret_cast<const void*>(pointer));
		glEnableVertexAttribArray(count);

		pointer += attribute.size;
		count++;
	}
}
