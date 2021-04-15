// ----------------------------------------------------------------------------------------
//  \file       RigidBody.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Math/Physics/RigidBody.h"

Math::RigidBody::RigidBody(const Vector3f& position, const float mass, const std::shared_ptr<btCollisionShape>& collisionShape) :
    _collisionShape(collisionShape),
    _motionState(nullptr),
    _rigidBody(nullptr)
{
    // Transformation
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(position.x, position.y, position.z));
    //transform.setRotation( ... ); // TODO

    this->_motionState = new btDefaultMotionState(transform);

    btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(mass, this->_motionState, nullptr);

    // Calculate local inertia
    if (collisionShape)
    {
        rigidBodyInfo.m_collisionShape = collisionShape.get();

        if (mass > 0.0f)
        {
            btVector3 inertia(0.0f, 0.0f, 0.0f);
            collisionShape->calculateLocalInertia(mass, inertia);
            rigidBodyInfo.m_localInertia = inertia;
        }
    }
    
    this->_rigidBody = new btRigidBody(rigidBodyInfo);
}

Math::RigidBody::~RigidBody()
{
    delete this->_rigidBody;
    delete this->_motionState;
}
