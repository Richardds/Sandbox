// ----------------------------------------------------------------------------------------
//  \file       SandboxScene.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"

#include <IO/Keyboard.h>
#include <IO/Mouse.h>
#include <Util/ResourcesLoader.h>

#include "SandboxScene.h"
#include "Scene/Hardcoded.h"
#include "Util/Random.h"

Sandbox::SandboxScene::SandboxScene() :
    _lockCameraToPlayer(true),
    _deformationFactor(0.0f)
{
}

bool Sandbox::SandboxScene::Setup()
{
    _Assert(Graphics::Scene::Setup());

    // Create projectile manager
    this->_projectileManager = std::make_shared<ProjectileManager>();

    // Configure camera
    this->_camera->SetDistance(12.5f);
    this->_camera->SetRotationX(20.0f);

    // Load Skybox
    std::shared_ptr<Graphics::Texture> skyboxTexture = Util::ResourcesLoader::Instance().LoadCubeMap("day");
    this->_skybox = std::make_shared<Graphics::Skybox>(skyboxTexture, 750.0f);

    // Configure lights
    //std::shared_ptr<Graphics::PointLight> playerLight = this->AddLight("player_light");
    //playerLight->SetPosition(Math::Vector3f(0.0f, 5.0f, 0.0f));
    //playerLight->SetAttenuation(Math::Vector3f(1.0f, 0.045f, 0.0095f));
    std::shared_ptr<Graphics::PointLight> light1 = this->AddLight("light_1");
    light1->SetColor(Math::Vector3f(1.0f, 0.8f, 0.6f));
    light1->SetPosition(Math::Vector3f(5.0f, 5.0f, 5.0f));
    light1->SetAttenuation(Math::Vector3f(1.0f, 0.1f, 0.025f));

    // TODO: Lights

    // Load water
    std::shared_ptr<Graphics::Water> water = this->AddWater("water", 1500.0f);

    // Load player
    this->_player = this->SetupPlayer("boat");

    // Add house entities
    for (int i = 0; i < 5; i++)
    {
        std::string entityName = "house_" + std::to_string(i);
        const float offsetX = -15.0f;
        const float offsetZ = -10.0f;
        std::shared_ptr<Graphics::Entity> entity = this->AddEntity(entityName, "house");
        entity->SetPosition(Math::Vector3f(
            offsetX + 3.0f * static_cast<float>(i),
            0.0f,
            offsetZ - 7.5f * static_cast<float>(i)
        ));
    }

    // Add pier entities
    for (int i = 0; i < 10; i++)
    {
        std::string entityName = "pier_" + std::to_string(i);
        const float offsetX = 5.0f;
        const float offsetZ = 2.5f;
        std::shared_ptr<Graphics::Entity> entity = this->AddEntity(entityName, "pier_modular");
        entity->SetPosition(Math::Vector3f(
            offsetX,
            0.0f,
            offsetZ - 1.55f * static_cast<float>(i)
        ));
    }

    std::shared_ptr<Graphics::Entity> drum1 = this->AddEntity("drum_1", "drum_shell");
    drum1->SetPosition(Math::Vector3f(5.5f, 0.65f, 2.75f));
    drum1->SetRotationY(45.0f);

    std::shared_ptr<Graphics::Entity> drum2 = this->AddEntity("drum_2", "drum_radioactive");
    drum2->SetPosition(Math::Vector3f(5.5f, 0.65f, 2.15f));
    drum2->SetRotationY(45.0f);

    // Add crate entities
    for (int i = 0; i < 5; i++)
    {
        std::string entityName = "crate_" + std::to_string(i);
        const float offsetX = -7.5f;
        const float offsetZ = 3.0f;
        std::shared_ptr<Graphics::Entity> entity = this->AddEntity(entityName, "water_crate");
        entity->SetRotationX(Util::Random::Instance().GetAngle());
        entity->SetRotationY(Util::Random::Instance().GetAngle());
        entity->SetRotationZ(Util::Random::Instance().GetAngle());
        entity->SetPosition(Math::Vector3f(
            offsetX + Util::Random::Instance().GetReal(-1.0f, 1.0f),
            Util::Random::Instance().GetReal(-0.75f, 0.25f),
            offsetZ - 3.0f * static_cast<float>(i)
        ));
    }

    std::shared_ptr<Graphics::Entity> brickWall = this->AddEntity("brick_wall_1", "brick_wall");
    brickWall->SetPosition(Math::Vector3f(15.0f, 2.0f, -15.0f));
    brickWall->SetRotationX(-30.0f);
    brickWall->SetRotationY(-30.0f);

    // Add hardcoded mesh to the scene
    std::shared_ptr<Graphics::Entity> hardcoded = std::make_shared<Graphics::Entity>();
    std::shared_ptr<Graphics::Model> hardcodedModel = std::make_shared<Graphics::Model>();
    std::shared_ptr<Graphics::TexturedMesh> hardcodedMesh = std::make_shared<Graphics::TexturedMesh>(
        Hardcoded::Instance().Generate());
    hardcodedMesh->SetMaterial(Graphics::Material(Math::Vector3f(1.0f), 1.0f, 0.25f, 25.0f));
    hardcodedModel->AddMesh("hardcoded", hardcodedMesh);
    hardcodedModel->FinishLoading();
    hardcoded->SetModel(hardcodedModel);
    hardcoded->SetPosition(Math::Vector3f(5.0f, 2.5f, -25.0f));
    this->AddEntity("hardcoded", hardcoded);

    // Register mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](float x, float y)
    {
        if (this->_lockCameraToPlayer)
        {
            this->_camera->IncreaseDistance(y);
        }
    });

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
            this->_camera->IncreaseRotation(-mouseMotion.y, mouseMotion.x, 0.0f);
        }
            // Free camera
        else
        {
            if (IO::Keyboard::Instance().IsAltPressed())
            {
                // Increase viewing position relative to the world
                mouseMotion *= -25.0f; // Invert and make motion more sensitive
                this->_camera->IncreasePosition(Math::Vector3f(mouseMotion.x, mouseMotion.y, 0.0f));
            }
            else
            {
                // Increase viewing rotation relative to the world
                mouseMotion *= -75.0f; // Invert and make motion more sensitive
                this->_camera->IncreaseRotation(-mouseMotion.y, mouseMotion.x, 0.0f);
            }
        }
    }

    // Switch POIs
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::One))
    {
        this->_lockCameraToPlayer = false;
        this->_camera->SetPosition(Math::Vector3f(15.0f, 5.0f, -12.0f));
        this->_camera->LookAt(Math::Vector3f(15.0f, 2.0f, -15.0f));
    }
}

