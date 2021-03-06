// ----------------------------------------------------------------------------------------
//  \file       Duck.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Game/Scene/Object/Duck.h"
#include "Math/MathUtils.h"

Sandbox::Duck::Duck(const Math::Vector3f& origin, const float rotation) :
    _origin(origin),
    _range(30.0f)
{
    this->SetPosition(origin);
    this->SetRotationY(rotation);
}

float Sandbox::Duck::DistanceToOrigin() const
{
    return this->DistanceTo(Math::Vector2f(this->_origin.x, this->_origin.z));
}

bool Sandbox::Duck::IsOutOfRange() const
{
    return this->DistanceToOrigin() > this->_range;
}
