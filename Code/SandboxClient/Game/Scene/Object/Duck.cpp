// ----------------------------------------------------------------------------------------
//  \file       Duck.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Game/Scene/Object/Duck.h"
#include "Math/MathUtils.h"

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
    return this->DistanceTo(Math::Vector2f(this->_origin.x, this->_origin.z));
}

bool Sandbox::Duck::IsOutOfRange() const
{
    return this->DistanceToOrigin() > this->_range;
}

bool Sandbox::Duck::IsHeadingBack() const
{
    const float headingRelativeToOrigin = Math::LookAtDiff(
        Math::Vector2f(this->_position.x, this->_position.z),
        this->_rotationY,
        Math::Vector2f(this->_origin.x, this->_origin.z)
    );

    if (glm::abs(headingRelativeToOrigin) < 45.0f) // TODO: Tweak the angle
    {
        return true;
    }

    return false;
}