void Sandbox::SandboxScene::ProcessPlayerInput()
{
    const Math::Vector3f worldPosition = this->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());
    const Math::Vector2f worldPointer = Math::Vector2f(worldPosition.x, worldPosition.z);

    // Player navigation and interaction
    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Left))
    {
        this->_player->LookAt(worldPointer);
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
            this->_player->Idle();
            this->_player->SetPosition(worldPosition);
        }
        else
        {
            this->_player->SetTarget(worldPointer);
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
            this->_player->LookAt(worldPointer);
            this->_player->BeamFire(this->_projectileManager, 4);
        }
    }
}

void Sandbox::SandboxScene::ProcessInput()
{
    Scene::ProcessInput();

    this->ProcessCameraInput();

    this->ProcessPlayerInput();

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
}

void Sandbox::SandboxScene::Update(const float delta)
{
    Scene::Update(delta);

    this->_projectileManager->Update(delta);

    this->_player->Update(delta);

    if (this->_lockCameraToPlayer)
    {
        this->_camera->Spectate(this->_player->GetPosition());
    }

    // Update player light position
    //const Math::Vector3f playerPosition = this->_player->GetPosition();
    //const float lightPositionY = this->_lights["player_light"]->GetPositionY();
    //this->_lights["player_light"]->SetPosition(Math::Vector3f(playerPosition.x, lightPositionY, playerPosition.z));

    // Time based updates
    if (!this->_paused)
    {
        // GoForward water motion
        this->_waterTiles["water"]->SetPositionY(glm::sin(this->_time / 1.75f) / 35.0f);

        // GoForward scene day & night cycle effect
        // Intensity interval <SUN_LOWER_LIMIT-1.000>
        //const float darkeningFactor = (glm::sin(this->_time / 5.0f) + 1.0f) / (2.0f / (1.0f - SUN_LOWER_LIMIT)) + SUN_LOWER_LIMIT;
        //this->_skyboxRenderer->GetShader(true)->LoadDarkeningFactor(darkeningFactor);
        //this->_sun->SetIntensity(darkeningFactor);
        //IO::Console::Instance().Info("Sun: %f\n", darkeningFactor);

        // Update hardcoded mesh rotation
        this->_entities["hardcoded"]->IncreaseRotationY(45.0f * delta);
        this->_entities["hardcoded"]->SetRotationX(glm::sin(this->_time) * 15.0f);
    }
}

void Sandbox::SandboxScene::Render()
{
    this->_entityRenderer->GetShader(true)->LoadDeformationFactor(this->_deformationFactor);
    Scene::Render();
}

void Sandbox::SandboxScene::RenderEntities()
{
    Scene::RenderEntities();
    this->_projectileManager->RenderWith(this->_entityRenderer);
}

std::shared_ptr<Sandbox::Player> Sandbox::SandboxScene::SetupPlayer(const std::string& resourceName)
{
    const std::string playerEntityName = "player";
    const auto it = this->_entities.find(playerEntityName);
    _Assert(it == this->_entities.end());
    std::shared_ptr<Player> player = std::make_shared<Player>();
    player->SetModel(Util::ResourcesLoader::Instance().LoadModel(resourceName));
    this->_entities.emplace_hint(it, playerEntityName, player);
    return player;
}
