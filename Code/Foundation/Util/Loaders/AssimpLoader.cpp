// ----------------------------------------------------------------------------------------
//  \file       AssimpLoader.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Loaders/AssimpLoader.h"
#include "Core/Types.h"
#include "IO/Console.h"
#include "Util/ResourcesLoader.h"

Util::AssimpLoader::AssimpLoader() :
    _scene(nullptr),
    _nodeCount(0),
    _meshCount(0)
{
    this->_attributesTemplate.Append(GL_FLOAT, 3);
    this->_attributesTemplate.Append(GL_FLOAT, 3);
    this->_attributesTemplate.Append(GL_FLOAT, 2);
    this->_attributesTemplate.Append(GL_FLOAT, 3);
}

std::shared_ptr<Graphics::Model> Util::AssimpLoader::Load(const std::vector<char>& buffer)
{
    this->_model = std::make_shared<Graphics::Model>();

    Assimp::Importer importer;

    this->_scene = importer.ReadFileFromMemory(buffer.data(), buffer.size(),
                                               aiProcess_FlipUVs
                                               | aiProcess_Triangulate
                                               | aiProcess_CalcTangentSpace
                                               | aiProcess_FixInfacingNormals
                                               | aiProcess_FindInvalidData
    );

    if (!this->_scene || this->_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->_scene->mRootNode)
    {
        IO::Console::Instance().Error("Failed to parse model\n");
        return this->_model;
    }

    this->ProcessNode(this->_scene->mRootNode);

    this->_model->FinishLoading();

    return this->_model;
}

void Util::AssimpLoader::ProcessNode(aiNode* node)
{
    this->_nodeCount++;

    for (uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = this->_scene->mMeshes[node->mMeshes[i]];
        IO::Console::Instance().Info("-> Mesh '%s'\n", mesh->mName.C_Str());
        this->_model->AddMesh(mesh->mName.C_Str(), this->ProcessMesh(mesh));
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++)
    {
        this->ProcessNode(node->mChildren[i]);
    }
}

std::shared_ptr<Graphics::TexturedMesh> Util::AssimpLoader::ProcessMesh(aiMesh* mesh)
{
    std::vector<Graphics::VertexData3> data;
    std::vector<Math::Vector3ui32> indices;

    this->_meshCount++;

    data.reserve(mesh->mNumVertices);

    for (uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        data.emplace_back(
            mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z,
            mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z,
            mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y,
            mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z
        );
    }

    indices.reserve(mesh->mNumFaces);

    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace face = mesh->mFaces[i];
        _Assert(3 == face.mNumIndices);
        indices.emplace_back(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
    }

    std::shared_ptr<Graphics::VertexArray> vao = std::make_shared<Graphics::VertexArray>();
    vao->Bind();

    std::shared_ptr<Graphics::Buffer> ebo = std::make_shared<Graphics::Buffer>(GL_ELEMENT_ARRAY_BUFFER);
    ebo->Bind();
    ebo->Data(indices);

    std::shared_ptr<Graphics::Buffer> vbo = std::make_shared<Graphics::Buffer>(GL_ARRAY_BUFFER);
    vbo->Bind();
    vbo->Data(data);

    this->_attributesTemplate.Apply(vao);

    vao->Unbind();
    ebo->Unbind();
    vbo->Unbind();

    std::shared_ptr<Graphics::TexturedMesh> texturedMesh = std::make_shared<Graphics::TexturedMesh>(
        vao, vbo, ebo, static_cast<uint32_t>(indices.size()));

    aiMaterial* material = this->_scene->mMaterials[mesh->mMaterialIndex];
    aiString assetPath;

    if (1 == material->GetTextureCount(aiTextureType_DIFFUSE))
    {
        material->GetTexture(aiTextureType_DIFFUSE, 0, &assetPath);
        texturedMesh->SetDiffuseMap(ResourcesLoader::Instance().LoadTexture(this->ParseAssetName(assetPath)));
    }

    if (1 == material->GetTextureCount(aiTextureType_NORMALS))
    {
        material->GetTexture(aiTextureType_NORMALS, 0, &assetPath);
        texturedMesh->SetNormalMap(ResourcesLoader::Instance().LoadTexture(this->ParseAssetName(assetPath)));
    }

    if (1 == material->GetTextureCount(aiTextureType_SPECULAR))
    {
        material->GetTexture(aiTextureType_SPECULAR, 0, &assetPath);
        texturedMesh->SetSpecularMap(ResourcesLoader::Instance().LoadTexture(this->ParseAssetName(assetPath)));
    }

    texturedMesh->SetMaterial(this->ParseMaterial(material));

    return texturedMesh;
}

std::string Util::AssimpLoader::ParseAssetName(const aiString& assetPath) const
{
    const std::string pathStr(assetPath.C_Str());
    const size_t extIndex = pathStr.find_last_of('.');
    return pathStr.substr(0, extIndex);
}

Math::Vector3f Util::AssimpLoader::ParseColor(const aiColor3D& assimpColor) const
{
    return Math::Vector3f(assimpColor.r, assimpColor.g, assimpColor.b);
}

Graphics::Material Util::AssimpLoader::ParseMaterial(const aiMaterial* assimpMaterial) const
{
    aiColor3D assimpColor;
    assimpMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, assimpColor);
    const Math::Vector3f color = this->ParseColor(assimpColor);

    float reflectivity;
    assimpMaterial->Get(AI_MATKEY_REFLECTIVITY, reflectivity);

    float specular;
    assimpMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, specular);

    float shininess;
    assimpMaterial->Get(AI_MATKEY_SHININESS, shininess);

    return Graphics::Material(color, reflectivity, specular, shininess);
}
