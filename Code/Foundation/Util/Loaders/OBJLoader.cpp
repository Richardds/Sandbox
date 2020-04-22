#include "OBJLoader.h"
#include "../ResourcesLoader.h"

Util::OBJLoader::OBJLoader() :
    _scene(nullptr),
    _nodeCount(0),
    _meshCount(0)
{
    this->_attributesTemplate.Append(GL_FLOAT, 3, sizeof(float));
    this->_attributesTemplate.Append(GL_FLOAT, 3, sizeof(float));
    this->_attributesTemplate.Append(GL_FLOAT, 2, sizeof(float));
}

Util::OBJLoader::~OBJLoader()
{
}

std::shared_ptr<Graphics::Model> Util::OBJLoader::Load(const std::vector<char>& buffer)
{
    this->_model = std::make_shared<Graphics::Model>();

    Assimp::Importer importer;

    this->_scene = importer.ReadFileFromMemory(buffer.data(), buffer.size(),
          aiProcess_FlipUVs
        | aiProcess_Triangulate
        | aiProcess_FixInfacingNormals
        | aiProcess_FindInvalidData
    );

    if (!this->_scene || this->_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->_scene->mRootNode) {
        return _model;
    }

    this->ProcessNode(this->_scene->mRootNode);

    this->_model->FinishLoading();

    return _model;
}

void Util::OBJLoader::ProcessNode(aiNode* node)
{
    uint16_t nodeId = this->_nodeCount++;
    for (uint32_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = this->_scene->mMeshes[node->mMeshes[i]];
        uint16_t meshId = this->_meshCount++;

        //std::string meshName = "mesh" + std::to_string(nodeId) + "_" + std::to_string(meshId);
        _assert(meshId == 0); // TODO: Multiple mesh model
        std::string meshName = "default";

        std::shared_ptr<Graphics::Mesh> modelMesh = this->ProcessMesh(mesh);
        modelMesh->SetTexture(Util::ResourcesLoader::Instance().LoadTexture("default"));
        this->_model->AddMesh(meshName, modelMesh);
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++) {
        this->ProcessNode(node->mChildren[i]);
    }
}

std::shared_ptr<Graphics::Mesh> Util::OBJLoader::ProcessMesh(aiMesh* mesh)
{
    std::vector<Graphics::Mesh::VertexData> data;
    std::vector<uint32_t> elements;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
        Graphics::Mesh::VertexData vertexData;
        vertexData.vertex.x = mesh->mVertices[i].x;
        vertexData.vertex.y = mesh->mVertices[i].y;
        vertexData.vertex.z = mesh->mVertices[i].z;

        vertexData.normal.x = mesh->mNormals[i].x;
        vertexData.normal.y = mesh->mNormals[i].y;
        vertexData.normal.z = mesh->mNormals[i].z;

        vertexData.texture.x = mesh->mTextureCoords[0][i].x;
        vertexData.texture.y = mesh->mTextureCoords[0][i].y;

        data.push_back(vertexData);
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (uint32_t j = 0; j < face.mNumIndices; j++) {
            elements.push_back(face.mIndices[j]);
        }
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

    return std::make_shared<Graphics::Mesh>(vao, vbo, ebo, static_cast<uint32_t>(elements.size()));
}
