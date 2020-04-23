#pragma once

#include <cstdint>

template<typename T>
auto EnumToValue(T const value)
{
	return static_cast<typename std::underlying_type<T>::type>(value);
}
