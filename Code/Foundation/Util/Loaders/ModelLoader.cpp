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

void Util::ModelLoader::Load(std::shared_ptr<Graphics::Model>& model, IO::InputFile& file) const
{
    FourCC magic;
    file.Read(magic);

    if (FourCC("MODL") != magic)
    {
        IO::Console::Instance().Error("File header mismatch\n");
        return;
    }

    uint16_t meshesCount;
    file.Read(meshesCount);

    for (uint16_t i = 0; i < meshesCount; i++)
    {
        std::string meshName;
        file.Read(meshName);
        IO::Console::Instance().Info("-> Mesh '%s'\n", meshName.c_str());
        model->AddMesh(meshName, this->ReadMesh(file));
    }
}

std::shared_ptr<Graphics::TexturedMesh> Util::ModelLoader::ReadMesh(IO::InputFile& file) const
{
    std::vector<Graphics::VertexData3> data;
    std::vector<Math::Vector3ui32> indices;

    uint32_t verticesCount;
    file.Read(verticesCount);

    data.reserve(verticesCount);

    for (uint32_t i = 0; i < verticesCount; i++)
    {
        Graphics::VertexData3 vertex{};
        file.Read(vertex);
        data.emplace_back(vertex);
    }

    uint32_t trianglesCount;
    file.Read(trianglesCount);

    indices.reserve(3 * static_cast<size_t>(trianglesCount));

    for (uint32_t i = 0; i < trianglesCount; i++)
    {
        Math::Vector3ui32 triangleIndexes;
        file.Read(triangleIndexes);
        indices.emplace_back(triangleIndexes);
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
        vao, vbo, ebo, static_cast<uint32_t>(3 * indices.size())
    );

    // Load model material
    std::shared_ptr<Graphics::Material> material = this->ReadMaterial(file);
    texturedMesh->SetMaterial(*material);

    // Load model textures
    uint8_t textureBitfield;
    file.Read(textureBitfield);

    std::string textureName;

    if (HAS_TEXTURE_DIFFUSE & textureBitfield)
    {
        file.Read(textureName);
        std::shared_ptr<Graphics::Texture> texture = ResourcesLoader::Instance().LoadTexture(textureName);
        texture->Bind();
        texture->SetLODBias(-1.0f);
        texture->SetAnisotropicFiltering(16.0f);
        texture->Unbind();
        texturedMesh->SetDiffuseMap(texture);
    }

    if (HAS_TEXTURE_NORMALS & textureBitfield)
    {
        file.Read(textureName);
        std::shared_ptr<Graphics::Texture> texture = ResourcesLoader::Instance().LoadTexture(textureName);
        texture->Bind();
        texture->SetLODBias(-1.0f);
        texture->SetAnisotropicFiltering(16.0f);
        texture->Unbind();
        texturedMesh->SetNormalMap(texture);
    }

    if (HAS_TEXTURE_SPECULAR & textureBitfield)
    {
        file.Read(textureName);
        std::shared_ptr<Graphics::Texture> texture = ResourcesLoader::Instance().LoadTexture(textureName);
        texture->Bind();
        texture->SetLODBias(-1.0f);
        texture->SetAnisotropicFiltering(16.0f);
        texture->Unbind();
        texturedMesh->SetSpecularMap(texture);
    }

    return texturedMesh;
}

std::shared_ptr<Graphics::Material> Util::ModelLoader::ReadMaterial(IO::InputFile& file) const
{
    Math::Vector3f color;
    file.Read(color);

    float reflectivity;
    file.Read(reflectivity);

    float specular;
    file.Read(specular);

    float shininess;
    file.Read(shininess);

    return std::make_shared<Graphics::Material>(color, reflectivity, specular, shininess);
}
