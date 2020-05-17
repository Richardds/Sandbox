#include <Util/ResourcesLoader.h>
#include <IO/Console.h>
#include <IO/Keyboard.h>
#include <IO/Mouse.h>

#include "GunnerBoiScene.h"

GunnerBoi::GunnerBoiScene::GunnerBoiScene() :
    _lockCameraToPlayer(true)
{
}

GunnerBoi::GunnerBoiScene::~GunnerBoiScene()
{
}

bool GunnerBoi::GunnerBoiScene::Setup()
{
    _assert(Graphics::Scene::Setup());

    // Create projectile manager
    this->_projectileManager = std::make_shared<ProjectileManager>();

    // Configure camera
    this->_camera->SetDistance(10.0f);

    // Configure lights
    std::shared_ptr<Graphics::PointLight> playerLight = this->AddLight("player_light");
    playerLight->setPosition(Math::Vector3f(0.0f, 5.0f, 0.0f));
    playerLight->SetAttenuation(Math::Vector3f(1.0f, 0.045f, 0.0095f));

    // Load terrain
    std::shared_ptr<Graphics::Entity> terrain = this->AddEntity("terrain", "terrain");

    // Load water
    std::shared_ptr<Graphics::Water> water = this->AddWater("water", 10.0f);

    // Load player
    this->_player = this->SetupPlayer("arrow");

    // Load other models
    std::shared_ptr<Graphics::Entity> crate1 = this->AddEntity("crate_01", "crate");
    crate1->setPosition(Math::Vector3f(-1.5f, 0.0f, -3.0f));
    std::shared_ptr<Graphics::Entity> crate2 = this->AddEntity("crate_02", "crate");
    crate2->setPosition(Math::Vector3f(1.5f, 0.0f, -3.0f));
    std::shared_ptr<Graphics::Entity> crate3 = this->AddEntity("crate_03", "crate");
    crate3->setPosition(Math::Vector3f(0.0f, 1.5f, -3.0f));
    crate3->setRotationY(45.0f);
    std::shared_ptr<Graphics::Entity> crate4 = this->AddEntity("crate_04", "crate");
    crate4->setPosition(Math::Vector3f(3.25f, 0.0f, -1.75f));
    std::shared_ptr<Graphics::Entity> rock1 = this->AddEntity("rock_01", "rock");
    rock1->setPosition(Math::Vector3f(-3.25f, 0.0f, -1.65f));
    std::shared_ptr<Graphics::Entity> brickWall = this->AddEntity("brick_wall_01", "brick_wall");
    brickWall->setPosition(Math::Vector3f(7.5f, 0.0f, -5.0f));
    brickWall->setRotationY(-45.0f);

    // Register mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](float x, float y) {
        if (this->_lockCameraToPlayer) {
            this->_camera->IncreaseDistance(y);
        }
    });

    return true;
}

void GunnerBoi::GunnerBoiScene::ProcessInput()
{
    Graphics::Scene::ProcessInput();

    // Player navigation and interation
    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
        Math::Vector3f worldPosition = this->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());
        Math::Vector2f target = Math::Vector2f(worldPosition.x, worldPosition.z);
        if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::LEFT_SHIFT)) {
            this->_player->Idle();
            this->_player->LookAt(target);

            if (this->_player->IsReadyToFire()) {
                this->_projectileManager->Manage(this->_player->Fire());
            }
        }
        else {
            this->_player->SetTarget(target);
            this->_player->Follow();
        }
    }

    // Camera motion
    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::RIGHT)) {
        Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();
        mouseMotion *= 50.0f;

        // Invert camera motion on free camera
        if (!this->_lockCameraToPlayer) {
            mouseMotion *= -1;
        }

        this->_camera->increaseRotation(-mouseMotion.y, mouseMotion.x, 0.0f);
    }

    // Camera modes
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::ONE)) {
        this->_lockCameraToPlayer = true;
    }
    else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::TWO)) {
        this->_lockCameraToPlayer = false;
        this->_camera->setPosition(Math::Vector3f(-10.0f, 10.0f, 5.0f));
        this->_camera->LookAt(Math::Vector3f(0.0f, 0.0f, 0.0f));
    }
    else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::THREE)) {
        this->_lockCameraToPlayer = false;
        this->_camera->setPosition(Math::Vector3f(15.0f, 20.0f, 10.0f));
        this->_camera->LookAt(Math::Vector3f(0.0f, 0.0f, 0.0f));
    }
}

void GunnerBoi::GunnerBoiScene::Update(float delta)
{
    Graphics::Scene::Update(delta);

    this->_projectileManager->Update(delta);

    this->_player->Update(delta);

    if (this->_lockCameraToPlayer) {
        this->_camera->Spectate(this->_player->getPosition());
    }

    Math::Vector3f playerPosition = this->_player->getPosition();
    float lightPositionY = this->_lights["player_light"]->getPositionY();
    this->_lights["player_light"]->setPosition(Math::Vector3f(playerPosition.x, lightPositionY, playerPosition.z));
}

void GunnerBoi::GunnerBoiScene::Render()
{
    Scene::Render();
}

void GunnerBoi::GunnerBoiScene::RenderEntities()
{
    Graphics::Scene::RenderEntities();
    this->_projectileManager->RenderWith(this->_entityRenderer);
}

std::shared_ptr<GunnerBoi::Boi> GunnerBoi::GunnerBoiScene::SetupPlayer(const std::string& resourceName)
{
    const std::string playerEntityName = "player";
    auto it = this->_entities.find(playerEntityName);
    _assert(it == this->_entities.end());
    std::shared_ptr<Boi> player = std::make_shared<Boi>();
    std::shared_ptr<Graphics::Model> model = Util::ResourcesLoader::Instance().LoadModel(resourceName);
    player->SetModel(model);
    this->_entities.emplace_hint(it, playerEntityName, player);
    return player;
}
