// ----------------------------------------------------------------------------------------
//  \file       RigidBody.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Math/Vector.h"

namespace Math
{
    class EXPORT RigidBody
    {
    public:
        RigidBody(const Vector3f& position, float mass, const std::shared_ptr<btCollisionShape>& collisionShape = nullptr);
        virtual ~RigidBody();

        btRigidBody* GetRigidBody() const;
        std::shared_ptr<btCollisionShape> GetCollisionShape() const;
        void SetCollisionShape(const std::shared_ptr<btCollisionShape>& collisionShape);

    protected:
        std::shared_ptr<btCollisionShape> _collisionShape;
        btMotionState* _motionState;
        btRigidBody* _rigidBody;
    };

    inline btRigidBody* RigidBody::GetRigidBody() const
    {
        return this->_rigidBody;
    }

    inline std::shared_ptr<btCollisionShape> RigidBody::GetCollisionShape() const
    {
        return this->_collisionShape;
    }

    inline void RigidBody::SetCollisionShape(const std::shared_ptr<btCollisionShape>& collisionShape)
    {
        this->_rigidBody->setCollisionShape(collisionShape.get());
        this->_collisionShape = collisionShape;
    }
    
}
