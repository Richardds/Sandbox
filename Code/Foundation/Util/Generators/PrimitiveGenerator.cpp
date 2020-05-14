#include <vector>

#include "PrimitiveGenerator.h"
#include "../../Graphics/Buffer.h"

Util::PrimitiveGenerator::PrimitiveGenerator()
{
    this->_2dAttributesTemplate.Append(GL_FLOAT, 3);
    this->_2dAttributesTemplate.Append(GL_FLOAT, 2);

    this->_3dAttributesTemplate.Append(GL_FLOAT, 3);
    this->_3dAttributesTemplate.Append(GL_FLOAT, 3);
    this->_3dAttributesTemplate.Append(GL_FLOAT, 2);
    this->_3dAttributesTemplate.Append(GL_FLOAT, 3);
}

Util::PrimitiveGenerator::~PrimitiveGenerator()
{
}

std::shared_ptr<Graphics::Mesh> Util::PrimitiveGenerator::Generate2dQuad(float size)
{
    float radius = size / 2.0f;

    std::vector<VertexData2> vertexData({
        {Math::Vector3f(-radius, -radius, 0.0f), Math::Vector2f(0.0f, 0.0f)},
        {Math::Vector3f(radius, -radius, 0.0f), Math::Vector2f(1.0f, 0.0f)},
        {Math::Vector3f(radius, radius, 0.0f), Math::Vector2f(1.0f, 1.0f)},
        {Math::Vector3f(-radius, radius, 0.0f), Math::Vector2f(0.0f, 1.0f)}
    });

    std::vector<uint32_t> elements({
        0, 1, 3,
        1, 2, 3
    });

    return this->Store(vertexData, elements, this->_2dAttributesTemplate);
}

std::shared_ptr<Graphics::Mesh> Util::PrimitiveGenerator::Generate3dQuad(float size)
{
    float radius = size / 2.0f;

    std::vector<VertexData3> vertexData({
        {Math::Vector3f(-radius, -radius, 0.0f), Math::Vector3f(0.0f, 0.0f, 1.0f), Math::Vector2f(0.0f, 0.0f), Math::Vector3f(0.0f, 0.0f, 1.0f)},
        {Math::Vector3f(radius, -radius, 0.0f), Math::Vector3f(0.0f, 0.0f, 1.0f), Math::Vector2f(1.0f, 0.0f), Math::Vector3f(0.0f, 0.0f, 1.0f)},
        {Math::Vector3f(radius, radius, 0.0f), Math::Vector3f(0.0f, 0.0f, 1.0f), Math::Vector2f(1.0f, 1.0f), Math::Vector3f(0.0f, 0.0f, 1.0f)},
        {Math::Vector3f(-radius, radius, 0.0f), Math::Vector3f(0.0f, 0.0f, 1.0f), Math::Vector2f(0.0f, 1.0f), Math::Vector3f(0.0f, 0.0f, 1.0f)}
    });

    std::vector<uint32_t> elements({
        0, 1, 3,
        1, 2, 3
    });

    return this->Store(vertexData, elements, this->_3dAttributesTemplate);
}
