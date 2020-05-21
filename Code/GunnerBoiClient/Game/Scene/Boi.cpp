#include <Math/Utils.h>

#include "Boi.h"

GunnerBoi::Boi::Boi() :
	_state(State::Idle),
	_target(0.0f),
	_attackSpeed(DEFAULT_ATTACK_SPEED),
	_countdown(0.0f)
{
}

bool GunnerBoi::Boi::IsReadyToFire() const
{
	return this->_countdown == 0.0f;
}

void GunnerBoi::Boi::SingleFire(std::shared_ptr<ProjectileManager>& projectileManager)
{
	this->_countdown = 1.0f / this->_attackSpeed;
	std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(this->_position, this->_rotationY);
	projectile->SetPositionY(0.5f);
	projectile->SetMovingSpeed(20.0f);
	projectileManager->Manage(projectile);
}

void GunnerBoi::Boi::StarFire(std::shared_ptr<ProjectileManager>& projectileManager, const unsigned int count)
{
	this->_countdown = 3.0f / this->_attackSpeed;

	const float step = 360.0f / static_cast<float>(count);

	for (unsigned int i = 0; i < count; ++i)
	{
		const float angle = static_cast<float>(i) * step;
		std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(this->_position, this->_rotationY + angle);
		projectile->SetPositionY(0.5f);
		projectile->SetMovingSpeed(15);
		projectileManager->Manage(projectile);
	}
}

void GunnerBoi::Boi::BeamFire(std::shared_ptr<ProjectileManager>& projectileManager, const unsigned int count)
{
	this->_countdown = 5.0f / this->_attackSpeed;

	const float step = 1.5f;
	
	for (unsigned int i = 0; i < count; ++i)
	{
		const float offset = static_cast<float>(i) * step;
		const Math::Vector3f position = Math::Vector3f(
			this->_position.x + glm::sin(glm::radians(this->_rotationY)) * offset,
			this->_position.y, 
			this->_position.z + glm::cos(glm::radians(this->_rotationY)) * offset
		);
		std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(position, this->_rotationY);
		projectile->SetPositionY(0.5f);
		projectile->SetMovingSpeed(30.0f);
		projectileManager->Manage(projectile);
	}
}

void GunnerBoi::Boi::Update(const float delta)
{
	// Update projectile countdown
	if (this->_countdown > 0.0f)
	{
		const float next = this->_countdown - delta;
		this->_countdown = Math::Max(next, 0.0f);
	}

	if (State::Following == this->_state)
	{
		if (this->DistanceTo(this->_target) < 0.1f)
		{
			this->_state = State::Idle;
		}
		else
		{
			this->LookAt(this->_target);
			Actor::Update(delta);
		}
	}
}
