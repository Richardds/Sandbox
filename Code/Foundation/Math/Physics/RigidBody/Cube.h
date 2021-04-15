// ----------------------------------------------------------------------------------------
//  \file       Cube.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Physics/RigidBody.h"

namespace Math
{
    class EXPORT Cube : public RigidBody
    {
    public:
        Cube(const Vector3f& position, const Vector3f& size, float mass = 1.0f);
    };
    
}
