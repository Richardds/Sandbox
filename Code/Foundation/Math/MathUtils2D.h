// ----------------------------------------------------------------------------------------
//  \file       MathUtils3D.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"

namespace Math
{
    // TODO
    //Matrix3f ProjectionMatrix2D(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);

    // TODO
    //Matrix3f ViewMatrix2D(const Vector2f& position, float rotation);

    EXPORT Matrix3f TransformationMatrix2D(const Vector2f& position, float rotation, float scale);

    EXPORT Matrix3f TranslationMatrix2D(const Vector2f& position);

    EXPORT Matrix3f RotationMatrix2D(float rotation);

    EXPORT Matrix3f ScaleMatrix2D(float scale);
}
