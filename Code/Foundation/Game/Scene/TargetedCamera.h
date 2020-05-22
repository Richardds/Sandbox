#pragma once

#include "Precompiled.h"
#include "Game/Scene/Camera.h"

namespace Graphics
{
	class TargetedCamera : public Camera
	{
	public:
		explicit TargetedCamera(float distance);

		[[nodiscard]] float GetDistance() const;
		void SetDistance(float distance);
		void IncreaseDistance(float distance);
		void Spectate(const Math::Vector3f& target);

	private:
		float _distance;
	};

	inline float TargetedCamera::GetDistance() const
	{
		return this->_distance;
	}

	inline void TargetedCamera::SetDistance(const float distance)
	{
		this->_distance = distance;
	}

	inline void TargetedCamera::IncreaseDistance(const float distance)
	{
		this->_distance += distance;
	}
}
