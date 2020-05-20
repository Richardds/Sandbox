#pragma once

#include "../../Graphics/Mesh.h"
#include "../../Graphics/Texture.h"

namespace Graphics
{
	class Skybox
	{
	public:
		explicit Skybox(const std::shared_ptr<Texture>& texture);
		Skybox(const std::shared_ptr<Texture>& texture, float size);

		[[nodiscard]] std::shared_ptr<Mesh> GetMesh() const;
		void SetMesh(const std::shared_ptr<Mesh>& mesh);
		[[nodiscard]] std::shared_ptr<Texture> GetTexture() const;
		void SetTexture(const std::shared_ptr<Texture>& texture);
		[[nodiscard]] float GetSize() const;
		void Render() const;

	private:
		static constexpr float DEFAULT_SKYBOX_SIZE = 500.0f;

		std::shared_ptr<Mesh> _mesh;
		std::shared_ptr<Texture> _texture;
		float _size;
	};

	inline std::shared_ptr<Mesh> Skybox::GetMesh() const
	{
		return this->_mesh;
	}

	inline void Skybox::SetMesh(const std::shared_ptr<Mesh>& mesh)
	{
		this->_mesh = mesh;
	}

	inline std::shared_ptr<Texture> Skybox::GetTexture() const
	{
		return this->_texture;
	}

	inline void Skybox::SetTexture(const std::shared_ptr<Texture>& texture)
	{
		this->_texture = texture;
	}
	
	inline float Skybox::GetSize() const
	{
		return this->_size;
	}
}
