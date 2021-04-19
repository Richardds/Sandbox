// ----------------------------------------------------------------------------------------
//  \file       Plane.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Math/Physics/RigidBody.h"

namespace Math
{
    class EXPORT Plane : public RigidBody
    {
    public:
        Plane();
        explicit Plane(const Vector3f& position);
        explicit Plane(const Vector3f& position, const Vector3f& normal);
    };
    
}
