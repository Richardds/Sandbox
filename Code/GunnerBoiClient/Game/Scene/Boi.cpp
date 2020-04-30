#include "Boi.h"

GunnerBoi::Boi::Boi() :
	_state(State::IDLE),
	_target(),
	_movingSpeed(3.0f)
{
}

GunnerBoi::Boi::Boi(Math::Vector3f position) :
	Player(position),
	_state(State::IDLE),
	_target(),
	_movingSpeed(1.0f)
{
}

GunnerBoi::Boi::~Boi()
{
}

std::shared_ptr<GunnerBoi::Projectile> GunnerBoi::Boi::Fire() const
{
	return std::make_shared<Projectile>(this->_position, this->_rotY);
}

float GunnerBoi::Boi::DistanceTo(Math::Vector2f target)
{
	return glm::distance(Math::Vector2f(this->_position.x, this->_position.z), target);
}

void GunnerBoi::Boi::Update(float delta)
{
	if (State::FOLLOWING == this->_state) {
		if (this->DistanceTo(this->_target) < 0.05f) {
			this->_state = State::IDLE;
		}
		else {
			this->LookAt(this->_target);
			this->Move(this->_movingSpeed * delta);
		}
	}
}
