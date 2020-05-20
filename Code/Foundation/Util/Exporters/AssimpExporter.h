#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "../../Graphics/Material.h"
#include "../../Math/Vector.h"

namespace Util
{
	class AssimpExporter
	{
	public:
		AssimpExporter();
		
		bool Load(const std::vector<char>& buffer);
		void Export(std::ofstream& outputFile) const;

	private:
		template<typename T> void Write(std::ofstream& file, T value) const;
		void WriteString(std::ofstream& outputFile, const std::string& string) const;
		void WriteNode(std::ofstream& file, aiNode* node) const;
		void WriteMaterial(std::ofstream& file, aiMaterial* material) const;
		void WriteMesh(std::ofstream& file, aiMesh* mesh) const;
		[[nodiscard]] std::string ParseAssetName(const aiString& assetPath) const;

		Assimp::Importer _importer;
		const aiScene* _scene;
	};

	template <typename T>
	void AssimpExporter::Write(std::ofstream& file, T value) const
	{
		file.write(reinterpret_cast<const char*>(&value), sizeof(T));
	}
}
