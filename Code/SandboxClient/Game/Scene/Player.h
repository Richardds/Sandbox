#pragma once

#include <Precompiled.h>
#include <Game/Scene/Actor.h>
#include <Math/Vector.h>

#include "Game/Managers/ProjectileManager.h"

namespace Sandbox
{
	class Player : public Graphics::Actor
	{
	public:
		enum class State
		{
			Idle,
			Running,
			Following
		};

		static constexpr float DEFAULT_ATTACK_SPEED = 3.0f;

		Player();

		[[nodiscard]] State GetState() const;
		[[nodiscard]] Math::Vector2f GetTarget() const;
		void SetTarget(const Math::Vector2f& target);
		void Follow();
		void Idle();
		[[nodiscard]] bool IsReadyToFire() const;
		void SingleFire(std::shared_ptr<ProjectileManager>& projectileManager);
		void StarFire(std::shared_ptr<ProjectileManager>& projectileManager, unsigned int count);
		void BeamFire(std::shared_ptr<ProjectileManager>& projectileManager, unsigned int count);
		void Update(float delta);

	private:
		State _state;
		Math::Vector2f _target;
		float _attackSpeed;
		float _countdown;
	};

	inline Player::State Player::GetState() const
	{
		return this->_state;
	}

	inline Math::Vector2f Player::GetTarget() const
	{
		return this->_target;
	}

	inline void Player::SetTarget(const Math::Vector2f& target)
	{
		this->_target = target;
	}

	inline void Player::Follow()
	{
		this->_state = State::Following;
	}

	inline void Player::Idle()
	{
		this->_state = State::Idle;
	}
}
