#pragma once

#include <Game/Scene/Actor.h>
#include <Graphics/Model.h>
#include <Math/Vector.h>

#include "../Managers/ProjectileManager.h"

namespace GunnerBoi
{
	class Boi : public Graphics::Actor
	{
	public:
		enum class State
		{
			Idle,
			Running,
			Following
		};

		static constexpr float DEFAULT_ATTACK_SPEED = 3.0f;

		Boi();

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

	inline Boi::State Boi::GetState() const
	{
		return this->_state;
	}

	inline Math::Vector2f Boi::GetTarget() const
	{
		return this->_target;
	}

	inline void Boi::SetTarget(const Math::Vector2f& target)
	{
		this->_target = target;
	}

	inline void Boi::Follow()
	{
		this->_state = State::Following;
	}

	inline void Boi::Idle()
	{
		this->_state = State::Idle;
	}
}
