// ----------------------------------------------------------------------------------------
//  \file       Box.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Math/Physics/RigidBody/Box.h"

Math::Box::Box(const Vector3f& position, const Vector3f& size, const float mass) :
    RigidBody(position, mass, std::make_shared<btBoxShape>(btVector3(size.x, size.y, size.z)))
{
}
