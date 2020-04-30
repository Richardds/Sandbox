#include "Projectile.h"

GunnerBoi::Projectile::Projectile(Math::Vector3f position, float rotation) :
	Entity(position, 0.0f, rotation, 0.0f)
{
}

GunnerBoi::Projectile::~Projectile()
{
}
