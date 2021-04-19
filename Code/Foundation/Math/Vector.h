// ----------------------------------------------------------------------------------------
//  \file       Vector.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"

namespace Math
{
    /// float vector with two components
    using Vector2f = glm::vec<2, float, glm::defaultp>;
    /// float vector with three components
    using Vector3f = glm::vec<3, float, glm::defaultp>;
    /// float vector with four components
    using Vector4f = glm::vec<4, float, glm::defaultp>;

    /// integer vector with two components
    using Vector2i = glm::vec<2, int, glm::defaultp>;
    /// integer vector with three components
    using Vector3i = glm::vec<3, int, glm::defaultp>;
    /// integer vector with four components
    using Vector4i = glm::vec<4, int, glm::defaultp>;

    /// unsigned integer vector with two components
    using Vector2ui = glm::vec<2, unsigned int, glm::defaultp>;
    /// unsigned integer vector with three components
    using Vector3ui = glm::vec<3, unsigned int, glm::defaultp>;
    /// unsigned integer vector with four components
    using Vector4ui = glm::vec<4, unsigned int, glm::defaultp>;

    /// integer vector with two components (guaranteed to be 32-bit)
    using Vector2i32 = glm::vec<2, int32_t, glm::defaultp>;
    /// integer vector with three components (guaranteed to be 32-bit)
    using Vector3i32 = glm::vec<3, int32_t, glm::defaultp>;
    /// integer vector with four components (guaranteed to be 32-bit)
    using Vector4i32 = glm::vec<4, int32_t, glm::defaultp>;

    /// unsigned integer vector with two components (guaranteed to be 32-bit)
    using Vector2ui32 = glm::vec<2, uint32_t, glm::defaultp>;
    /// unsigned integer vector with three components (guaranteed to be 32-bit)
    using Vector3ui32 = glm::vec<3, uint32_t, glm::defaultp>;
    /// unsigned integer vector with four components (guaranteed to be 32-bit)
    using Vector4ui32 = glm::vec<4, uint32_t, glm::defaultp>;

    /// integer vector with two components (guaranteed to be 64-bit)
    using Vector2i64 = glm::vec<2, int64_t, glm::defaultp>;
    /// integer vector with three components (guaranteed to be 64-bit)
    using Vector3i64 =  glm::vec<3, int64_t, glm::defaultp>;
    /// integer vector with four components (guaranteed to be 64-bit)
    using Vector4i64 = glm::vec<4, int64_t, glm::defaultp>;

    /// unsigned integer vector with two components (guaranteed to be 64-bit)
    using Vector2ui64 = glm::vec<2, uint64_t, glm::defaultp>;
    /// unsigned integer vector with three components (guaranteed to be 64-bit)
    using Vector3ui64 = glm::vec<3, uint64_t, glm::defaultp>;
    /// unsigned integer vector with four components (guaranteed to be 64-bit)
    using Vector4ui64 = glm::vec<4, uint64_t, glm::defaultp>;
}
