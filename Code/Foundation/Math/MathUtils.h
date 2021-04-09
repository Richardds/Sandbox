// ----------------------------------------------------------------------------------------
//  \file       MathUtils3D.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/MathUtils2D.h"
#include "Math/MathUtils3D.h"
#include "Math/Vector.h"

namespace Math
{
    EXPORT float LookAt(const Vector2f& position, const Vector2f& target);

    template <typename T>
    T Min(T value1, T value2)
    {
        return (value1 < value2) ? value1 : value2;
    }

    template <typename T>
    T Max(T value1, T value2)
    {
        return (value2 < value1) ? value1 : value2;
    }

    template <typename T>
    T Restrict(T value, T lowerLimit, T upperLimit)
    {
        return Min(Max(value, lowerLimit), upperLimit);
    }
}
