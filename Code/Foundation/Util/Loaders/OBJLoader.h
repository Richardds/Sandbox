#pragma once

#include <fstream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../Core/Singleton.h"
#include "../../Math/Vector.h"
#include "../../Graphics/Model.h"
#include "../../Graphics/VertexAttributeConfig.h"

namespace Util
{

    class OBJLoader
    {
    public:
        OBJLoader();
        virtual ~OBJLoader();
        std::shared_ptr<Graphics::Model> Load(const std::vector<char>& buffer);
        void ProcessNode(aiNode* node);
        std::shared_ptr<Graphics::Mesh> ProcessMesh(aiMesh* mesh);

    private:
        Graphics::VertexAttributeConfig _attributesTemplate;
        std::shared_ptr<Graphics::Model> _model;
        const aiScene* _scene;
        uint32_t _nodeCount;
        uint32_t _meshCount;
    };

}
