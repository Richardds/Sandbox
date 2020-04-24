#pragma once

#include <cstdint>

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Math/Quaternion.h"

struct VertexData {
    Math::Vector3f vertex;
    Math::Vector3f normal;
    Math::Vector2f texture;
    Math::Vector3f tangent;
};

template<typename T>
auto EnumToValue(T const value)
{
	return static_cast<typename std::underlying_type<T>::type>(value);
}
