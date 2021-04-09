// ----------------------------------------------------------------------------------------
//  \file       MathUtils.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"

namespace Math
{
    EXPORT Matrix4f ProjectionMatrix3D(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);

    EXPORT Matrix4f ViewMatrix3D(const Vector3f& position, float rotationX, float rotationY);

    EXPORT Matrix4f TransformationMatrix3D(const Vector3f& position, float rotationX, float rotationY, float rotationZ, float scale);

    EXPORT Matrix4f TranslationMatrix3D(const Vector3f& position);

    EXPORT Matrix4f RotationMatrix3D(float rotationX, float rotationY, float rotationZ);

    EXPORT Matrix4f ScaleMatrix3D(float scale);
}
