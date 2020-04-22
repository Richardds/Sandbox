#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

namespace Math
{

    Matrix4f projectionMatrix(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);

    Matrix4f viewMatrix(Vector3f position, float rotX, float rotY);

    Matrix4f transformationMatrix(const Vector3f& position, float rotX, float rotY, float rotZ, float scale);

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
