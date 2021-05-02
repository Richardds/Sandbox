// ----------------------------------------------------------------------------------------
//  \file       SandboxScene.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <IO/Keyboard.h>
#include <IO/Mouse.h>
#include <Util/Random.h>
#include <Util/ResourcesLoader.h>
#include <Math/Physics/RigidBody/Box.h>

#include "SandboxScene.h"
#include "Scene/Object/Hardcoded.h"
#include "Util/String.h"

Sandbox::SandboxScene::SandboxScene() :
    _lockCameraToPlayer(true)
{
}

bool Sandbox::SandboxScene::Setup()
{
    if (!Scene::Setup())
    {
        return false;
    }

    // Setup managers
    this->_projectileManager = std::make_shared<ProjectileManager>(Util::ResourcesLoader::Instance().LoadModel("projectile"));
    this->_duckManager = std::make_shared<DuckManager>();

    // Configure camera
    this->_camera->SetDistance(12.0f);
    this->_camera->SetRotationX(20.0f);

    // Add title
    std::shared_ptr<Graphics::Text> textTitle = this->AddText("SANDBOX");
    textTitle->SetPositionY(0.90f);
    // Add version
    std::shared_ptr<Graphics::Text> textVersion = this->AddText("0.1.4-dev");
    textVersion->SetColor(Math::Vector4f(0.85f, 0.0f, 0.0f, 1.0f));
    textVersion->SetScale(0.25f);
    textVersion->SetPosition(Math::Vector2f(0.175f, 0.7775f));
    // Add frame delta
    this->_textStats = this->AddText("60 FPS (16.667 ms)");
    this->_textStats->SetScale(0.35f);
    this->_textStats->SetPosition(Math::Vector2f(-0.8225f, 0.96f));

    // Setup flash light
    this->_flashLight->SetColor(Math::Vector3f(1.0f, 1.0f, 0.8f));
    this->_flashLight->SetCutOffAngle(7.5f);
    this->_flashLight->SetOuterCutOffAngleOffset(7.5f);
    this->_flashLight->SetIntensity(0.75f);

    // Load water
    std::shared_ptr<Graphics::Water> water = this->AddWater("water", 1500.0f);

    // Register mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](const float x, const float y)
    {
        if (this->_lockCameraToPlayer)
        {
            this->_camera->IncreaseDistance(y);
        }
    });

    return this->OnSceneSetup();
}

void Sandbox::SandboxScene::Reset()
{
    this->_projectileManager->Reset();
    this->_duckManager->Reset();
    Scene::Reset();
}

bool Sandbox::SandboxScene::OnSceneSetup()
{
    // Load player
    this->_player = this->SetupPlayer("duck");
    this->_player->SetMovingSpeed(1.0f);

    // Add duck entities
    const std::shared_ptr<Graphics::Model> duckModel = Util::ResourcesLoader::Instance().LoadModel("duck");
    const Math::Vector3f duckBoxSize(0.3f, 0.4f, 0.5f);
    for (int i = 0; i < 10; i++)
    {
        std::string entityName = "duck_" + std::to_string(i);
        const float offsetX = 7.5f;
        const float offsetZ = 5.0f;

        const Math::Vector3f position = Math::Vector3f(
            offsetX + Util::Random::Instance().GetReal(0.0f, 20.0f),
            0.0f,
            offsetZ - Util::Random::Instance().GetReal(0.0f, 20.0f)
        );
        const float rotation = Util::Random::Instance().GetAngle();
        const float scale = Util::Random::Instance().GetReal(1.0f, 5.0f);

        // Setup duck entity
        std::shared_ptr<Duck> duck = std::make_shared<Duck>(position, rotation);
        duck->SetModel(duckModel);
        duck->SetPosition(position);
        duck->SetRotationY(rotation);
        duck->SetScale(scale);
        duck->SetMovingSpeed(Util::Random::Instance().GetReal(1.0f, 3.0f));
        this->_duckManager->Manage(duck);

        // Setup physics
        //auto rbDuck = std::make_shared<Math::Box>(position, duckBoxSize * scale, 2.5f);
        //this->_physics->Register(rbDuck, duck);
    }

    // Light up birbs
    std::shared_ptr<Graphics::PointLight> light = this->AddLight("light_birbs");
    light->SetColor(Math::Vector3f(1.0f, 1.0f, 1.0f));
    light->SetPosition(Math::Vector3f(15.0f, 7.5f, 12.5f));
    light->SetAttenuation(Math::Vector3f(1.0f, 0.005f, 0.0075f));
    
    // Add hardcoded mesh to the scene
    std::shared_ptr<Graphics::Entity> hardcoded = std::make_shared<Graphics::Entity>();
    std::shared_ptr<Graphics::Model> hardcodedModel = std::make_shared<Graphics::Model>();
    std::shared_ptr<Graphics::TexturedMesh> hardcodedMesh = std::make_shared<Graphics::TexturedMesh>(
        Hardcoded::Instance().Generate());
    hardcodedMesh->SetMaterial(Graphics::Material(Math::Vector3f(1.0f), 1.0f, 0.25f, 25.0f));
    hardcodedModel->AddMesh("hardcoded", hardcodedMesh);
    hardcodedModel->FinishLoading();
    hardcoded->SetModel(hardcodedModel);
    hardcoded->SetPosition(Math::Vector3f(5.0f, 2.5f, -15.0f));
    this->AddEntity("hardcoded", hardcoded);

    // Add physics test
    auto rbTestCube1 = std::make_shared<Math::Box>(Math::Vector3f(5.0f, 3.0f, -3.0f), Math::Vector3f(0.75f, 0.75f, 0.75f), 0.1f);
    auto testCube1 = this->AddEntity("test_cube_1", "crate");
    this->_physics->Register(rbTestCube1, testCube1);

    auto rbTestCube2 = std::make_shared<Math::Box>(Math::Vector3f(5.0f, 6.0f, -2.0f), Math::Vector3f(0.75f, 0.75f, 0.75f), 1.0f);
    auto testCube2 = this->AddEntity("test_cube_2", "crate");
    this->_physics->Register(rbTestCube2, testCube2);

    return true;
}

