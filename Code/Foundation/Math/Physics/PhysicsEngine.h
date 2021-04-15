// ----------------------------------------------------------------------------------------
//  \file       PhysicsEngine.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "RigidBody.h"
#include "Game/Scene/Object/Entity.h"

namespace Math
{
    class EXPORT PhysicsEngine
    {
    public:
        enum class State
        {
            Initial,
            Ready
        };

        PhysicsEngine();
        virtual ~PhysicsEngine();

        void Setup();
        void Register(const std::shared_ptr<RigidBody>& rigidBody);
        void Register(const std::shared_ptr<RigidBody>& rigidBody, const std::shared_ptr<Graphics::Entity>& entity);
        void Update(float delta);
        void Destroy();

    private:
        State _state;
        btDynamicsWorld* _btWorld;
        btDispatcher* _btDispatcher;
        btCollisionConfiguration* _btCollisionConfiguration;
        btBroadphaseInterface* _btBroadphase;
        btConstraintSolver* _btSolver;
        std::list<std::shared_ptr<RigidBody>> _single;
        std::list<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<Graphics::Entity>>> _pairs;
    };
    
}
