#pragma once

#include "Precompiled.h"
#include "Game/Scene/Light.h"

namespace Graphics
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight();

		[[nodiscard]] Math::Vector3f GetDirection() const;
		void SetDirection(const Math::Vector3f& direction);

	private:
		Math::Vector3f _direction;
	};

	inline Math::Vector3f DirectionalLight::GetDirection() const
	{
		return this->_direction;
	}

	inline void DirectionalLight::SetDirection(const Math::Vector3f& direction)
	{
		this->_direction = direction;
	}
}
