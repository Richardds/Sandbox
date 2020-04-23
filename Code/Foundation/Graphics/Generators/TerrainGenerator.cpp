#include "TerrainGenerator.h"
#include "../../Graphics/Buffer.h"
#include "../../Util/ResourcesLoader.h"

Graphics::TerrainGenerator::TerrainGenerator()
{
    this->_attributesTemplate.Append(GL_FLOAT, 3, sizeof(float));
    this->_attributesTemplate.Append(GL_FLOAT, 3, sizeof(float));
    this->_attributesTemplate.Append(GL_FLOAT, 2, sizeof(float));
}

Graphics::TerrainGenerator::~TerrainGenerator()
{
}

void Graphics::TerrainGenerator::Generate(float size)
{
	float radius = size / 2.0f;

	this->_vertexData.assign({
        {Math::Vector3f(-radius, 0.0f, radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(0.0f, 0.0f)},
        {Math::Vector3f(radius, 0.0f, radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(0.0f, 1.0f)},
        {Math::Vector3f(radius, 0.0f, -radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(1.0f, 1.0f)},
        {Math::Vector3f(-radius, 0.0f, -radius), Math::Vector3f(0.0f, 1.0f, 0.0f), Math::Vector2f(1.0f, 0.0f)}
	});

	this->_elements.assign({
		0, 1, 2,
		0, 2, 3
	});
}

std::shared_ptr<Graphics::Mesh> Graphics::TerrainGenerator::Store()
{
    std::shared_ptr<Graphics::VertexArray> vao = std::make_shared<Graphics::VertexArray>();
    vao->Bind();

    std::shared_ptr<Graphics::Buffer> ebo = std::make_shared<Graphics::Buffer>(GL_ELEMENT_ARRAY_BUFFER);
    ebo->Bind();
    ebo->Data(this->_elements);

    std::shared_ptr<Graphics::Buffer> vbo = std::make_shared<Graphics::Buffer>(GL_ARRAY_BUFFER);
    vbo->Bind();
    vbo->Data(this->_vertexData);

    this->_attributesTemplate.Apply(vao);

    vao->Unbind();
    ebo->Unbind();
    vbo->Unbind();

    return std::make_shared<Graphics::Mesh>(vao, vbo, ebo, static_cast<uint32_t>(this->_elements.size()));
}
