// ----------------------------------------------------------------------------------------
//  \file       TexturedMesh.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/TexturedMesh.h"

Graphics::TexturedMesh::TexturedMesh(std::shared_ptr<VertexArray> vertexArrayObject,
                                     std::shared_ptr<Buffer> vertexBuffer,
                                     std::shared_ptr<Buffer> elementsBuffer,
                                     const uint32_t elementsCount) :
	Mesh(std::move(vertexArrayObject), std::move(vertexBuffer), std::move(elementsBuffer), elementsCount),
	_material(Math::Vector3f(0.85f), 0.0f, 0.5f, 25.0f)
{
}

Graphics::TexturedMesh::TexturedMesh(const std::shared_ptr<Mesh>& mesh) :
	TexturedMesh(mesh->GetVertexArray(), mesh->GetVertexBuffer(), mesh->GetElementBuffer(), mesh->GetElementsCount())
{
}

void Graphics::TexturedMesh::Render(const std::shared_ptr<EntityShader>& shader) const
{
	shader->LoadMaterial(this->_material);

	const bool hasDiffuseMap = this->HasDiffuseMap();
	shader->LoadHasDiffuseMap(hasDiffuseMap);
	if (hasDiffuseMap)
	{
		this->_diffuseMap->Activate(Texture::Bank::Diffuse);
	}

	const bool hasNormalMap = this->HasNormalMap();
	shader->LoadHasNormalMap(hasNormalMap);
	if (hasNormalMap)
	{
		this->_normalMap->Activate(Texture::Bank::Normal);
	}

	const bool hasSpecularMap = this->HasSpecularMap();
	shader->LoadHasSpecularMap(hasSpecularMap);
	if (hasSpecularMap)
	{
		this->_specularMap->Activate(Texture::Bank::Specular);
	}

	DrawElements();
}
