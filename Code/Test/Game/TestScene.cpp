// ----------------------------------------------------------------------------------------
//  \file       TestScene.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <Precompiled.h>
#include <Util/ResourcesLoader.h>
#include <Util/Generators/TextMeshGenerator.h>
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

    // Setup text
    std::shared_ptr<Graphics::TextType> font = Util::ResourcesLoader::Instance().LoadFont("tahoma");
    this->_testText = Util::TextMeshGenerator::Instance().Generate("AAA", font, 32.0f);

    // Add crate entity
    std::shared_ptr<Graphics::Entity> entity = this->AddEntity("object", "crate");
    entity->SetPosition(Math::Vector3f(-5.0f, 0.0f, 0.0f));

    // Register mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](float x, float y)
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
        this->_camera->IncreaseRotation(-mouseMotion.y, mouseMotion.x, 0.0f);
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

    this->_camera->Spectate(this->_entities["object"]->GetPosition());
}

void Sandbox::TestScene::Render()
{
    Scene::Render();

    this->_glyphRenderer->Begin();
    this->_glyphRenderer->Render(this->_testText);
}
