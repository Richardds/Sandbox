// ----------------------------------------------------------------------------------------
//  \file       Plane.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Physics/RigidBody.h"

namespace Math
{
    class EXPORT Plane : public RigidBody
    {
    public:
        Plane();
        explicit Plane(const Vector3f& normal);
    };
    
}
