// ----------------------------------------------------------------------------------------
//  \file       MathUtils.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Math/MathUtils.h"
#include "Math/Constants.h"

float Math::LookAt(const Vector2f& position, const Vector2f& target)
{
    // https://math.stackexchange.com/a/1596518
    const Vector2f diff = target - position;
    const float theta = glm::atan(diff.x, diff.y);
    return glm::degrees(theta < 0.0f ? theta + TwoPi : theta);
}

float Math::LookAtDiff(const Vector2f& position, const float rotation, const Vector2f& target)
{
    const float diff = LookAt(position, target) - rotation;

    if (diff >= 0.0f && diff < 180.0f)
    {
        return -diff;
    }

    return 360.0f - diff;
}

float Math::DistanceTo(const Vector2f& position, const Vector2f& target)
{
    return distance(position, target);
}
