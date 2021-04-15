// ----------------------------------------------------------------------------------------
//  \file       Plane.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Math/Physics/RigidBody/Plane.h"

Math::Plane::Plane() :
    Plane(Vector3f(0.0f, 1.0f, 0.0f))
{
}

Math::Plane::Plane(const Vector3f& normal) :
    RigidBody(
        Vector3f(0.0f, 0.0f, 0.0f),
        0.0f,
        std::make_shared<btStaticPlaneShape>(btVector3(normal.x, normal.y, normal.z), 0.0f)
    )
{
}
