// ----------------------------------------------------------------------------------------
//  \file       AssimpLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Material.h"
#include "Graphics/Model.h"
#include "Graphics/VertexAttributeConfig.h"
#include "Math/Vector.h"

namespace Util
{
    /// Model loader which uses Assimp library
    class AssimpLoader
    {
    public:
        AssimpLoader();
        std::shared_ptr<Graphics::Model> Load(const std::vector<char>& buffer);

    private:
        void ProcessNode(aiNode* node);
        std::shared_ptr<Graphics::TexturedMesh> ProcessMesh(aiMesh* mesh);
        std::string ParseAssetName(const aiString& assetPath) const;
        Math::Vector3f ParseColor(const aiColor3D& assimpColor) const;
        Graphics::Material ParseMaterial(const aiMaterial* assimpMaterial) const;

        Graphics::VertexAttributeConfig _attributesTemplate;
        std::shared_ptr<Graphics::Model> _model;
        const aiScene* _scene;
        uint32_t _nodeCount;
        uint32_t _meshCount;
    };
}
