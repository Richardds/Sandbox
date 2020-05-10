#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

namespace Math
{

    Matrix4f ProjectionMatrix(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);

    Matrix4f ViewMatrix(const Vector3f& position, float rotX, float rotY);

    Matrix4f TransformationMatrix(const Vector3f& position, float rotX, float rotY, float rotZ, float scale);

    Matrix4f TranslationMatrix(const Vector3f& position);

    Matrix4f RotationMatrix(float rotX, float rotY, float rotZ);

    Matrix4f ScaleMatrix(float scale);

    float LookAt(const Vector2f& position, const Vector2f& target);

    template<typename T>
    T min(T value1, T value2)
    {
        return (value1 < value2) ? value1 : value2;
    }

    template<typename T>
    T max(T value1, T value2)
    {
        return (value2 < value1) ? value1 : value2;
    }

    template<typename T>
    T Restrict(T value, T lowerLimit, T upperLimit)
    {
        return min(max(value, lowerLimit), upperLimit);
    }

}
