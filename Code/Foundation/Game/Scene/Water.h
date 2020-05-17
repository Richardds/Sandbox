#pragma once

#include <memory>

#include "../../Graphics/TexturedMesh.h"
#include "../../Graphics/Shaders/WaterShader.h"
#include "../Attributes/HasPosition.h"

namespace Graphics
{
	class Water : public HasPosition
	{
	public:
		Water();

		[[nodiscard]] std::shared_ptr<TexturedMesh> GetMesh() const;
		void SetMesh(const std::shared_ptr<TexturedMesh>& mesh);
		[[nodiscard]] float GetDistortionSpeed() const;
		void SetDistortionSpeed(float speed);
		[[nodiscard]] float GetTiling() const;
		void SetTiling(float tiling);
		void Update(float delta);
		void Render(const std::shared_ptr<WaterShader>& shader) const;

	private:
		static constexpr float DEFAULT_DISTORTION_SPEED = 0.025f;
		static constexpr float DEFAULT_TILING = 1.0f;

		std::shared_ptr<TexturedMesh> _mesh;
		float _distortionOffset;
		float _distortionSpeed;
		float _tiling;
	};

	inline std::shared_ptr<TexturedMesh> Water::GetMesh() const
	{
		return this->_mesh;
	}

	inline void Water::SetMesh(const std::shared_ptr<TexturedMesh>& mesh)
	{
		this->_mesh = mesh;
	}

	inline float Water::GetDistortionSpeed() const
	{
		return this->_distortionSpeed;
	}

	inline void Water::SetDistortionSpeed(const float speed)
	{
		this->_distortionSpeed = speed;
	}

	inline float Water::GetTiling() const
	{
		return this->_tiling;
	}

	inline void Water::SetTiling(const float tiling)
	{
		this->_tiling = tiling;
	}
}
