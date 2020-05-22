#pragma once

#include "Entity.h"

namespace Graphics
{
	class Actor : public Entity
	{
	public:
		Actor();
		virtual ~Actor() = default;

		[[nodiscard]] float GetMovingSpeed() const;
		void SetMovingSpeed(float speed);
		void Move(float distance);
		virtual void GoForward(float delta);
		virtual void TurnLeft(float delta);
		virtual void TurnRight(float delta);
		void LookAt(Math::Vector2f target);
		[[nodiscard]] float DistanceTo(Math::Vector2f target) const;

	private:
		float _movingSpeed;
		float _turningSpeed;
	};

	inline float Actor::GetMovingSpeed() const
	{
		return this->_movingSpeed;
	}

	inline void Actor::SetMovingSpeed(const float speed)
	{
		this->_movingSpeed = speed;
	}
}
