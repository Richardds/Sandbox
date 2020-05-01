#include <Math/Utils.h>

#include "Boi.h"

GunnerBoi::Boi::Boi(Math::Vector3f position) :
	Actor(position),
	_state(State::IDLE),
	_target(),
	_attackSpeed(1.2f),
	_countdown(0.0f)
{
}

GunnerBoi::Boi::~Boi()
{
}

bool GunnerBoi::Boi::IsReadyToFire() const
{
	return this->_countdown == 0.0f;
}

std::shared_ptr<GunnerBoi::Projectile> GunnerBoi::Boi::Fire()
{
	this->_countdown = 1.0f / this->_attackSpeed;
	std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(this->_position, this->_rotY);
	projectile->setPositionY(0.5f);
	projectile->SetMovingSpeed(20.0f);
	return projectile;
}

void GunnerBoi::Boi::Update(float delta)
{
	// Update projectile countdown
	if (this->_countdown > 0.0f) {
		float next = this->_countdown - delta;
		this->_countdown = Math::max(next, 0.0f);
	}

	if (State::FOLLOWING == this->_state) {
		if (this->DistanceTo(this->_target) < 0.05f) {
			this->_state = State::IDLE;
		}
		else {
			this->LookAt(this->_target);
			Actor::Update(delta);
		}
	}
}