void Sandbox::SandboxScene::ProcessCameraInput()
{
    // Detach from camera locked to player
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::D))
    {
        this->_lockCameraToPlayer = false;
    }

    // Attach from camera locked to player
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::A))
    {
        this->_camera->LookAt(this->_player->GetPosition());
        this->_lockCameraToPlayer = true;
    }

    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Right))
    {
        // Mouse relative motion to previous state
        Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();

        // Locked camera
        if (this->_lockCameraToPlayer)
        {
            // Increase viewing rotation relative to the player
            mouseMotion *= 75.0f; // Make motion more sensitive
            this->_camera->IncreaseRotation(Math::Vector3f(-mouseMotion.y, mouseMotion.x, 0.0f));
        }
        // Free camera
        else
        {
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
                this->_camera->IncreaseRotation(Math::Vector3f(-mouseMotion.y, mouseMotion.x, 0.0f));
            }
        }
    }

    // Switch POIs
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::One))
    {
        this->_lockCameraToPlayer = false;
        this->_camera->SetPosition(Math::Vector3f(-10.142110f, 7.907108f, -23.678909f));
        this->_camera->SetRotationX(26.458340f);
        this->_camera->SetRotationY(133.125061f);
    }
    else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Two))
    {
        this->_lockCameraToPlayer = false;
        this->_camera->SetPosition(Math::Vector3f(4.106152f, 1.032108f, 5.452480f));
        this->_camera->SetRotationX(14.374990f);
        this->_camera->SetRotationY(1.289135f);
    }
    else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Three))
    {
        this->_lockCameraToPlayer = false;
        this->_camera->SetPosition(Math::Vector3f(26.611273f, 6.448774f, 11.242806f));
        this->_camera->SetRotationX(25.416643f);
        this->_camera->SetRotationY(-27.304625f);
    }
}

void Sandbox::SandboxScene::ProcessPlayerInput()
{
    const Math::Vector2f cursorPosition2d = Math::Vector2f(this->_cursorPosition.x, this->_cursorPosition.z);

    // Player navigation and interaction
    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Left))
    {
        this->_player->LookAt(cursorPosition2d);
        if (IO::Keyboard::Instance().IsShiftPressed())
        {
            this->_player->Idle();

            if (this->_player->IsReadyToFire())
            {
                this->_player->SingleFire(this->_projectileManager);
            }
        }
        else if (IO::Keyboard::Instance().IsControlPressed())
        {
            this->_player->SetMovingSpeed(15.0f);
        }
        else
        {
            this->_player->SetMovingSpeed(2.0f);
            this->_player->SetTarget(cursorPosition2d);
            this->_player->Follow();
        }
    }

    // Additional "skills"
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::X))
    {
        if (this->_player->IsReadyToFire())
        {
            this->_player->StarFire(this->_projectileManager, 5);
        }
    }
    else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Z))
    {
        if (this->_player->IsReadyToFire())
        {
            this->_player->LookAt(cursorPosition2d);
            this->_player->BeamFire(this->_projectileManager, 4);
        }
    }
}

