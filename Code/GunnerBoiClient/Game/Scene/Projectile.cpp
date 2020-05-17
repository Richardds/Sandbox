#include "Projectile.h"

GunnerBoi::Projectile::Projectile(const std::shared_ptr<Actor>& actor) :
	Projectile(actor->GetPosition(), actor->GetRotationY())
{
}

GunnerBoi::Projectile::Projectile(const Math::Vector3f& position, const float rotation) :
	_origin(position),
	_range(25.0f)
{
	this->SetPosition(position);
	this->SetRotationY(rotation);
}

GunnerBoi::Projectile::~Projectile()
{
}

float GunnerBoi::Projectile::DistanceToOrigin() const
{
	return this->DistanceTo(this->_origin);
}

bool GunnerBoi::Projectile::OutOfRange() const
{
	return this->DistanceToOrigin() > this->_range;
}
