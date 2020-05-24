#include <Precompiled.h>
#include <Core/Types.h>
#include <Exporters/AssimpExporter.h>
#include <Util/FourCC.h>
#include <Util/ResourcesLoader.h>

#include "IO/Console.h"

Util::AssimpExporter::AssimpExporter() :
	_scene(nullptr)
{
}

bool Util::AssimpExporter::Load(const std::vector<char>& buffer)
{
	this->_scene = this->_importer.ReadFileFromMemory(buffer.data(), buffer.size(),
		aiProcess_Triangulate
		| aiProcess_FlipUVs
		| aiProcess_CalcTangentSpace
		| aiProcess_GenNormals
		| aiProcess_JoinIdenticalVertices
		| aiProcess_FixInfacingNormals
		| aiProcess_FindInvalidData
		| aiProcess_FindDegenerates
		| aiProcess_RemoveRedundantMaterials
		| aiProcess_ImproveCacheLocality
		| aiProcess_OptimizeMeshes
		| aiProcess_OptimizeGraph
		| aiProcess_ValidateDataStructure
	);

	if (!this->_scene || this->_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->_scene->mRootNode)
	{
		return false;
	}

	return true;
}

void Util::AssimpExporter::Export(std::ofstream& outputFile) const
{
	this->Write(outputFile, Util::FourCC("MODL"));
	this->WriteNode(outputFile, this->_scene->mRootNode);
}

void Util::AssimpExporter::WriteString(std::ofstream& outputFile, const std::string& string) const
{
	this->Write(outputFile, static_cast<uint16_t>(string.size()));
	outputFile.write(string.c_str(), string.size());
}

void Util::AssimpExporter::WriteNode(std::ofstream& file, aiNode* node) const
 {
	const uint16_t meshesCount = node->mNumMeshes;

	if (meshesCount > 0)
	{
		this->Write(file, meshesCount);

		for (uint16_t i = 0; i < meshesCount; i++)
		{
			aiMesh* mesh = this->_scene->mMeshes[node->mMeshes[i]];
			this->WriteMesh(file, mesh);
		}
	}
	
	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		this->WriteNode(file, node->mChildren[i]);
	}
}

void Util::AssimpExporter::WriteMaterial(std::ofstream& file, aiMaterial* material) const
{
	aiColor3D assimpColor;
	material->Get(AI_MATKEY_COLOR_DIFFUSE, assimpColor);
	this->Write(file, Math::Vector3f(assimpColor.r, assimpColor.g, assimpColor.b));

	float specular;
	material->Get(AI_MATKEY_SHININESS_STRENGTH, specular);
	this->Write(file, specular);

	float shininess;
	material->Get(AI_MATKEY_SHININESS, shininess);
	this->Write(file, shininess);
}

void Util::AssimpExporter::WriteMesh(std::ofstream& file, aiMesh* mesh) const
{
	// Write name
	this->WriteString(file, mesh->mName.C_Str());

	// Write vertices count
	const uint32_t verticesCount = mesh->mNumVertices;
	this->Write(file, verticesCount);

	for (uint32_t i = 0; i < verticesCount; i++)
	{
		VertexData3 vertexData = {};
		vertexData.vertex.x = mesh->mVertices[i].x;
		vertexData.vertex.y = mesh->mVertices[i].y;
		vertexData.vertex.z = mesh->mVertices[i].z;

		vertexData.normal.x = mesh->mNormals[i].x;
		vertexData.normal.y = mesh->mNormals[i].y;
		vertexData.normal.z = mesh->mNormals[i].z;

		vertexData.texture.x = mesh->mTextureCoords[0][i].x;
		vertexData.texture.y = mesh->mTextureCoords[0][i].y;

		vertexData.tangent.x = mesh->mTangents[i].x;
		vertexData.tangent.y = mesh->mTangents[i].y;
		vertexData.tangent.z = mesh->mTangents[i].z;

		// Print vertex data
		//IO::Console::Instance().Info(
		//	"{%ff,%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff},\n",
		//	vertexData.vertex.x, vertexData.vertex.y, vertexData.vertex.z,
		//	vertexData.normal.x, vertexData.normal.y, vertexData.normal.z,
		//	vertexData.texture.x, vertexData.texture.y,
		//	vertexData.tangent.x, vertexData.tangent.y, vertexData.tangent.z
		//);
		
		// Write vertex attributes
		this->Write(file, vertexData);
	}

	const uint32_t trianglesCount = mesh->mNumFaces;
	this->Write(file, trianglesCount);
	
	for (uint32_t i = 0; i < trianglesCount; i++)
	{
		const aiFace face = mesh->mFaces[i];
		_Assert(3 == face.mNumIndices);
		for (uint32_t j = 0; j < 3; j++)
		{
			// Write vertex index
			const uint32_t index = face.mIndices[j];
			this->Write(file, index);
		}

		// Print indices
		//IO::Console::Instance().Info("%u, %u, %u,\n", face.mIndices[0], face.mIndices[1], face.mIndices[2]);
	}

	// Write material
	aiMaterial* material = this->_scene->mMaterials[mesh->mMaterialIndex];
	this->WriteMaterial(file, this->_scene->mMaterials[mesh->mMaterialIndex]);

	uint8_t textureBitfield = 0;
	textureBitfield |= HAS_TEXTURE_DIFFUSE * (1 == material->GetTextureCount(aiTextureType_DIFFUSE));
	textureBitfield |= HAS_TEXTURE_NORMALS * (1 == material->GetTextureCount(aiTextureType_NORMALS));
	textureBitfield |= HAS_TEXTURE_SPECULAR * (1 == material->GetTextureCount(aiTextureType_SPECULAR));

	// Write texture bitfield
	this->Write(file, textureBitfield);
	
	aiString assetPath;

	// Write diffuse texture name
	if (HAS_TEXTURE_DIFFUSE & textureBitfield)
	{
		material->GetTexture(aiTextureType_DIFFUSE, 0, &assetPath);
		this->WriteString(file, this->ParseAssetName(assetPath));
	}

	// Write normals mapping name
	if (HAS_TEXTURE_NORMALS & textureBitfield)
	{
		material->GetTexture(aiTextureType_NORMALS, 0, &assetPath);
		this->WriteString(file, this->ParseAssetName(assetPath));
	}

	// Write specular mapping name
	if (HAS_TEXTURE_SPECULAR & textureBitfield)
	{
		material->GetTexture(aiTextureType_SPECULAR, 0, &assetPath);
		this->WriteString(file, this->ParseAssetName(assetPath));
	}
}

std::string Util::AssimpExporter::ParseAssetName(const aiString& assetPath) const
{
	const std::string pathStr(assetPath.C_Str());
	const size_t extIndex = pathStr.find_last_of('.');
	return pathStr.substr(0, extIndex);
}
