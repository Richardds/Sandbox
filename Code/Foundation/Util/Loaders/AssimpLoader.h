#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../Math/Vector.h"
#include "../../Graphics/Model.h"
#include "../../Graphics/VertexAttributeConfig.h"
#include "../../Graphics/Material.h"

namespace Util
{

    class AssimpLoader
    {
    public:
        AssimpLoader();
        virtual ~AssimpLoader();
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
