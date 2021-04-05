// ----------------------------------------------------------------------------------------
//  \file       MathUtils.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Math/MathUtils.h"

float Math::LookAt(const Vector2f& position, const Vector2f& target)
{
    const Vector2f diff = target - position;
    return glm::degrees(glm::atan(-diff.y, diff.x)) + 90.0f;
}
