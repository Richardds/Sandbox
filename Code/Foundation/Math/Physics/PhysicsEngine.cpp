// ----------------------------------------------------------------------------------------
//  \file       PhysicsEngine.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Math/Physics/PhysicsEngine.h"

#include "RigidBody/Plane.h"

Math::PhysicsEngine::PhysicsEngine() :
    _state(State::Initial),
    _btWorld(nullptr),
    _btDispatcher(nullptr),
    _btCollisionConfiguration(nullptr),
    _btBroadphase(nullptr),
    _btSolver(nullptr)
{
}

Math::PhysicsEngine::~PhysicsEngine()
{
    if (State::Ready == this->_state)
    {
        this->Destroy();
    }
}

void Math::PhysicsEngine::Setup()
{
    this->_btCollisionConfiguration = new btDefaultCollisionConfiguration();
    this->_btDispatcher = new btCollisionDispatcher(this->_btCollisionConfiguration);
    this->_btBroadphase = new btDbvtBroadphase();
    this->_btSolver = new btSequentialImpulseConstraintSolver();
    this->_btWorld = new btDiscreteDynamicsWorld(this->_btDispatcher, this->_btBroadphase, this->_btSolver, this->_btCollisionConfiguration);
    this->_btWorld->setGravity(btVector3(0.0f, -10.0f, 0.0f));
}

void Math::PhysicsEngine::Register(const std::shared_ptr<RigidBody>& rigidBody)
{
    this->_btWorld->addRigidBody(rigidBody->GetRigidBody());
    this->_single.emplace_back(rigidBody);
}

void Math::PhysicsEngine::Register(const std::shared_ptr<RigidBody>& rigidBody, const std::shared_ptr<Graphics::Entity>& entity)
{
    this->_btWorld->addRigidBody(rigidBody->GetRigidBody());
    this->_pairs.emplace_back(std::make_pair(rigidBody, entity));
}

void Math::PhysicsEngine::Update(const float delta)
{
    this->_btWorld->stepSimulation(delta);

    for (const auto& [rigidBody, entity] : this->_pairs)
    {
        const btTransform& transform = rigidBody->GetRigidBody()->getWorldTransform();
        const btVector3 position = transform.getOrigin();
        const btQuaternion qRotation = transform.getRotation();
        const Vector3f rotation = eulerAngles(glm::quat(qRotation.x(), qRotation.y(), qRotation.z(), qRotation.w()));

        entity->SetPosition(Vector3f(position.x(), position.y(), position.z()));
        entity->SetRotationX(glm::degrees(-rotation.z));
        entity->SetRotationY(glm::degrees(-rotation.y));
        entity->SetRotationZ(glm::degrees(rotation.x));
    }
}

void Math::PhysicsEngine::Destroy()
{
    auto it = this->_pairs.begin();

    while (it != this->_pairs.end())
    {
        const auto& [rigidBody, entity] = (*it);

        this->_btWorld->removeRigidBody(rigidBody->GetRigidBody());
        it = this->_pairs.erase(it);
    }

    delete this->_btWorld;
    delete this->_btSolver;
    delete this->_btBroadphase;
    delete this->_btDispatcher;
    delete this->_btCollisionConfiguration;
}