void Sandbox::SandboxScene::ProcessFlashLight() const
{
    // Turn on flash light
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Right))
    {
        this->_entityRenderer->GetShader(true)->LoadFlashLightEnabled(true);
        this->_waterRenderer->GetShader(true)->LoadFlashLightEnabled(true);
    }

    // Turn off flash light
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Left))
    {
        this->_entityRenderer->GetShader(true)->LoadFlashLightEnabled(false);
        this->_waterRenderer->GetShader(true)->LoadFlashLightEnabled(false);
    }
}

void Sandbox::SandboxScene::ProcessInput()
{
    Scene::ProcessInput();

    this->ProcessCameraInput();

    this->ProcessPlayerInput();

    this->ProcessFlashLight();

    // Enabled fog
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F))
    {
        this->_renderSkybox = false;
        this->_waterRenderer->GetShader(true)->LoadFogEnabled(true);
        this->_entityRenderer->GetShader(true)->LoadFogEnabled(true);
    }

    // Disable fog
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::G))
    {
        this->_renderSkybox = true;
        this->_waterRenderer->GetShader(true)->LoadFogEnabled(false);
        this->_entityRenderer->GetShader(true)->LoadFogEnabled(false);
    }

    // Toggle entities deformation
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::T))
    {
        // Enabled deformation based on time
        this->_entityRenderer->GetShader(true)->LoadDeformationFactor(this->_time / 3.0f);
    }
    else
    {
        // Disable deformation
        this->_entityRenderer->GetShader(true)->LoadDeformationFactor(0.0f);
    }
}

void Sandbox::SandboxScene::Update(const float delta)
{
    Scene::Update(delta);

    // Check camera angle lower threshold
    if (this->_camera->GetRotationX() < 0.5f)
    {
        this->_camera->SetRotationX(0.5f);
    }

    // Check camera angle upper threshold
    if (this->_camera->GetRotationX() > 90.0f)
    {
        this->_camera->SetRotationX(90.0f);
    }

    // Update player
    this->_player->Update(delta);

    // Spectate the player if the camera is locked to player
    if (this->_lockCameraToPlayer)
    {
        this->_camera->Spectate(this->_player->GetPosition());
    }

    // Time based updates
    if (!this->_paused)
    {
        // Update managers
        this->_projectileManager->Update(delta);
        this->_duckManager->Update(delta);

        // GoForward scene day & night cycle effect
        // Intensity interval <SUN_LOWER_LIMIT-1.000>
        const float darkeningFactor = (glm::sin(this->_time / 5.0f) + 1.0f) / (2.0f / (1.0f - SUN_LOWER_LIMIT)) + SUN_LOWER_LIMIT;
        this->_skyboxRenderer->GetShader(true)->LoadDarkeningFactor(darkeningFactor);
        this->_directionalLightsMapping["sun"]->SetIntensity(darkeningFactor);

        // Update hardcoded mesh motion
        if (this->_entitiesMapping["hardcoded"])
        {
            this->_entitiesMapping["hardcoded"]->IncreaseRotationY(45.0f * delta);
            this->_entitiesMapping["hardcoded"]->SetRotationX(glm::sin(this->_time) * 15.0f);
            this->_entitiesMapping["hardcoded"]->SetPositionY(2.5f + glm::sin(this->_time) * 0.5f);
        }
    }
}

void Sandbox::SandboxScene::UpdateDebugInformation(const App::RenderApplication::Stats& stats) const
{
    this->_textStats->SetMesh(this->_textFactory->GenerateMesh(
        Util::String::Format("%d FPS (%.3f ms)", stats.framePerSecond, stats.frameTimeAverage)
    ));
}

void Sandbox::SandboxScene::RenderEntities() const
{
    Scene::RenderEntities();
    this->_projectileManager->RenderWith(this->_entityRenderer);
    this->_duckManager->RenderWith(this->_entityRenderer);
}

std::shared_ptr<Sandbox::Player> Sandbox::SandboxScene::SetupPlayer(const std::string& resourceName)
{
    std::shared_ptr<Player> player = std::make_shared<Player>();
    player->SetModel(Util::ResourcesLoader::Instance().LoadModel(resourceName));
    this->AddEntity("player", player);
    return player;
}
