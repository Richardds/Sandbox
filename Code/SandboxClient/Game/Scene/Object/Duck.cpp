// ----------------------------------------------------------------------------------------
//  \file       Duck.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Game/Scene/Object/Duck.h"

Sandbox::Duck::Duck(const std::shared_ptr<Actor>& actor) :
    Duck(actor->GetPosition(), actor->GetRotationY())
{
}

Sandbox::Duck::Duck(const Math::Vector3f& origin, const float rotation) :
    _origin(origin),
    _range(30.0f)
{
    this->SetPosition(origin);
    this->SetRotationY(rotation);
}

float Sandbox::Duck::DistanceToOrigin() const
{
    return this->DistanceTo(this->_origin);
}

bool Sandbox::Duck::OutOfRange() const
{
    return this->DistanceToOrigin() > this->_range;
}
