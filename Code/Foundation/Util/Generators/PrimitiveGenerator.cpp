#include <vector>

#include "PrimitiveGenerator.h"

Util::PrimitiveGenerator::PrimitiveGenerator()
{
	this->_2dQuadAttributesTemplate.Append(GL_FLOAT, 3);
	this->_2dQuadAttributesTemplate.Append(GL_FLOAT, 2);

	this->_3dQuadAttributesTemplate.Append(GL_FLOAT, 3);
	this->_3dQuadAttributesTemplate.Append(GL_FLOAT, 3);
	this->_3dQuadAttributesTemplate.Append(GL_FLOAT, 2);
	this->_3dQuadAttributesTemplate.Append(GL_FLOAT, 3);
}

std::shared_ptr<Graphics::Mesh> Util::PrimitiveGenerator::Generate2dQuad(const float size)
{
	const float radius = size / 2.0f;

	const std::vector<VertexData2> vertexData({
		{Math::Vector3f(-radius, -radius, 0.0f), Math::Vector2f(0.0f, 0.0f)},
		{Math::Vector3f(radius, -radius, 0.0f), Math::Vector2f(1.0f, 0.0f)},
		{Math::Vector3f(radius, radius, 0.0f), Math::Vector2f(1.0f, 1.0f)},
		{Math::Vector3f(-radius, radius, 0.0f), Math::Vector2f(0.0f, 1.0f)}
	});

	const std::vector<uint32_t> elements({
		0, 1, 3,
		1, 2, 3
	});

	return this->Store(vertexData, elements, this->_2dQuadAttributesTemplate);
}

std::shared_ptr<Graphics::Mesh> Util::PrimitiveGenerator::Generate3dQuad(const float size)
{
	const float radius = size / 2.0f;

	const std::vector<VertexData3> vertexData({
		{
			Math::Vector3f(-radius, 0.0f, radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(0.0f, 1.0f),
			Math::Vector3f(-1.0f, 0.0f, 0.0f)
		},
		{
			Math::Vector3f(radius, 0.0f, radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(1.0f, 1.0f),
			Math::Vector3f(-1.0f, 0.0f, 0.0f)
		},
		{
			Math::Vector3f(radius, 0.0f, -radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(1.0f, 0.0f),
			Math::Vector3f(-1.0f, 0.0f, 0.0f)
		},
		{
			Math::Vector3f(-radius, 0.0f, -radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(0.0f, 0.0f),
			Math::Vector3f(-1.0f, 0.0f, 0.0f)
		}
	});

	const std::vector<uint32_t> elements({
		0, 1, 3,
		1, 2, 3
	});

	return this->Store(vertexData, elements, this->_3dQuadAttributesTemplate);
}
