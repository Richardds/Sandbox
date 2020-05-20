#pragma once

#include <string>
#include <fstream>

#include "../../Graphics/Material.h"
#include "../../Graphics/Model.h"
#include "../../Graphics/VertexAttributeConfig.h"

namespace Util
{
	class ModelLoader
	{
	public:
		ModelLoader();
		std::shared_ptr<Graphics::Model> Load(std::ifstream& file);

	private:
		template<typename T> void Read(std::ifstream& file, T* value) const;
		std::string ReadString(std::ifstream& file) const;
		void ParseFile(std::ifstream& file) const;
		std::shared_ptr<Graphics::Material> ParseMaterial(std::ifstream& file) const;
		std::shared_ptr<Graphics::TexturedMesh> ParseMesh(std::ifstream& file) const;

		Graphics::VertexAttributeConfig _attributesTemplate;
		std::shared_ptr<Graphics::Model> _model;
	};

	template <typename T>
	void ModelLoader::Read(std::ifstream& file, T* value) const
	{
		file.read(reinterpret_cast<char*>(value), sizeof(T));
	}
}
