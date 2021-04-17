// ----------------------------------------------------------------------------------------
//  \file       TestScene.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <IO/Mouse.h>

#include "TestScene.h"

bool Sandbox::TestScene::Setup()
{
    if (!Scene::Setup())
    {
        return false;
    }

    // Configure camera
    this->_camera->SetDistance(5.0f);
    this->_camera->SetRotationX(20.0f);

    // Add test text
    this->AddText("test", "It works!");

    // Add crate entity
    std::shared_ptr<Graphics::Entity> entity = this->AddEntity("object", "crate");
    entity->SetPosition(Math::Vector3f(-5.0f, 0.0f, 0.0f));

    // Register mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](const float x, const float y)
    {
        this->_camera->IncreaseDistance(y);
    });

    return true;
}

void Sandbox::TestScene::ProcessCameraInput() const
{
    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Right))
    {
        // Increase viewing rotation relative to the player
        const Math::Vector2f mouseMotion = 75.0f * IO::Mouse::Instance().GetRelativeGlMotion();
        this->_camera->IncreaseRotation(Math::Vector3f(-mouseMotion.y, mouseMotion.x, 0.0f));
    }
}

void Sandbox::TestScene::ProcessInput()
{
    Scene::ProcessInput();

    this->ProcessCameraInput();
}

void Sandbox::TestScene::Update(const float delta)
{
    Scene::Update(delta);

    this->_camera->Spectate(this->_entitiesMapping["object"]->GetPosition());
}

void Sandbox::TestScene::Render()
{
    Scene::Render();
}
