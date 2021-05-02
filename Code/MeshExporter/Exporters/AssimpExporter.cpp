// ----------------------------------------------------------------------------------------
//  \file       AssimpExporter.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <Core/Types.h>
#include <Util/FourCC.h>
#include <Util/ResourcesLoader.h>

#include "Exporters/AssimpExporter.h"

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

void Util::AssimpExporter::Export(IO::OutputFile& outputFile) const
{
    outputFile.Write(FourCC("MODL"));
    this->WriteNode(outputFile, this->_scene->mRootNode);
}

std::string Util::AssimpExporter::ParseAssetName(const aiString& assetPath)
{
    const std::string pathStr(assetPath.C_Str());
    const size_t extIndex = pathStr.find_last_of('.');
    return pathStr.substr(0, extIndex);
}

void Util::AssimpExporter::WriteNode(IO::OutputFile& file, const aiNode* node) const
{
    const unsigned int meshesCount = node->mNumMeshes;
    unsigned int validMeshesCount = meshesCount;

    // Decrease the counter to valid mesh count
    for (unsigned int i = 0; i < meshesCount; i++)
    {
        // Skip the mesh if does not contain any triangles
        if (aiPrimitiveType_TRIANGLE != this->_scene->mMeshes[node->mMeshes[i]]->mPrimitiveTypes)
        {
            validMeshesCount--;
        }
    }

    _Assert(65535 >= validMeshesCount)

    file.Write(static_cast<uint16_t>(validMeshesCount));

    if (meshesCount > 0)
    {
        for (unsigned int i = 0; i < meshesCount; i++)
        {
            const aiMesh* mesh = this->_scene->mMeshes[node->mMeshes[i]];

            // Skip the mesh if does not contain any triangles
            if (aiPrimitiveType_TRIANGLE == mesh->mPrimitiveTypes)
            {
                this->WriteMesh(file, mesh);
            }
        }
    }

    // Nested graph not supported
    //for (unsigned int i = 0; i < node->mNumChildren; i++)
    //{
    //    this->WriteNode(file, node->mChildren[i]);
    //}
}

void Util::AssimpExporter::WriteMaterial(IO::OutputFile& file, const aiMaterial* material) const
{
    aiColor3D assimpColor;
    material->Get(AI_MATKEY_COLOR_DIFFUSE, assimpColor);
    file.Write(Math::Vector3f(assimpColor.r, assimpColor.g, assimpColor.b));

    float reflectivity;
    material->Get(AI_MATKEY_REFLECTIVITY, reflectivity);
    file.Write(reflectivity);

    float specular;
    material->Get(AI_MATKEY_SHININESS_STRENGTH, specular);
    file.Write(specular);

    float shininess;
    material->Get(AI_MATKEY_SHININESS, shininess);
    file.Write(shininess);

    uint8_t textureBitfield = 0;
    textureBitfield |= HAS_TEXTURE_DIFFUSE * (1 == material->GetTextureCount(aiTextureType_DIFFUSE));
    textureBitfield |= HAS_TEXTURE_NORMALS * (1 == material->GetTextureCount(aiTextureType_NORMALS));
    textureBitfield |= HAS_TEXTURE_SPECULAR * (1 == material->GetTextureCount(aiTextureType_SPECULAR));

    // Write texture bitfield
    file.Write(textureBitfield);

    aiString assetPath;

    // Write diffuse texture name
    if (HAS_TEXTURE_DIFFUSE & textureBitfield)
    {
        material->GetTexture(aiTextureType_DIFFUSE, 0, &assetPath);
        file.Write(this->ParseAssetName(assetPath));
    }

    // Write normals mapping name
    if (HAS_TEXTURE_NORMALS & textureBitfield)
    {
        material->GetTexture(aiTextureType_NORMALS, 0, &assetPath);
        file.Write(this->ParseAssetName(assetPath));
    }

    // Write specular mapping name
    if (HAS_TEXTURE_SPECULAR & textureBitfield)
    {
        material->GetTexture(aiTextureType_SPECULAR, 0, &assetPath);
        file.Write(this->ParseAssetName(assetPath));
    }
}

void Util::AssimpExporter::WriteMesh(IO::OutputFile& file, const aiMesh* mesh) const
{
    // Write name
    file.Write(std::string(mesh->mName.C_Str()));

    // Write vertices count
    const unsigned int verticesCount = mesh->mNumVertices;
    file.Write(static_cast<uint32_t>(verticesCount));

    // Write vertices
    if (mesh->mTextureCoords[0] == nullptr || mesh->mTangents == nullptr)
    {
        for (unsigned int i = 0; i < verticesCount; i++)
        {
            const aiVector3D* position = &mesh->mVertices[i];
            const aiVector3D* normal = &mesh->mNormals[i];

            Graphics::VertexData3 vertex{};
            vertex.vertex = Math::Vector3f(position->x, position->y, position->z);
            vertex.normal = Math::Vector3f(normal->x, normal->y, normal->z);
            
            // Write vertex attributes
            file.Write(vertex);
        }
    } else
    {
        for (unsigned int i = 0; i < verticesCount; i++)
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
            file.Write(vertex);
        }
    }

    // Write triangles count
    const unsigned int trianglesCount = mesh->mNumFaces;
    file.Write(static_cast<uint32_t>(trianglesCount));

    // Write triangles
    for (unsigned int i = 0; i < trianglesCount; i++)
    {
        const aiFace face = mesh->mFaces[i];

        // Process triangles only
        if (face.mNumIndices == 3)
        {
            file.Write(Math::Vector3ui32(face.mIndices[0], face.mIndices[1], face.mIndices[2]));
        }
    }

    // Write material
    const aiMaterial* material = this->_scene->mMaterials[mesh->mMaterialIndex];
    this->WriteMaterial(file, material);
}
