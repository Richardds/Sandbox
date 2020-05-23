// ----------------------------------------------------------------------------------------
//  \file       Actor.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Entity.h"

namespace Graphics
{
	/// 3D scene actor entity
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
