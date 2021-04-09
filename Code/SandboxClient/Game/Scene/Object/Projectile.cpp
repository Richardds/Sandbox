// ----------------------------------------------------------------------------------------
//  \file       Projectile.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Game/Scene/Object/Projectile.h"

Sandbox::Projectile::Projectile(const std::shared_ptr<Actor>& actor) :
    Projectile(actor->GetPosition(), actor->GetRotationY())
{
}

Sandbox::Projectile::Projectile(const Math::Vector3f& position, const float rotation) :
    _origin(position),
    _range(75.0f)
{
    this->SetPosition(position);
    this->SetRotationY(rotation);
}

float Sandbox::Projectile::DistanceToOrigin() const
{
    return this->DistanceTo(this->_origin);
}

bool Sandbox::Projectile::OutOfRange() const
{
    return this->DistanceToOrigin() > this->_range;
}
