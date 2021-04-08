// ----------------------------------------------------------------------------------------
//  \file       AssimpExporter.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <Precompiled.h>
#include <Core/Types.h>
#include <Exporters/AssimpExporter.h>
#include <Util/FourCC.h>
#include <Util/ResourcesLoader.h>

Util::AssimpExporter::AssimpExporter() :
    _scene(nullptr)
{
}

bool Util::AssimpExporter::Load(const std::vector<char>& buffer)
{
    this->_scene = this->_importer.ReadFileFromMemory(buffer.data(), buffer.size(),
                                                      aiProcess_Triangulate
                                                      | aiProcess_SortByPType
                                                      | aiProcess_FlipUVs
                                                      | aiProcess_CalcTangentSpace
                                                      | aiProcess_GenSmoothNormals
                                                      | aiProcess_GenUVCoords
                                                      | aiProcess_JoinIdenticalVertices
                                                      | aiProcess_SplitLargeMeshes
                                                      | aiProcess_FixInfacingNormals
                                                      | aiProcess_FindInvalidData
                                                      | aiProcess_FindDegenerates
                                                      | aiProcess_RemoveRedundantMaterials
                                                      | aiProcess_ImproveCacheLocality
                                                      | aiProcess_OptimizeMeshes
                                                      | aiProcess_OptimizeGraph
                                                      | aiProcess_FindInstances
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

            // Skip the mesh if does not contain any triangles
            if (mesh->mPrimitiveTypes & aiPrimitiveType_TRIANGLE)
            {
                this->WriteMesh(file, mesh);
            }
        }

        return;
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

    float reflectivity;
    material->Get(AI_MATKEY_REFLECTIVITY, reflectivity);
    this->Write(file, reflectivity);

    float specular;
    material->Get(AI_MATKEY_SHININESS_STRENGTH, specular);
    this->Write(file, specular);

    float shininess;
    material->Get(AI_MATKEY_SHININESS, shininess);
    this->Write(file, shininess);

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

void Util::AssimpExporter::WriteMesh(std::ofstream& file, aiMesh* mesh) const
{
    // Write name
    this->WriteString(file, mesh->mName.C_Str());

    // Write vertices count
    const uint32_t verticesCount = mesh->mNumVertices;
    this->Write(file, verticesCount);

    // Write vertices
    if (mesh->mTextureCoords[0] == nullptr || mesh->mTangents == nullptr)
    {
        for (uint32_t i = 0; i < verticesCount; i++)
        {
            const aiVector3D* position = &mesh->mVertices[i];
            const aiVector3D* normal = &mesh->mNormals[i];

            Graphics::VertexData3 vertex{};
            vertex.vertex = Math::Vector3f(position->x, position->y, position->z);
            vertex.normal = Math::Vector3f(normal->x, normal->y, normal->z);
            
            // Write vertex attributes
            this->Write(file, vertex);
        }
    } else
    {
        for (uint32_t i = 0; i < verticesCount; i++)
        {
            const aiVector3D* position = &mesh->mVertices[i];
            const aiVector3D* normal = &mesh->mNormals[i];
            const aiVector3D* texture = &mesh->mTextureCoords[0][i];
            const aiVector3D* tangent = &mesh->mTangents[i];

            const Graphics::VertexData3 vertex(
                position->x, position->y, position->z,
                normal->x, normal->y, normal->z,
                texture->x, texture->y,
                tangent->x, tangent->y, tangent->z
            );
            
            // Write vertex attributes
            this->Write(file, vertex);
        }
    }

    // Write triangles count
    const uint32_t trianglesCount = mesh->mNumFaces;
    this->Write(file, trianglesCount);

    // Write triangles
    for (uint32_t i = 0; i < trianglesCount; i++)
    {
        const aiFace face = mesh->mFaces[i];

        // Process triangles only
        if (face.mNumIndices == 3)
        {
            this->Write(file, Math::Vector3ui32(face.mIndices[0], face.mIndices[1], face.mIndices[2]));
        }
    }

    // Write material
    aiMaterial* material = this->_scene->mMaterials[mesh->mMaterialIndex];
    this->WriteMaterial(file, material);
}

std::string Util::AssimpExporter::ParseAssetName(const aiString& assetPath) const
{
    const std::string pathStr(assetPath.C_Str());
    const size_t extIndex = pathStr.find_last_of('.');
    return pathStr.substr(0, extIndex);
}
