#pragma once

#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Math/Quaternion.h"
#include "../Math/Vector.h"

#define _Pack( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))

namespace Timing
{
	using Nanoseconds = std::chrono::duration<float, std::nano>;
	using Microseconds = std::chrono::duration<float, std::micro>;
	using Milliseconds = std::chrono::duration<float, std::milli>;
	using Seconds = std::chrono::duration<float>;
	using Minutes = std::chrono::duration<float, std::ratio<60>>;
	using Hours = std::chrono::duration<float, std::ratio<3600>>;
	using Days = std::chrono::duration<float, std::ratio<86400>>;
	using Weeks = std::chrono::duration<float, std::ratio<604800>>;
	using Months = std::chrono::duration<float, std::ratio<2629746>>;
	using Years = std::chrono::duration<float, std::ratio<31556952>>;

	using TimePoint = std::chrono::time_point<std::chrono::steady_clock, Microseconds>;
	using Duration = Microseconds;
}

namespace Util
{
	// Diffuse texture bitfield
	static const uint8_t HAS_TEXTURE_DIFFUSE  = 0b001;
	// Normals map bitfield
	static const uint8_t HAS_TEXTURE_NORMALS  = 0b010;
	// Specular map bitfield
	static const uint8_t HAS_TEXTURE_SPECULAR = 0b100;
}

struct VertexData2
{
	Math::Vector3f vertex;
	Math::Vector2f texture;
};

struct VertexData3
{
	Math::Vector3f vertex;
	Math::Vector3f normal;
	Math::Vector2f texture;
	Math::Vector3f tangent;
};

template <typename T>
auto EnumToValue(T const value)
{
	return static_cast<typename std::underlying_type<T>::type>(value);
}
