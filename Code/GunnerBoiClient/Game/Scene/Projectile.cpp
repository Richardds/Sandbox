#include "Projectile.h"

GunnerBoi::Projectile::Projectile(std::shared_ptr<Actor> actor) :
    Projectile(actor->getPosition(), actor->getRotationY())
{
}

GunnerBoi::Projectile::Projectile(Math::Vector3f position, float rotation) :
    Actor(position, rotation),
    _origin(position),
    _range(15.0f)
{
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
