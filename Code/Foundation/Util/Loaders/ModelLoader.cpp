// ----------------------------------------------------------------------------------------
//  \file       ModelLoader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Loaders/ModelLoader.h"
#include "Core/Types.h"
#include "IO/Console.h"
#include "Math/Vector.h"
#include "Util/FourCC.h"
#include "Util/ResourcesLoader.h"

Util::ModelLoader::ModelLoader()
{
	this->_attributesTemplate.Append(GL_FLOAT, 3);
	this->_attributesTemplate.Append(GL_FLOAT, 3);
	this->_attributesTemplate.Append(GL_FLOAT, 2);
	this->_attributesTemplate.Append(GL_FLOAT, 3);
}

std::shared_ptr<Graphics::Model> Util::ModelLoader::Load(std::ifstream& file)
{
	FourCC magic;
	this->Read(file, &magic);

	if (magic != FourCC("MODL"))
	{
		throw std::runtime_error("Model file signature mismatch");
	}

	this->_model = std::make_shared<Graphics::Model>();

	this->ParseFile(file);

	this->_model->FinishLoading();

	return _model;
}

std::string Util::ModelLoader::ReadString(std::ifstream& file) const
{
	uint16_t length;
	this->Read(file, &length);

	char* stringBuffer = new char[static_cast<size_t>(length) + 1];
	file.read(stringBuffer, length);
	stringBuffer[length] = '\0';

	std::string string(stringBuffer, length);

	delete[] stringBuffer;

	return string;
}

void Util::ModelLoader::ParseFile(std::ifstream& file) const
{
	uint16_t meshesCount;
	this->Read(file, &meshesCount);

	for (uint16_t i = 0; i < meshesCount; i++)
	{
		const std::string meshName = this->ReadString(file);
		IO::Console::Instance().Info("-> Mesh '%s'\n", meshName.c_str());
		this->_model->AddMesh(meshName, this->ParseMesh(file));
	}
}

std::shared_ptr<Graphics::Material> Util::ModelLoader::ParseMaterial(std::ifstream& file) const
{
	Math::Vector3f color;
	this->Read(file, &color);

	float specular;
	this->Read(file, &specular);

	float shininess;
	this->Read(file, &shininess);

	return std::make_shared<Graphics::Material>(color, specular, shininess);
}

std::shared_ptr<Graphics::TexturedMesh> Util::ModelLoader::ParseMesh(std::ifstream& file) const
{
	std::vector<VertexData3> data;
	std::vector<Math::Vector3ui32> elements;

	uint32_t verticesCount;
	this->Read(file, &verticesCount);

	data.reserve(verticesCount);

	for (uint32_t i = 0; i < verticesCount; i++)
	{
		VertexData3 vertexData = {};
		this->Read(file, &vertexData);
		data.push_back(vertexData);
	}

	uint32_t trianglesCount;
	this->Read(file, &trianglesCount);

	elements.reserve(3 * static_cast<size_t>(trianglesCount));

	for (uint32_t i = 0; i < trianglesCount; i++)
	{
		Math::Vector3ui32 triangleIndexes;
		this->Read(file, &triangleIndexes);
		elements.emplace_back(triangleIndexes);
	}

	std::shared_ptr<Graphics::VertexArray> vao = std::make_shared<Graphics::VertexArray>();
	vao->Bind();

	std::shared_ptr<Graphics::Buffer> ebo = std::make_shared<Graphics::Buffer>(GL_ELEMENT_ARRAY_BUFFER);
	ebo->Bind();
	ebo->Data(elements);

	std::shared_ptr<Graphics::Buffer> vbo = std::make_shared<Graphics::Buffer>(GL_ARRAY_BUFFER);
	vbo->Bind();
	vbo->Data(data);

	this->_attributesTemplate.Apply(vao);

	vao->Unbind();
	ebo->Unbind();
	vbo->Unbind();

	std::shared_ptr<Graphics::TexturedMesh> texturedMesh = std::make_shared<Graphics::TexturedMesh>(
		vao, vbo, ebo, static_cast<uint32_t>(3 * elements.size()));

	// Load model material
	std::shared_ptr<Graphics::Material> material = this->ParseMaterial(file);
	texturedMesh->SetMaterial(*material);

	// Load model textures
	uint8_t textureBitfield;
	this->Read(file, &textureBitfield);

	std::string textureName;

	if (HAS_TEXTURE_DIFFUSE & textureBitfield)
	{
		textureName = this->ReadString(file);
		std::shared_ptr<Graphics::Texture> texture = ResourcesLoader::Instance().LoadTexture(textureName);
		texturedMesh->SetDiffuseMap(texture);
	}

	if (HAS_TEXTURE_NORMALS & textureBitfield)
	{
		textureName = this->ReadString(file);
		std::shared_ptr<Graphics::Texture> texture = ResourcesLoader::Instance().LoadTexture(textureName);
		texturedMesh->SetNormalMap(texture);
	}

	if (HAS_TEXTURE_SPECULAR & textureBitfield)
	{
		textureName = this->ReadString(file);
		std::shared_ptr<Graphics::Texture> texture = ResourcesLoader::Instance().LoadTexture(textureName);
		texturedMesh->SetSpecularMap(texture);
	}

	return texturedMesh;
}
