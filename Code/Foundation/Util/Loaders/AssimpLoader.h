#pragma once

#include <string>
#include <assimp/scene.h>

#include "../../Graphics/Material.h"
#include "../../Graphics/Model.h"
#include "../../Graphics/VertexAttributeConfig.h"
#include "../../Math/Vector.h"

namespace Util
{
	class AssimpLoader
	{
	public:
		AssimpLoader();
		std::shared_ptr<Graphics::Model> Load(const std::vector<char>& buffer);

	private:
		void ProcessNode(aiNode* node);
		[[nodiscard]] std::shared_ptr<Graphics::TexturedMesh> ProcessMesh(aiMesh* mesh);
		[[nodiscard]] std::string ParseAssetName(const aiString& assetPath) const;
		[[nodiscard]] Math::Vector3f ParseColor(const aiColor3D& assimpColor) const;
		[[nodiscard]] Graphics::Material ParseMaterial(const aiMaterial* assimpMaterial) const;

		Graphics::VertexAttributeConfig _attributesTemplate;
		std::shared_ptr<Graphics::Model> _model;
		const aiScene* _scene;
		uint32_t _nodeCount;
		uint32_t _meshCount;
	};
}
