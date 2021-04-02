// ----------------------------------------------------------------------------------------
//  \file       TestScene.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"

#include <IO/Keyboard.h>
#include <IO/Mouse.h>

#include "TestScene.h"
#include "Util/ResourcesLoader.h"


bool Sandbox::TestScene::Setup()
{
    _Assert(Graphics::Scene::Setup());

    // Configure camera
    this->_camera->SetDistance(12.5f);
    this->_camera->SetRotationX(20.0f);

    // Load Skybox
    std::shared_ptr<Graphics::Texture> skyboxTexture = Util::ResourcesLoader::Instance().LoadCubeMap("day");
    this->_skybox = std::make_shared<Graphics::Skybox>(skyboxTexture, 750.0f);

    // Add crate entities
    std::shared_ptr<Graphics::Entity> entity = this->AddEntity("crate", "crate");
    entity->SetPosition(Math::Vector3f(-5.0f, 0.0f, 0.0f));

    return true;
}

void Sandbox::TestScene::ProcessCameraInput()
{
    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Right))
    {
        // Mouse relative motion to previous state
        Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();

        if (IO::Keyboard::Instance().IsAltPressed())
        {
            // Increase viewing position relative to the world
            mouseMotion *= -25.0f; // Invert and make motion more sensitive
            const float rotationRadians = glm::radians(this->_camera->GetRotationY());
            this->_camera->IncreasePosition(Math::Vector3f(
                mouseMotion.x * glm::cos(rotationRadians),
                mouseMotion.y,
                mouseMotion.x * glm::sin(rotationRadians)
            ));
        }
        else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Space))
        {
            // Increase viewing position relative to the world
            mouseMotion *= -25.0f; // Invert and make motion more sensitive
            const float rotationRadians = glm::radians(this->_camera->GetRotationY());
            this->_camera->IncreasePosition(Math::Vector3f(
                mouseMotion.x * glm::cos(rotationRadians) + mouseMotion.y * glm::sin(rotationRadians),
                0.0f,
                mouseMotion.x * glm::sin(rotationRadians) - mouseMotion.y * glm::cos(rotationRadians)
            ));
        }
        else
        {
            // Increase viewing rotation relative to the world
            mouseMotion *= -75.0f; // Invert and make motion more sensitive
            this->_camera->IncreaseRotation(-mouseMotion.y, mouseMotion.x, 0.0f);
        }
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
}

void Sandbox::TestScene::Render()
{
    Scene::Render();

    this->_glyphRenderer->Begin();

    this->_glyphRenderer->Render('X', 100, 100);
}

void Sandbox::TestScene::RenderEntities()
{
    Scene::RenderEntities();
}
