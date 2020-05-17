#pragma once

#include <unordered_map>
#include <string>

#include "TexturedMesh.h"
#include "Shaders/EntityShader.h"

namespace Graphics
{
	class Model
	{
	public:
		enum class State
		{
			Initial,
			Loaded
		};

		Model();
		void Render(const std::shared_ptr<EntityShader>& shader);
		[[nodiscard]] State GetState() const;
		void AddMesh(const std::string& name, const std::shared_ptr<TexturedMesh>& mesh);
		[[nodiscard]] std::shared_ptr<TexturedMesh> GetMesh(const std::string& name) const;
		[[nodiscard]] std::unordered_map<std::string, std::shared_ptr<TexturedMesh>> GetMeshes() const;
		void FinishLoading();

	private:
		State _state;
		std::unordered_map<std::string, std::shared_ptr<TexturedMesh>> _meshes;
	};

	inline Model::State Model::GetState() const
	{
		return this->_state;
	}
}
