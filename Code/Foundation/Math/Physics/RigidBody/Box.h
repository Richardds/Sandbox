// ----------------------------------------------------------------------------------------
//  \file       Box.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Math/Physics/RigidBody.h"

namespace Math
{
    class EXPORT Box : public RigidBody
    {
    public:
        Box(const Vector3f& position, const Vector3f& size, float mass = 1.0f);
    };
    
}
