#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

namespace Math
{
	Matrix4f ProjectionMatrix(float aspectRatio, float fieldOfView, float nearPlane, float farPlane);

	Matrix4f ViewMatrix(const Vector3f& position, float rotationX, float rotationY);

	Matrix4f TransformationMatrix(const Vector3f& position, float rotationX, float rotationY, float rotationZ,
	                              float scale);

	Matrix4f TranslationMatrix(const Vector3f& position);

	Matrix4f RotationMatrix(float rotationX, float rotationY, float rotationZ);

	Matrix4f ScaleMatrix(float scale);

	float LookAt(const Vector2f& position, const Vector2f& target);

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
