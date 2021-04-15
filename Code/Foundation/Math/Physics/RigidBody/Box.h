// ----------------------------------------------------------------------------------------
//  \file       Box.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Physics/RigidBody.h"

namespace Math
{
    class EXPORT Box : public RigidBody
    {
    public:
        Box(const Vector3f& position, const Vector3f& size, float mass = 1.0f);
    };
    
}
