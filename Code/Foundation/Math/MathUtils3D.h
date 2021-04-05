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
    Matrix4f ProjectionMatrix3D(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);

    Matrix4f ViewMatrix3D(const Vector3f& position, float rotationX, float rotationY);

    Matrix4f TransformationMatrix3D(const Vector3f& position, float rotationX, float rotationY, float rotationZ, float scale);

    Matrix4f TranslationMatrix3D(const Vector3f& position);

    Matrix4f RotationMatrix3D(float rotationX, float rotationY, float rotationZ);

    Matrix4f ScaleMatrix3D(float scale);
}
