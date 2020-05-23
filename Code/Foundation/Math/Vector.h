// ----------------------------------------------------------------------------------------
//  \file       Vector.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Math
{
	/// float vector with two components
	typedef glm::vec<2, float, glm::defaultp> Vector2f;
	/// float vector with three components
	typedef glm::vec<3, float, glm::defaultp> Vector3f;
	/// float vector with four components
	typedef glm::vec<4, float, glm::defaultp> Vector4f;

	/// integer vector with two components
	typedef glm::vec<2, int, glm::defaultp> Vector2i;
	/// integer vector with three components
	typedef glm::vec<3, int, glm::defaultp> Vector3i;
	/// integer vector with four components
	typedef glm::vec<4, int, glm::defaultp> Vector4i;

	/// unsigned integer vector with two components
	typedef glm::vec<2, unsigned int, glm::defaultp> Vector2ui;
	/// unsigned integer vector with three components
	typedef glm::vec<3, unsigned int, glm::defaultp> Vector3ui;
	/// unsigned integer vector with four components
	typedef glm::vec<4, unsigned int, glm::defaultp> Vector4ui;

	/// integer vector with two components (guaranteed to be 32-bit)
	typedef glm::vec<2, int32_t, glm::defaultp> Vector2i32;
	/// integer vector with three components (guaranteed to be 32-bit)
	typedef glm::vec<3, int32_t, glm::defaultp> Vector3i32;
	/// integer vector with four components (guaranteed to be 32-bit)
	typedef glm::vec<4, int32_t, glm::defaultp> Vector4i32;

	/// unsigned integer vector with two components (guaranteed to be 32-bit)
	typedef glm::vec<2, uint32_t, glm::defaultp> Vector2ui32;
	/// unsigned integer vector with three components (guaranteed to be 32-bit)
	typedef glm::vec<3, uint32_t, glm::defaultp> Vector3ui32;
	/// unsigned integer vector with four components (guaranteed to be 32-bit)
	typedef glm::vec<4, uint32_t, glm::defaultp> Vector4ui32;

	/// integer vector with two components (guaranteed to be 64-bit)
	typedef glm::vec<2, int64_t, glm::defaultp> Vector2i64;
	/// integer vector with three components (guaranteed to be 64-bit)
	typedef glm::vec<3, int64_t, glm::defaultp> Vector3i64;
	/// integer vector with four components (guaranteed to be 64-bit)
	typedef glm::vec<4, int64_t, glm::defaultp> Vector4i64;

	/// unsigned integer vector with two components (guaranteed to be 64-bit)
	typedef glm::vec<2, uint64_t, glm::defaultp> Vector2ui64;
	/// unsigned integer vector with three components (guaranteed to be 64-bit)
	typedef glm::vec<3, uint64_t, glm::defaultp> Vector3ui64;
	/// unsigned integer vector with four components (guaranteed to be 64-bit)
	typedef glm::vec<4, uint64_t, glm::defaultp> Vector4ui64;
}
